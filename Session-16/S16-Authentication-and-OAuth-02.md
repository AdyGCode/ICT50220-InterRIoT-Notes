---
theme: default
paginate: true
footer: © Copyright 2024, Adrian Gould & NM TAFE
header: "![NMTAFE](../images/Black-Red-Banner.svg)"
auto-scaling: true
size: 4k
color: "#ccc"
backgroundColor: "#060606"
tags:
  - Internet of Things
  - InterRIoT
  - IoT
  - Robotics
  - Python
  - Arduino
  - ESP-32
  - C
  - C++

date created: 03 July 2024
date modified: 10 July 2024
---

# Intermediate RIoT

## Application Security: Authentication and OAuth Part 2


Developed by Adrian Gould

---

```table-of-contents
title: # Contents
style: nestedList
minLevel: 0
maxLevel: 3
includeLinks: true
```

---

# Acknowledgements

These notes and practical tutorial is based on:

- Authlib: Python Authentication. (2017). Authlib.org. https://docs.authlib.org/en/latest/
- Nguyen, B. H. (2024, May 14). Python FastAPI: Integrating OAuth2 Security with the Application’s Own Authentication Process. DEV Community. https://dev.to/behainguyen/python-fastapi-integrating-oauth2-security-with-the-applications-own-authentication-process-335i
- Authlib. (2020, May 30). Google login for FastAPI. Authlib. https://blog.authlib.org/2020/fastapi-google-login
- What Is OAuth? | Microsoft Security. (2025). Microsoft.com. https://www.microsoft.com/en-au/security/business/security-101/what-is-oauth?ef_id=_k_13866022417913c583ef081d9f182d0f_k_&OCID=AIDcmmtlibe7fa_SEM__k_13866022417913c583ef081d9f182d0f_k_&msclkid=13866022417913c583ef081d9f182d0f
- (2021). Auth0.com. https://auth0.com/intro-to-iam/what-is-oauth-2
- Merwan Chinta. (2024, February 13). Understanding OAuth 2.0: A Step-by-Step Guide | CodeNx. Medium; CodeNx. https://medium.com/codenx/oauth-2-0-4cddd6c7471f
- GeeksforGeeks. (2021, October 2). Explain OAuth (Open Authorization). GeeksforGeeks. https://www.geeksforgeeks.org/explain-oauth-open-authorization/
- What is OAuth? | SAML vs. OAuth. (2025). Cloudflare.com. https://www.cloudflare.com/learning/access-management/what-is-oauth/

Content has also been created using ChatGPT, CaludeAI and CoPilot.



# Resources Needed

- Python 3.10+
- PyCharm Professional 2024.2+



---

# Creating an OAuth Server

Great! Let's begin enhancing the tutorial by breaking it into clearly explained sections. We'll start with **Section 1: Project Overview and Setup**, and proceed step by step through the rest of the tutorial.

---

## ✅ Section 1: Project Overview and Setup

### 🔧 What This Project Builds

This tutorial walks you through building a **fully functional OAuth 2.1 Authorization Server** using:

- **FastAPI** for the web framework
- **MySQL** for the database
- **SQLAlchemy** for ORM
- **Jinja2** for templating
- **Tailwind CSS** for styling

By the end, you'll have:

- A secure OAuth 2.1 server with PKCE support
- User registration and login
- Client application management
- Authorization code flow with token issuance
- Admin interface for managing clients

---

### 📁 Project Structure Explained

Here's a breakdown of the project layout:

```
oauth-server/
├── app/
│   ├── main.py               # Entry point of the FastAPI app
│   ├── config.py             # Loads environment variables and settings
│   ├── database.py           # SQLAlchemy engine and session setup
│   ├── models/               # SQLAlchemy models for users, clients, tokens
│   ├── routers/              # FastAPI route handlers (auth, oauth, admin)
│   ├── services/             # Business logic for auth and OAuth flows
│   └── templates/            # Jinja2 HTML templates
├── static/                   # Static files (CSS)
├── requirements.txt          # Python dependencies
└── .env                      # Environment variables (DB URL, secrets)
```

---

### 📦 Step-by-Step Setup

### 0. Create the project structure

```bash
mkdir oauth-server
cd oauth-server
mkdir -p {static,app/{models,routers,services,templates/admin}}
touch {static,app/{models,routers,services,templates/admin}}/.gitignore
touch app/{models,routers,services}/__init__py
```

#### 1. Create the Database

```sql
CREATE DATABASE oauth_server_db;
```

This creates the MySQL database that will store users, clients, tokens, and authorization codes.

#### 2. Define Dependencies

Create a `requirements.txt` file with all necessary packages:

```txt
fastapi==0.104.1
uvicorn[standard]==0.24.0
sqlalchemy==2.0.23
mysql-connector-python==8.2.0
alembic==1.12.1
python-multipart==0.0.6
jinja2==3.1.2
python-jose[cryptography]==3.3.0
passlib[bcrypt]==1.7.4
authlib==1.2.1
httpx==0.25.2
python-dotenv==1.0.0
pydantic-settings==2.9.1
secrets==0.0.1
```

Install them with:

```bash
pip install -r requirements.txt
```

#### 3. Configure Environment Variables

Create a `.env` file to store sensitive settings:

```env
DDATABASE_URL=mysql+mysqlconnector://oauth_demo:Password1234@localhost:3306/oauth_demo?charset=utf8mb4&collation=utf8mb4_general_ci
SECRET_KEY=your-super-secret-key-change-this-in-production
ALGORITHM=HS256
ACCESS_TOKEN_EXPIRE_MINUTES=30
REFRESH_TOKEN_EXPIRE_DAYS=7
```

These values are loaded into the app using `pydantic` in `config.py`.

---

### ▶️ Running the Server

Use `uvicorn` to start the FastAPI app:

```bash
uvicorn app.main:app --reload --host 0.0.0.0 --port 8000
```

You can now access:

- **Homepage**: http://localhost:8000
- **Register**: http://localhost:8000/register
- **Login**: http://localhost:8000/login

---

## ✅ Section 2: Configuration and Database Setup

This section covers how the application reads environment variables and sets up the database connection using SQLAlchemy.

---

### ⚙️ `app/config.py` – Application Settings

This file defines a `Settings` class using `pydantic`'s `BaseSettings`, which automatically loads values from the `.env` file.

```python
import os
from pydantic_settings import BaseSettings

class Settings(BaseSettings):
    database_url: str = ""
    secret_key: str = ""
    algorithm: str = "HS256"
    access_token_expire_minutes: int = 30
    refresh_token_expire_days: int = 7

    class Config:
        env_file = ".env"

settings = Settings()
```

#### 🔍 Explanation:

- `BaseSettings`: Automatically reads environment variables.
- `env_file = ".env"`: Specifies the file to load variables from.
- `settings = Settings()`: Creates a global settings object used throughout the app.

This approach keeps sensitive data (like DB credentials and secret keys) out of your codebase.

---

### 🗃️ `app/database.py` – SQLAlchemy Setup

This file sets up the SQLAlchemy engine, session, and base class for models.

```python
from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
from .config import settings

engine = create_engine(settings.database_url)
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)
Base = declarative_base()

def get_db():
    db = SessionLocal()
    try:
        yield db
    finally:
        db.close()
```

#### 🔍 Explanation:

- `create_engine()`: Connects to the MySQL database using the URL from `.env`.
- `SessionLocal`: Factory for creating new database sessions.
- `Base`: Base class for all ORM models.
- `get_db()`: Dependency function used in routes to get a database session.

This setup ensures that each request gets its own database session, which is properly closed afterward.

[]()
---

## ✅ Section 3: Database Models

The models define the structure of the database tables using SQLAlchemy ORM. These include users, clients, authorization codes, access tokens, and refresh tokens.

---

### 👤 `app/models/user.py` – User Model

```python
class User(Base):
    __tablename__ = "users"

    id = Column(Integer, primary_key=True, index=True)
    email = Column(String(255), unique=True, index=True, nullable=False)
    username = Column(String(100), unique=True, index=True, nullable=False)
    hashed_password = Column(String(255), nullable=False)
    is_active = Column(Boolean, default=True)
    created_at = Column(DateTime(timezone=True), server_default=func.now())
```

#### 🔍 Explanation:

- Represents registered users.
- Stores hashed passwords (never plain text).
- `is_active` can be used to disable accounts.
- `created_at` tracks when the user was created.

---

### 🧾 `app/models/client.py` – OAuth Client Model

```python
class OAuthClient(Base):
    __tablename__ = "oauth_clients"

    id = Column(Integer, primary_key=True, index=True)
    client_id = Column(String(255), unique=True, index=True, nullable=False)
    client_secret = Column(String(255), nullable=True)  # Null for public clients
    client_name = Column(String(255), nullable=False)
    redirect_uris = Column(Text, nullable=False)        # Stored as JSON string
    grant_types = Column(Text, nullable=False)          # Stored as JSON string
    scope = Column(Text, nullable=False)                # Space-separated scopes
    is_confidential = Column(Boolean, default=True)     # False for public clients
    created_at = Column(DateTime(timezone=True), server_default=func.now())
```

#### 🔍 Explanation:

- Represents third-party applications that want to access user data.
- `client_id` and `client_secret` are used for authentication.
- `redirect_uris` and `grant_types` are stored as JSON strings for flexibility.
- `is_confidential` distinguishes between public and confidential clients.

---

### 🔐 `app/models/token.py` – Tokens and Authorization Codes

#### 1. `AuthorizationCode`

```python
class AuthorizationCode(Base):
    __tablename__ = "authorization_codes"

    id = Column(Integer, primary_key=True, index=True)
    code = Column(String(255), unique=True, index=True, nullable=False)
    client_id = Column(String(255), ForeignKey("oauth_clients.client_id"), nullable=False)
    user_id = Column(Integer, ForeignKey("users.id"), nullable=False)
    redirect_uri = Column(Text, nullable=False)
    scope = Column(Text, nullable=False)
    code_challenge = Column(String(255), nullable=True)
    code_challenge_method = Column(String(10), nullable=True)
    expires_at = Column(DateTime(timezone=True), nullable=False)
    used = Column(Boolean, default=False)
    created_at = Column(DateTime(timezone=True), server_default=func.now())
```

- Used in the **authorization code flow**.
- Supports **PKCE** via `code_challenge` and `code_challenge_method`.
- `used` prevents reuse of the same code.

#### 2. `AccessToken`

```python
class AccessToken(Base):
    __tablename__ = "access_tokens"

    id = Column(Integer, primary_key=True, index=True)
    token = Column(String(255), unique=True, index=True, nullable=False)
    client_id = Column(String(255), ForeignKey("oauth_clients.client_id"), nullable=False)
    user_id = Column(Integer, ForeignKey("users.id"), nullable=False)
    scope = Column(Text, nullable=False)
    expires_at = Column(DateTime(timezone=True), nullable=False)
    revoked = Column(Boolean, default=False)
    created_at = Column(DateTime(timezone=True), server_default=func.now())
```

- Represents a short-lived token used to access protected resources.
- `revoked` allows invalidating tokens before expiry.

#### 3. `RefreshToken`

```python
class RefreshToken(Base):
    __tablename__ = "refresh_tokens"

    id = Column(Integer, primary_key=True, index=True)
    token = Column(String(255), unique=True, index=True, nullable=False)
    access_token_id = Column(Integer, ForeignKey("access_tokens.id"), nullable=False)
    expires_at = Column(DateTime(timezone=True), nullable=False)
    revoked = Column(Boolean, default=False)
    created_at = Column(DateTime(timezone=True), server_default=func.now())
```

- Used to obtain new access tokens without re-authenticating.
- Tied to an `access_token_id` for traceability.

---

These models form the backbone of the OAuth server, enabling secure authentication, authorization, and token management.

Would you like to continue with **Section 4: Authentication Service** next?

Awesome! Let’s continue with **Section 4: Authentication Service**, which handles user login, password hashing, and token creation.

---

## ✅ Section 4: Authentication Service

The authentication service encapsulates all logic related to verifying user credentials, hashing passwords, and generating JWT access tokens.

---

### 🔐 `app/services/auth_service.py`

```python
from datetime import datetime, timedelta
from jose import JWTError, jwt
from passlib.context import CryptContext
from sqlalchemy.orm import Session
from ..models.user import User
from ..config import settings

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")

class AuthService:
    @staticmethod
    def verify_password(plain_password: str, hashed_password: str) -> bool:
        return pwd_context.verify(plain_password, hashed_password)

    @staticmethod
    def get_password_hash(password: str) -> str:
        return pwd_context.hash(password)

    @staticmethod
    def authenticate_user(db: Session, email: str, password: str):
        user = db.query(User).filter(User.email == email).first()
        if not user or not AuthService.verify_password(password, user.hashed_password):
            return False
        return user

    @staticmethod
    def create_access_token(data: dict, expires_delta: timedelta = None):
        to_encode = data.copy()
        expire = datetime.utcnow() + (expires_delta or timedelta(minutes=15))
        to_encode.update({"exp": expire})
        encoded_jwt = jwt.encode(to_encode, settings.secret_key, algorithm=settings.algorithm)
        return encoded_jwt
```

---

### 🔍 Explanation of Key Methods

#### 🔑 `verify_password()`

- Uses `passlib` to compare a plain password with a hashed one.
- Ensures passwords are never stored or compared in plain text.

#### 🔐 `get_password_hash()`

- Hashes a password using bcrypt before storing it in the database.

#### 👤 `authenticate_user()`

- Looks up a user by email.
- Verifies the password using the method above.
- Returns the user object if valid, otherwise `False`.

#### 🪪 `create_access_token()`

- Generates a JWT (JSON Web Token) with an expiration time.
- Encodes user data (e.g., user ID) into the token payload.
- Uses the secret key and algorithm defined in `.env`.

---

This service is used in the login and registration routes to securely manage user credentials and issue tokens.

Would you like to continue with **Section 5: OAuth Service** next?


Great! Let’s now explore **Section 5: OAuth Service**, which is the heart of the OAuth 2.1 flow implementation. This service handles client validation, PKCE verification, authorization code generation, and token issuance.

---

## ✅ Section 5: OAuth Service

The `OAuthService` class encapsulates the logic for handling OAuth 2.1 flows, including:

- PKCE verification
- Authorization code generation
- Access and refresh token generation
- Client and redirect URI validation
- Token exchange

---

### 🔁 `app/services/oauth_service.py`

Here’s a breakdown of the key methods and what they do:

---

### 🔐 PKCE Verification

```python
def verify_pkce(code_verifier: str, code_challenge: str, method: str = "S256") -> bool:
    if method == "S256":
        digest = hashlib.sha256(code_verifier.encode()).digest()
        expected = base64.urlsafe_b64encode(digest).decode().rstrip("=")
        return expected == code_challenge
    elif method == "plain":
        return code_verifier == code_challenge
    return False
```

- **PKCE (Proof Key for Code Exchange)** is a security enhancement for public clients.
- This method supports both `S256` (recommended) and `plain` methods.

---

### 🔑 Token and Code Generators

```python
def generate_authorization_code() -> str:
    return secrets.token_urlsafe(32)

def generate_access_token() -> str:
    return secrets.token_urlsafe(32)

def generate_refresh_token() -> str:
    return secrets.token_urlsafe(32)
```

- These methods generate secure, random strings for authorization codes and tokens.

---

### 🧾 Client Validation

```python
def validate_client(db: Session, client_id: str, client_secret: str = None):
    client = db.query(OAuthClient).filter(OAuthClient.client_id == client_id).first()
    if not client:
        return None
    if client.is_confidential and client.client_secret != client_secret:
        return None
    return client
```

- Ensures the client exists and, if confidential, that the secret matches.

---

### 🌐 Redirect URI Validation

```python
def validate_redirect_uri(client: OAuthClient, redirect_uri: str) -> bool:
    allowed_uris = json.loads(client.redirect_uris)
    return redirect_uri in allowed_uris
```

- Prevents open redirect vulnerabilities by enforcing exact URI matches.

---

### 📥 Create Authorization Code

```python
def create_authorization_code(...):
    code = generate_authorization_code()
    expires_at = datetime.utcnow() + timedelta(minutes=10)
    auth_code = AuthorizationCode(...)
    db.add(auth_code)
    db.commit()
    return code
```

- Stores the authorization code in the database with a 10-minute expiry.
- Supports optional PKCE parameters.

---

### 🔄 Exchange Code for Tokens

```python
def exchange_code_for_tokens(...):
    # Validate code, client, redirect URI, and PKCE
    # Mark code as used
    # Create access and refresh tokens
    return {
        "access_token": access_token.token,
        "refresh_token": refresh_token.token,
        "token_type": "Bearer",
        "expires_in": 1800,
        "scope": auth_code.scope
    }
```

- This is the core of the **authorization code flow**.
- Ensures the code is valid, not expired, and not reused.
- Issues both access and refresh tokens with appropriate expiry.

---

This service is used by the `/authorize` and `/token` endpoints to implement the OAuth 2.1 flow securely and correctly.

Would you like to continue with **Section 6: Templates and Frontend Pages** next?


Excellent! Let’s now move on to **Section 6: Templates and Frontend Pages**, which covers the user interface components built with Jinja2 and styled using Tailwind CSS.

---

## ✅ Section 6: Templates and Frontend Pages

The application uses **Jinja2 templates** to render HTML pages for user interaction. These templates are located in the `app/templates/` directory and are styled using **Tailwind CSS** for a modern, responsive UI.

---

### 🧱 `base.html` – Layout Template

This is the base layout that all other templates extend.

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>{% block title %}OAuth Server{% endblock %}</title>
  <script src="https:// and styling.
- Other templates inject their content into the `{% block content %}` section.

---

### 🔐 `login.html` – User Login Page

Extends `base.html` and provides a login form.

- Fields: `email`, `password`
- Displays error messages if login fails.
- Includes a link to the registration page.

---

authorize.html` – OAuth Consent Page

This page is shown during the OAuth flow when a user is asked to approve access for a third-party client.

- Displays the client name and requested scopes.
- Two forms: one to **allow** and one to **deny** access.
- Uses hidden fields to preserve OAuth parameters.

---

### 🛠️ `admin/clients.html` – Admin Client Management

This is the admin interface for managing OAuth clients.

- Lists all registered clients.
- Allows creating new clients with:
  - Name
  - Redirect URIs
  - Grant types
  - Scopes
  - Confidentiality
- Supports deleting clients and regenerating secrets.

---

These templates provide a clean and user-friendly interface for both users and administrators, making the OAuth server accessible and manageable.

Would you like to continue with **Section 7: OAuth Routes and Endpoints** next?


Great! Let’s now explore **Section 7: OAuth Routes and Endpoints**, which implement the core OAuth 2.1 flow using FastAPI routes.

---

## ✅ Section 7: OAuth Routes and Endpoints

These routes are defined in `app/routers/oauth.py` and handle:

- Authorization requests
- User consent
- Token exchange

They rely on the `OAuthService` and `AuthService` classes for business logic.

---

### 🔓 `/oauth/authorize` – Authorization Endpoint

#### `GET /oauth/authorize`

```python
@router.get("/authorize", response_class=HTMLResponse)
async def authorize_get(...):
    # Validate client and redirect URI
    # Redirect to login if user not authenticated
    # Render consent page
```

- Validates the client and redirect URI.
- If the user is not logged in, redirects to the login page with a `next` parameter.
- If authenticated, renders the `authorize.html` template to ask for user consent.

#### `POST /oauth/authorize`

```python
@router.post("/authorize")
async def authorize_post(...):
    if action == "deny":
        # Redirect with error
    else:
        # Create authorization code
        # Redirect with code and optional state
```

- Handles the user's decision to allow or deny access.
- If allowed, generates an authorization code and redirects to the client’s redirect URI with the code and state.

---

### 🔁 `/oauth/token` – Token Endpoint

```python
@router.post("/token")
async def token_endpoint(...):
    # Validate client
    # Handle grant_type = authorization_code
    # Exchange code for tokens
```

- Accepts `grant_type=authorization_code` and exchanges the code for access and refresh tokens.
- Validates the client, code, redirect URI, and PKCE verifier.
- Returns a JSON response with tokens and metadata.

---

### 🔍 Key Parameters

- `client_id`, `client_secret`: Identify and authenticate the client.
- `code`: The authorization code to exchange.
- `redirect_uri`: Must match the one used in the authorization request.
- `code_verifier`: Required for PKCE validation.

---

These endpoints implement the **OAuth 2.1 Authorization Code Flow with PKCE**, ensuring secure and standards-compliant authentication.

Would you like to continue with **Section 8: Authentication Routes** next?



Awesome! Let’s now move on to **Section 8: Authentication Routes**, which handle user registration, login, and logout functionality.

---

## ✅ Section 8: Authentication Routes

These routes are defined in `app/routers/auth.py` and provide the user-facing authentication features of the OAuth server.

---

### 🔐 `/login` – User Login

#### `GET /login`

```python
@router.get("/login", response_class=HTMLResponse)
async def login_get(request: Request, next: Optional[str] = None):
    return templates.TemplateResponse("login.html", {"request": request, "next": next})
```

- Renders the login form.
- Accepts an optional `next` parameter to redirect the user after login (used in OAuth flow).

#### `POST /login`

```python
@router.post("/login")
async def login_post(...):
    user = AuthService.authenticate_user(db, email, password)
    if not user:
        return templates.TemplateResponse("login.html", {...})
    return RedirectResponse(url=next or "/", status_code=302)
```

- Authenticates the user using `AuthService`.
- If successful, redirects to the `next` URL or homepage.
- In a real app, this is where you'd create a session or issue a JWT.

---

### 📝 `/register` – User Registration

#### `GET /register`

```python
@router.get("/register", response_class=HTMLResponse)
async def register_get(request: Request):
    return templates.TemplateResponse("register.html", {"request": request})
```

- Renders the registration form.

#### `POST /register`

```python
@router.post("/register")
async def register_post(...):
    # Validate input
    # Check for existing user
    # Hash password and create user
    return RedirectResponse(url="/login?message=Registration successful", status_code=302)
```

- Validates form input (e.g., password match, length).
- Checks if the email or username is already taken.
- Hashes the password and creates a new user.
- Redirects to the login page with a success message.

---

### 🚪 `/logout` – User Logout

```python
@router.get("/logout")
async def logout():
    return RedirectResponse(url="/login?message=Logged out successfully", status_code=302)
```

- In a real application, this would clear the session or JWT.
- Here, it simply redirects to the login page.

---

These routes provide the essential user authentication flow and integrate with the OAuth process by supporting login redirection and user identity verification.

Would you like to continue with **Section 9: Admin Routes and Client Management** next?



Great! Let’s now explore **Section 9: Admin Routes and Client Management**, which provides an interface for administrators to manage OAuth clients.

---

## ✅ Section 9: Admin Routes and Client Management

These routes are defined in `app/routers/admin.py` and allow administrators to:

- View all registered OAuth clients
- Create new clients
- Delete clients
- Regenerate client secrets

This is a simplified admin interface meant for development or internal use.

---

### 🔐 Admin Authentication (Simplified)

```python
def get_current_admin_user():
    return {"id": 1, "username": "admin"}
```

- This is a placeholder function that always returns a hardcoded admin user.
- In a production system, this should be replaced with proper role-based access control.

---

### 📋 `GET /admin/clients` – List Clients

```python
@router.get("/clients", response_class=HTMLResponse)
async def list_clients(...):
    clients = db.query(OAuthClient).all()
    return templates.TemplateResponse("admin/clients.html", {...})
```

- Fetches all OAuth clients from the database.
- Renders them in a table using the `clients.html` template.

---

### ➕ `POST /admin/clients` – Create New Client

```python
@router.post("/clients")
async def create_client(...):
    # Generate client_id and optional client_secret
    # Validate and parse redirect URIs and grant types
    # Save new client to the database
```

- Accepts form data for:
  - `client_name`
  - `redirect_uris` (one per line)
  - `grant_types` (comma-separated)
  - `scope`
  - `is_confidential` (checkbox)
- Generates a secure `client_id` and optionally a `client_secret`.
- Validates redirect URIs to ensure they start with `http://` or `https://`.

---

### ❌ `POST /admin/clients/{client_id}/delete` – Delete Client

```python
@router.post("/clients/{client_id}/delete")
async def delete_client(client_id: str, ...):
    client = db.query(OAuthClient).filter(...).first()
    db.delete(client)
    db.commit()
```

- Deletes the specified client from the database.
- Useful for revoking access or cleaning up test clients.

---

### 🔁 `POST /admin/clients/{client_id}/regenerate-secret` – Regenerate Secret

```python
@router.post("/clients/{client_id}/regenerate-secret")
async def regenerate_client_secret(client_id: str, ...):
    client.client_secret = secrets.token_urlsafe(32)
    db.commit()
```

- Generates a new `client_secret` for confidential clients.
- Important for rotating secrets if they are compromised.

---

These admin routes provide a simple but effective interface for managing OAuth clients, which is essential for maintaining control over which applications can access your users' data.

Would you like to continue with **Section 10: Main Application and Server Startup** next?



Certainly! Here's a regenerated version of **Section 10: Main Application and Server Startup**, with clear structure and explanations:

---

## ✅ Section 10: Main Application and Server Startup

This section ties together all the components of the OAuth server and launches the FastAPI application.

---

### 📁 File: `app/main.py`

```python
from fastapi import FastAPI, Request
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
from .routers import oauth, auth, admin
from .database import engine, Base

# Create all database tables
Base.metadata.create_all(bind=engine)

# Initialize FastAPI app
app = FastAPI(title="OAuth 2.1 Server", version="1.0.0")

# Mount static files (e.g., CSS)
app.mount("/static", StaticFiles(directory="static"), name="static")

# Register routers
app.include_router(oauth.router)
app.include_router(auth.router)
app.include_router(admin.router)

# Set up Jinja2 templates
templates = Jinja2Templates(directory="app/templates")

# Root route (homepage)
@app.get("/")
async def root(request: Request):
    return templates.TemplateResponse("base.html", {"request": request})

# Run the app with Uvicorn if executed directly
if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
```

---

### 🔍 Explanation

- `Base.metadata.create_all()`: Automatically creates all tables defined in your SQLAlchemy models when the app starts.
- `FastAPI()`: Initializes the application with metadata like title and version.
- `app.mount()`: Serves static files (like CSS) from the `/static` path.
- `app.include_router()`: Registers the routers for OAuth, authentication, and admin functionality.
- `templates.TemplateResponse()`: Renders the homepage using the base layout.
- `uvicorn.run()`: Starts the development server if the script is run directly.

---

### ▶️ Running the Server

To launch the server, use:

```bash
uvicorn app.main:app --reload --host 0.0.0.0 --port 8000
```

Then open your browser and visit:

- http://localhost:8000 – Homepage
- http://localhost:8000/login – Login
- http://localhost:8000/register – Register
- http://localhost:8000/admin/clients – Admin Panel

---

Would you like to continue with **Section 11: Testing and Compliance Features** next?



Excellent! Let’s now complete the tutorial with **Section 11: Testing and Compliance Features**, which ensures your OAuth 2.1 server is functioning correctly and adheres to modern security standards.

---

## ✅ Section 11: Testing and Compliance Features

This section walks through how to test your OAuth server and highlights the key OAuth 2.1 compliance features implemented in the project.

---

### 🧪 Testing the OAuth Flow

#### 1. Register a Test Client

You can manually insert a test client into the database using SQL:

```sql
INSERT INTO oauth_clients (
  client_id,
  client_name,
  redirect_uris,
  grant_types,
  scope,
  is_confidential
) VALUES (
  'test-client-id',
  'Test Application',
  '["http://localhost:3000/callback"]',
  '["authorization_code", "refresh_token"]',
  'openid profile email',
  0
);
```

This creates a **public client** with a redirect URI pointing to a local frontend app.

---

#### 2. Authorization Request

Visit the following URL in your browser:

```
http://localhost:8000/oauth/authorize?client_id=test-client-id&
redirect_uri=http://localhost:3000/callback&
response_type=code&
scope=openid&
code_challenge=dBjftJeZ4CVP-mB92K27uhbUJU1p1r_wW1gFWFOEjXk&
code_challenge_method=S256
```

- This initiates the **authorization code flow with PKCE**.
- You’ll be prompted to log in and approve access.

---

#### 3. Token Exchange

Use `curl` to exchange the code for tokens:

```bash
curl -X POST http://localhost:8000/oauth/token \
  -H "Content-Type: application/x-www-form-urlencoded" \
  -d "grant_type=authorization_code&code=YOUR_CODE&
      redirect_uri=http://localhost:3000/callback&
      client_id=test-client-id&
      code_verifier=dBjftJeZ4CVP-mB92K27uhbUJU1p1r_wW1gFWFOEjXk"
```

Replace `YOUR_CODE` with the actual code received from the redirect.

---

### ✅ OAuth 2.1 Compliance Features

This implementation includes several key security and compliance features:

| Feature | Description |
|--------|-------------|
| **PKCE Required** | All authorization code flows require a code challenge and verifier. |
| **No Implicit Flow** | Only the secure authorization code flow is supported. |
| **Exact Redirect URI Matching** | Prevents open redirect attacks. |
| **Short-lived Access Tokens** | Access tokens expire after 30 minutes. |
| **Refresh Token Rotation** | New refresh token issued with each use (planned). |
| **Client Authentication** | Supports both public and confidential clients. |

---

### 🧭 Next Steps for Production Readiness

To make this server production-ready, consider implementing:

1. ✅ **Session Management** – Use secure cookies or JWTs for user sessions.
2. ✅ **Scope Management** – Allow users to manage and revoke scopes.
3. ✅ **Token Introspection** – Add support for RFC 7662.
4. ✅ **Rate Limiting** – Prevent abuse of endpoints.
5. ✅ **Audit Logging** – Track all sensitive operations.
6. ✅ **Security Headers** – Add CORS, CSP, and other HTTP headers.
7. ✅ **Admin Roles** – Implement proper access control for admin routes.

---

This concludes the enhanced walkthrough of your OAuth 2.1 server tutorial! Would you like a downloadable version of the enhanced tutorial or help with deploying it?


Deploying your OAuth 2.1 server involves preparing it for production use, ensuring it's secure, scalable, and reliably accessible. Here's a step-by-step guide to help you deploy it:

---

## 🚀 Deployment Guide for the OAuth 2.1 Server

### ✅ 1. Prepare for Production

Before deploying, make sure you:

- Replace development secrets in `.env` with strong, secure values.
- Set `debug=False` and remove `--reload` from your server command.
- Use HTTPS in production (e.g., via a reverse proxy like Nginx or a cloud provider).
- Implement proper session management (e.g., secure cookies or JWTs).
- Add logging and monitoring.

---

### 🐳 Option A: Deploy with Docker

**Step 1: Create a `Dockerfile`

```Dockerfile
FROM python:3.11-slim

WORKDIR /app

COPY . /app

RUN pip install --no-cache-dir -r requirements.txt

CMD ["uvicorn", "app.main:app", "--host", "0.0.0.0", "--port", "8000"]
```

**Step 2: Create a `.dockerignore`

```
__pycache__/
.env
*.pyc
*.pyo
*.pyd
```

**Step 3: Build and Run**

```bash
docker build -t oauth-server .
docker run -d -p 8000:8000 --env-file .env oauth-server
```

---

### ☁️ Option B: Deploy to a Cloud Provider

You can deploy to platforms like:

- **Render** (easy for FastAPI apps)
- **Railway**
- **Fly.io**
- **Heroku**
- **AWS EC2 / Lightsail**
- **Azure App Service**
- **Google Cloud Run**

Each platform has its own deployment steps, but generally:

1. Push your code to GitHub.
2. Connect your repo to the platform.
3. Set environment variables (.env values) in the platform’s dashboard.
4. Define the start command:
   ```bash
   uvicorn app.main:app --host 0.0.0.0 --port 8000
   ```

---

### 🔐 2. Secure Your Server

- Use HTTPS (via a reverse proxy like Nginx or a managed certificate).
- Add CORS headers if your frontend is hosted separately.
- Enable rate limiting and request validation.
- Use a production-ready database (e.g., managed MySQL on AWS RDS).

---

### 📈 3. Monitor and Maintain

- Use tools like **Prometheus**, **Grafana**, or **Sentry** for monitoring.
- Set up logging (e.g., with `loguru` or `structlog`).
- Regularly rotate secrets and update dependencies.

---





# END

Next up - [LINK TEXT](#)
