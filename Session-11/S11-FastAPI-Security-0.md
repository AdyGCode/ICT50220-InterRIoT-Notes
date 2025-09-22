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
p, anonymous, /, GET
p, anonymous, /docs, GET
p, anonymous, /openapi.json, GET

p, alice, /dataset1/*, GET
p, alice, /dataset1/create, POST
p, alice, /dataset1/update/*, PUT

p, bob, /dataset2/resource1, *
p, bob, /dataset2/resource2, GET
p, bob, /dataset2/folder1/*, POST

p, dataset1_admin, /dataset1/*, *

p, *, /login, *

g, cathy, dataset1_admin

```

## Step 3: Create the main application

Create a file named `main.py` with the following content:

```python
# RBAC Demo using Casbin and FastAPI

# Imports -------------------------------------------------
import casbin
from fastapi import FastAPI, Depends, HTTPException
from fastapi.security import HTTPBearer, HTTPAuthorizationCredentials
from fastapi.responses import JSONResponse
from starlette.requests import Request

```

This imports the requirements for the application.

```python
# Create & configure app ----------------------------------
app = FastAPI()
enforcer = casbin.Enforcer("model.conf", "policy.csv")
security = HTTPBearer()

```

```python
# Functions -----------------------------------------------
def get_current_user(credentials: HTTPAuthorizationCredentials = Depends(security)):
    # VERY SIMPLIFIED! Do not use in production.
    # You should validate the token and return the user
    # in a real application. In this example we will use the
    # token as the username
    return credentials.credentials

```

### Middleware

```python
# Middleware ----------------------------------------------
@app.middleware("http")
async def enforce_policy(request: Request, call_next):
    if request.url.path == "/login":
        return await call_next(request)

    try:
        credentials = await security(request)
        user = credentials.credentials
    except HTTPException as e:
        user = "anonymous"

    policy = enforcer.enforce(user, request.url.path, request.method)
    if policy in (None, False):
        return JSONResponse(status_code=403, content={"message": "Forbidden"})
    else:
        return await call_next(request)

```

### Main Application Code / Endpoints

Start with the "root" or "home" endpoint.

This is accessed using http://FQDN/ where FQDN is localhost:8000 when we are testing/developing.

```python
# Endpoints -----------------------------------------------
@app.get("/")
async def root():
    return {"message": "Welcome to PBAC Tutorial!"}


```

Next we add the login endpoint. At the moment this only responds with JSOn to say that this accesses the login endpoint.
```python

@app.get("/login")
async def login():
    return {"message": "This is the login page"}

```

Now we will add the first of the dataset1 endpoints: GET

```python

@app.get("/dataset1/{resource}")
async def dataset1(resource: str, user: str = Depends(get_current_user)):
    """
    Provides access to a single dataset1 resource identified by {resource}
    """
    return {"message": f"{user} is accessing dataset1 resource: {resource}"}

```


```python
@app.post("/dataset1/{resource}")
async def dataset1_post(resource: str, user: str = Depends(get_current_user)):
    return {"message": f"{user} is posting to dataset1 resource: {resource}"}

```

```python
@app.put("/dataset1/{resource}")
async def dataset1_put(resource: str, user: str = Depends(get_current_user)):
    return {"message": f"{user} is putting to dataset1 resource: {resource}"}
```

```python
@app.get("/dataset2/{resource}")
async def dataset2_get(resource: str, user: str = Depends(get_current_user)):
    return {"message": f"{user} is accessing dataset2 resource: {resource}"}

```

```python
@app.post("/dataset2/{resource}")
async def dataset2_post(resource: str, user: str = Depends(get_current_user)):
    return {"message": f"{user} is posting to dataset2 resource: {resource}"}
```

```python

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

4. Try to POST to dataset1/create as Alice (allowed):
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
