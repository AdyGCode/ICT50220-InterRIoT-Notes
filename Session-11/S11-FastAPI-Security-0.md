# Policy Based Access Control Tutorial with Python, Casbin, and FastAPI

Created by Claude.AI

https://claude.site/artifacts/d84d01c1-6217-4776-a8b0-f48e9c7ef2e0


## Prerequisites

- Python 3.10
- Casbin 1.36
- FastAPI 0.114

## Step 1: Set up the project

First, create a new directory for your project and set up a virtual environment:

```bash
mkdir pbac_tutorial
cd pbac_tutorial
python -m venv venv
source venv/bin/activate  # On Windows, use `venv\Scripts\activate`
```

Install the required packages:

```bash
pip install casbin==1.36 fastapi==0.114 uvicorn
```

## Step 2: Create the Casbin model and policy files

Create a file named `model.conf` with the following content:

```
[request_definition]
r = sub, obj, act

[policy_definition]
p = sub, obj, act

[role_definition]
g = _, _

[policy_effect]
e = some(where (p.eft == allow))

[matchers]
m = g(r.sub, p.sub) && keyMatch(r.obj, p.obj) && (r.act == p.act || p.act == "*")
```

Create a file named `policy.csv` with the policies you provided:

```
p, alice, /dataset1/*, GET
p, alice, /dataset1/resource1, POST
p, bob, /dataset2/resource1, *
p, bob, /dataset2/resource2, GET
p, bob, /dataset2/folder1/*, POST
p, dataset1_admin, /dataset1/*, *
p, *, /login, *
p, anonymous, /, GET

g, cathy, dataset1_admin
```

## Step 3: Create the main application

Create a file named `main.py` with the following content:

```python
import casbin
from fastapi import FastAPI, Depends, HTTPException
from fastapi.security import HTTPBearer, HTTPAuthorizationCredentials
from starlette.requests import Request

app = FastAPI()
enforcer = casbin.Enforcer("model.conf", "policy.csv")
security = HTTPBearer()

def get_current_user(credentials: HTTPAuthorizationCredentials = Depends(security)):
    # In a real application, you would validate the token and return the user
    # For this example, we'll just use the token as the username
    return credentials.credentials

@app.middleware("http")
async def enforce_policy(request: Request, call_next):
    # Skip authorization for login endpoint
    if request.url.path == "/login":
        return await call_next(request)

    try:
        credentials = await security(request)
        user = credentials.credentials
    except HTTPException:
        user = "anonymous"

    if enforcer.enforce(user, request.url.path, request.method):
        return await call_next(request)
    else:
        raise HTTPException(status_code=403, detail="Forbidden")

@app.get("/")
async def root():
    return {"message": "Welcome to the PBAC tutorial!"}

@app.get("/login")
async def login():
    return {"message": "This is the login page"}

@app.get("/dataset1/{resource}")
async def dataset1(resource: str, user: str = Depends(get_current_user)):
    return {"message": f"Accessing dataset1 resource: {resource}"}

@app.post("/dataset1/{resource}")
async def dataset1_post(resource: str, user: str = Depends(get_current_user)):
    return {"message": f"Posting to dataset1 resource: {resource}"}

@app.get("/dataset2/{resource}")
async def dataset2(resource: str, user: str = Depends(get_current_user)):
    return {"message": f"Accessing dataset2 resource: {resource}"}

@app.post("/dataset2/{resource}")
async def dataset2_post(resource: str, user: str = Depends(get_current_user)):
    return {"message": f"Posting to dataset2 resource: {resource}"}

if __name__ == "__main__":
    import uvicorn
    uvicorn.run(app, host="0.0.0.0", port=8000)
```

## Step 4: Run the application

Run the application using the following command:

```bash
python main.py
```

The server will start running on `http://localhost:8000`.

## Step 5: Test the application

You can use tools like `curl` or Postman to test the application. Here are some example requests:

1. Access the root path (allowed for anonymous users):
   ```
   curl http://localhost:8000/
   ```

2. Access the login page (allowed for all users):
   ```
   curl http://localhost:8000/login
   ```

3. Access dataset1 as Alice (allowed):
   ```
   curl -H "Authorization: Bearer alice" http://localhost:8000/dataset1/resource1
   ```

4. Try to POST to dataset1/resource1 as Alice (allowed):
   ```
   curl -X POST -H "Authorization: Bearer alice" http://localhost:8000/dataset1/resource1
   ```

5. Try to access dataset2 as Alice (forbidden):
   ```
   curl -H "Authorization: Bearer alice" http://localhost:8000/dataset2/resource1
   ```

6. Access dataset2 as Bob (allowed):
   ```
   curl -H "Authorization: Bearer bob" http://localhost:8000/dataset2/resource1
   ```

7. Access dataset1 as Cathy (allowed due to role inheritance):
   ```
   curl -H "Authorization: Bearer cathy" http://localhost:8000/dataset1/resource1
   ```

## Conclusion

This tutorial demonstrates how to implement Policy Based Access Control using Python, Casbin, and FastAPI. The application enforces the specified policies, allowing or denying access based on the user's role and the requested resource.

To further enhance this application, you could:

1. Implement proper user authentication
2. Add more endpoints and resources
3. Create an interface for managing policies dynamically
4. Implement logging for access attempts and policy changes

Remember to always follow security best practices when implementing access control in production environments.
