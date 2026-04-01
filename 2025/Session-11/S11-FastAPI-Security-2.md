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

# Python, FastAPI and PBAC

## Intermediate RIoT

### Session 10

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

# Resources Needed

- Python 3.10+
- PyCharm Professional 2024.2+
- The demo FastAPI/Jinja2 Application


# Step 0 - Setting Up

We will do this manually, then open PyCharm for development.

Open terminal with the Bash CLI.

> **Note:**
> If you need to set up Bash and aliases then please refer to:
> - Adding Bash to Windows Terminal [link]
> - Aliases to simplify your work with Bash [link]


Ensure you are in your Source/Repos folder, and replace the `xxx` with your initials in each command.

## Clone & Initialise with Windows Terminal and Git Bash

If you haven't done so... open your Windows Terminal and start a new Bash CLI.

Make sure you are in your `Source/Repos` folder.

```shell
git clone https://github.com/AdyGCode/InterRIoT-2024S2-fastapi-templating.git xxx-fastapi-security-1

cd xxx-fastapi-security-1/

python -m venv .venv
source ./.venv/Scripts/activate
npm install 
npx tailwindcss -i src/source.css -o static/css/site.css --watch
```

For Linux and Mac use:

```shell
git clone https://github.com/AdyGCode/InterRIoT-2024S2-fastapi-templating.git xxx-fastapi-security-1

cd xxx-fastapi-security-1/

python -m venv .venv
source ./.venv/bin/activate
npm install 
npx tailwindcss -i src/source.css -o static/css/site.css --watch
```

Open a second Bash CLI (or split the screen as you wish).

In this terminal, first make sure you are in your `Source/Repos` folder.

Then run:

```bash
cd xxx-fastapi-security-1/
source ./.venv/Scripts/activate
pip install -r requirements.txt

fastapi dev app.py
```

You should be able to visit [`http://127.0.0.1:8000`](http://127.0.0.1:8000) to see the base application.

# Step 1 - Update Home page (and About)

Edit the Home page (`templates/pages/home.html`) to read:

```html
{% extends "base.html" %}

{% block title %}Home | XXX{% endblock title %}

{% block page_title %}
<h2 class="mx-4 text-3xl text-zinc-700 text-left font-medium uppercase title-font">
    <i class="fa-solid fa-home text-zinc-500"></i>
    Fast API and Access Control
</h2>
{% endblock %}

{% block main %}
<section class="container mx-auto border grow h-full shadow-md p-4 pb-8 rounded space-y-2">
    <h2 class="text-2xl text-zinc-50 bg-zinc-600 p-4 pb-6 mb-6 -mx-4 -mt-4 rounded-t">
        Attribute/Policy Based Access Control
    </h2>

    <h3 class="text-xl text-zinc-500">To Do Checklist:</h3>
    <div class="text-zinc-700 grid grid-cols-6 md:grid-cols-12 items-start gap-y-8">
        <i class="text-2xl text-green-700 fa-regular fa-check-square min-w-6 col-span-1"></i>

        <div class="col-span-5 md:col-span-11 space-y-1">
            <h4 class="font-bold">Step 0:</h4>

            <p>
                Each time you complete a stage, before commit, you should update the square/box icon from
                <code>fa-square</code> and from red <i class="text-red-700 fa-regular fa-square"></i> to
                <code>fa-check-square</code> and green <i class="text-green-700 fa-regular fa-check-square"></i>.
            </p>
        </div>

        <i class="text-2xl text-red-700 fa-regular fa-square min-w-6 col-span-1 "></i>
        <div class="col-span-5 md:col-span-11 space-y-1">
            <h4 class="font-bold">Step 1:</h4>
            <p>
                Update the title to use your initials in the form `PAGE | XXX`.
                This page will be `Home | XXX` and About will be `About | XXX`.
            </p>
            <p>Update the About page so the heading is "About this Security Demo 1 App"</p>
        </div>

        <i class="text-2xl text-red-700 fa-regular fa-square min-w-6 col-span-1"></i>
        <div class="col-span-5 md:col-span-11">
            <h4 class="font-bold">Step 2:</h4>
            <p>Update the Application file, reorganising existing code</p>
        </div>

        <i class="text-2xl text-red-700 fa-regular fa-square min-w-6 col-span-1"></i>
        <div class="col-span-5 md:col-span-11">
            <h4 class="font-bold">Step 3:</h4>
            <p>Add Enforcer and BasicAuth</p>
        </div>

        <i class="text-2xl text-red-700 fa-regular fa-square min-w-6 col-span-1"></i>
        <div class="col-span-5 md:col-span-11">
            <h4 class="font-bold">Step 4:</h4>
            <p>Create PBAC Models and Policies, and Anonymous Endpoints</p>
        </div>

        <i class="text-2xl text-red-700 fa-regular fa-square min-w-6 col-span-1"></i>
        <div class="col-span-5 md:col-span-11">
            <h4 class="font-bold">Step 5:</h4>
            <p>Testing the Endpoint Policies and Models</p>
        </div>

    </div>

</section>
{% endblock %}
```

## Update the About page

On the about page add "Casbin (via fastapi-authz)" with a Python icon to the list of technologies.

# Step 2 - Update the Application

## Add Casbin Package

Open a _third_ Bash CLI (or split the screen as you wish).

In this terminal, first make sure you are in your `Source/Repos` folder.

As before, we need to activate Python in the application's folder.

Run the following:

```shell
cd xxx-fastapi-security-1/
source ./.venv/Scripts/activate
```

Now we install `Casbin` & the `fastapi-authz` package:

```shell
pip install casbin fastapi-authz
```

## Create policies files and folders

Before we add the Casbin code, create a folder (and required files) for the policies

```bash
mkdir policies
touch policies/{rebac_model.conf,rebac_policy.csv,.gitignore}
```

## Refactor the Application Code

We now need to do a little work on the `app.py` file before we start.

Open the file and start by reorganising/adding lines at the top of the file:

```python
import base64
import binascii
from pathlib import Path

import casbin
import uvicorn

from fastapi import FastAPI, Request, HTTPException
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates

from starlette.authentication import AuthenticationBackend, AuthenticationError, SimpleUser, AuthCredentials
from starlette.middleware.authentication import AuthenticationMiddleware

from fastapi_authz import CasbinMiddleware

from basicauth import BasicAuth
```

These are the various packages/libraries we will be using in our application.

The BasicAuth module will be created in a little while...

## Refactor Templates and other Items

Next we put all the parts for the application to be loaded, and the static files to be accessed:

```python

BASE_PATH = Path(__file__).resolve().parent

app = FastAPI(title="FastAPI Templating")

app.mount("/static", StaticFiles(directory="static"), name="static")
app.mount("/css", StaticFiles(directory="static/css"), name="css")
app.mount("/js", StaticFiles(directory="static/js"), name="js")

TEMPLATES = Jinja2Templates(directory="templates")

```

# Step 3 - Add Enforcer and BasicAuth 

## Create a BasicAuth module

Create a new python file named `basicauth.py` in the same folder as the `app.py` file.

In the file add:

```python
# -------------------------------------------------------------------
# Project:    InterRIoT-2024S2-fastapi-security-1
# Filename:   basicauth.py
# Location:   ./
# Author:     Adrian Gould <adrian.gould@nmtafe.wa.edu.au>
# Created:    2024-09-24
# Purpose:
#    To provide a basic authentication mechanism for PBAC demo
#    
# ---------------------------------------------------------------------
import base64
import binascii

from starlette.authentication import ( 
    AuthenticationBackend, 
    AuthenticationError, 
    AuthCredentials, 
    SimpleUser
)


class BasicAuth(AuthenticationBackend):
    async def authenticate(self, request):
        if "Authorization" not in request.headers:
            return None

        auth = request.headers["Authorization"]
        
        try:
            scheme, credentials = auth.split()
            decoded = base64.b64decode(credentials).decode("ascii")
        except (ValueError, UnicodeDecodeError, binascii.Error):
            raise AuthenticationError("Invalid basic auth credentials")

        username, _, password = decoded.partition(":")
        return AuthCredentials(["authenticated"]), SimpleUser(username)

```

## Add the Enforcer...

Back to `app.py` and we next add, before the routes, the following:

```python
enforcer = casbin.Enforcer('./policies/rbac_model.conf', './policies/rbac_policy.csv')

app.add_middleware(CasbinMiddleware, enforcer=enforcer)
app.add_middleware(AuthenticationMiddleware, backend=BasicAuth())
```

You will find that FastAPI will be craving attention with loads of errors.

This is because we have not created our policies and models.

# Step 4 - PBAC Policy & Model Files

## Model File

Open the `rbac_model.conf` file and add:

```ini
[request_definition]
r = sub, obj, act

[policy_definition]
p = sub, obj, act

[role_definition]
g = _, _

[policy_effect]
e = some(where (p.eft == allow))

[matchers]
m = (p.sub == "*" || g(r.sub, p.sub)) && (r.obj == p.obj || keyMatch(r.obj, p.obj)) && (p.act == "*" || r.act == p.act)
m = g(r.sub, p.sub) && keyMatch(r.obj, p.obj) && (r.act == p.act || p.act == "*")

```

> **Warning:** It is important that the long matchers lines are kept on one line each,
> AND that spacing is exactly correct!

## Policy file

Likewise open the `rbac_policy.csv` file and add:

```csv
p, alice, /dataset1/*, GET
p, alice, /dataset1/resource1, POST
p, bob, /dataset2/resource1, *
p, bob, /dataset2/resource2, GET
p, bob, /dataset2/folder1/*, POST
p, dataset1_admin, /dataset1/*, *

p, anonymous, /, GET

g, cathy, dataset1_admin
```

Let's look at an example line:

```csv
p, alice, book, read
```

This corresponds to:

| item    | example | what it means                               |
|---------|---------|---------------------------------------------|
| policy  | p       | the following items determine the policy    |
| subject | alice   | when alice is authorised, she may...        |
| object  | book    | access the book resource (endpoint) for ... | 
| action  | read    | read access                                 |

## Check the Application

Stop the FastAPI application (<kbd>CTRL</kbd>+<kbd>C</kbd>), and restart it using `fastapi dev app.py`.

Try accessing the home page... did it load correctly?

Check the "log" from FastCLI on the CLI... it will have lines like this:

```text
INFO:     127.0.0.1:63944 - "GET / HTTP/1.1" 200 OK
INFO:     127.0.0.1:63944 - "GET /static/css/site.css HTTP/1.1" 403 Forbidden
INFO:     127.0.0.1:63945 - "GET /static/js/menu.js HTTP/1.1" 403 Forbidden
```

OOPS! we got our static files blocked :unsmiley:

## Adding Static File Policies

OK, so we need to update the policies to fix this.

Open the `rbac_policy.csv` file and add immediately after the first anonymous line...

```csv
p, anonymous, /static/*, GET
```

This corresponds to:

| item    | example   | what it means                                     |
|---------|-----------|---------------------------------------------------|
| policy  | p         | The policy is...                                  |
| subject | anonymous | when any 'unauthorised' client accesses           |
| object  | /static/* | the static folder and all items within the folder | 
| action  | GET       | using the GET method                              |

Let's also make sure that we can access the About page:

```csv
p, anonymous, /about, GET
```

## Try accessing the pages...

Did you manage to see the About and Home pages?

No?

# Casbin & Restarting the Application

> **Note:** This is a little frustrating, but as policies are loaded into memory on application start,
> we need to restart the FastAPI application each time.

Stop the FastAPI application (<kbd>CTRL</kbd>+<kbd>C</kbd>), and restart it using `fastapi dev app.py`.

You may also use "uvicorn" to access the FastAPI application:

```shell
uvicorn app:app --reload
```

# FastAPI Creates API Documentation!

Try accessing the following:

- [http://127.0.0.1:8000/docs](http://127.0.0.1:8000/docs)

Yep it failed as we do not have a policy to allow access to it.

Add the lines below, one to allow access to the docs endpoint, the other to allow access to the OpenAPI JSON file that
is dynamically updated for us.

```csv
p, anonymous, /docs, GET
p, anonymous, /openapi.json, GET
```

> **Remember:** Restart the server!

Try accessing the endpoint again...

# Testing API Endpoints

To test the non HTML (API) endpoints we will use the `curl` command.

GET Method requests are in the form:

```shell
curl -i -u USERNAME:PASSWORD URI:PORT/RESOURCE_PATH
```

POST method requests are in the form:"

```shell
curl -i -u USERNAME:PASSWORD URI:PORT/RESOURCE_PATH --request POST --json DATA_TO_POST
```

| Switch              | Meaning                                                                                                                                                            |
|---------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `-i` or `--include` | include response headers in output                                                                                                                                 |
| `-u` or `--user`    | username and password used in 'basic' authentication                                                                                                               |
| `--request`         | followed by the HTTP Request type being made - GET, POST, PUT, PATCH, DELETE                                                                                       |
| `--json`            | followed by JSON_DATA, sends data as JSON, replacing need to include  `--data [arg] --header "Content-Type: application/json" --header "Accept: application/json"` |

> **Note:** you can find more about the command line 'switched' by using
> ```shell
> curl --manual | more
> ```


The table below shows the tests you will run:

| USERNAME | PASSWORD | URI                | PORT   | Method | RESOURCE_PATH            | DATA_TO_POST       |
|----------|----------|--------------------|--------|--------|--------------------------|--------------------|
|          |          | `http://127.0.0.1` | `8000` | GET    | `/`                      |                    |
| alice    | password | `http://127.0.0.1` | `8000` | POST   | `/dataset1/resource1`    | `{"name":"Alice"}` |
| alice    | password | `http://127.0.0.1` | `8000` | GET    | `/dataset1`              |                    |
| alice    | password | `http://127.0.0.1` | `8000` | GET    | `/dataset2/resource2`    |                    |
| bob      | secret01 | `http://127.0.0.1` | `8000` | GET    | `/dataset1`              |                    |
| bob      | secret01 | `http://127.0.0.1` | `8000` | POST   | `/dataset1/resource1`    | `{"name":"Bob"}`   |
| bob      | secret01 | `http://127.0.0.1` | `8000` | GET    | `/dataset2/resource2`    |                    |
| cathy    | password | `http://127.0.0.1` | `8000` | POST   | `/api/v1/dataset1`       | `{"name":"Cathy"}` |
| cathy    | password | `http://127.0.0.1` | `8000` | POST   | `/api/v1/dataset1/dummy` | `{"name":"Cathy"}` |

> **Note about guest users:**
>
> A blank username and password means it is "any anonymous user".

> **Note about POST/PUT/PATCH:**
>
> When POST (or PUT, or PATCH) methods are called, you need to
> escape the `"` (quotes) in the CLI.
>
> e.g. `"{\"name\":\"Anonymous\"}"`

Here are some example curl requests to POST JSON data:

```shell
curl -i -u alice:password http://127.0.0.1:8000/api/v1/dataset1/resource1 --request POST --json "{\"name\":\"Alice\"}"

curl -i -u bob:secret01 http://127.0.0.1:8000/api/v1/dataset2/resource1 --request POST --json "{\"name\":\"Bob\"}"
```

# Conclusion

There are many flaws in this tutorial, such as the routes not being in separate files, but the main purpose is to
discover how to use Policy Based Access Control with FastAPI.

# END

Next up - [LINK TEXT](#)
