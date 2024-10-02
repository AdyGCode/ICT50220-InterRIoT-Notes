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

# Python, FastAPI and Open Authentication

## Intermediate RIoT

### Session 11

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

# Setting Up

We will do this manually, then open PyCharm for development.

Open terminal with the Bash CLI.

> **Note:**
> If you need to set up Bash and aliases then please refer to:
> - Adding Bash to Windows Terminal [link]
> - Aliases to simplify your work with Bash [link]


Ensure you are in your `Source/Repos` folder, and replace the `xxx` with your initials in each command.

## Clone & Initialise with Windows Terminal and Git Bash

If you haven't done so... open your Windows Terminal and start a new Bash CLI.

Make sure you are in your `Source/Repos` folder.

```shell
git clone https://github.com/AdyGCode/InterRIoT-2024S2-fastapi-templating.git xxx-fastapi-security-oauth2

cd xxx-fastapi-security-oauth/
git remove origin

python -m venv .venv
source ./.venv/Scripts/activate
npm install 
npx tailwindcss -i src/source.css -o static/css/site.css --watch
```

For Linux and Mac use:

```shell
git clone https://github.com/AdyGCode/InterRIoT-2024S2-fastapi-templating.git xxx-fastapi-security-oauth

cd xxx-fastapi-security-oauth/
git remove origin

python -m venv .venv
source ./.venv/bin/activate
npm install 
npx tailwindcss -i src/source.css -o static/css/site.css --watch
```

> **Note:** You will need to add your own remote by either:
> (a) first creating an empty GitHub repository, then setting the remote to your own repo, and pushing the code up
> or
> (b) using PyCharm's Git and GitHub integrations to share the repo to your GitHub account.
> 
> It is left to you to do this.

Open a second Bash CLI (or split the screen as you wish).

In this terminal, first make sure you are in your `Source/Repos` folder.

Then run:

```bash
cd xxx-fastapi-security-oauth/
source ./.venv/Scripts/activate
pip install -r requirements.txt

fastapi dev app.py
```

You should be able to visit [`http://127.0.0.1:8000`](http://127.0.0.1:8000) to see the base application.

![](CleanShot%202024-09-27%20at%2017.05.06@2x.png)

## Change XXX to Your Initials

Remember that anywhere we have **`XXX`** should be replaces by **your initials**.


## Update the Base template

Edit the `base.html` file and make the following updates:

Update the `title` element:

```{html icon}
 <title>
  {% block title %}DEFAULT TITLE{% endblock %} | XXX | InterRIoT
</title>
```

Rename the `main` block to `page_content`.

Add the following **before** the footer component include line:

```html
<div class="container text-zinc-400 mx-auto mb-6 flex flex-col space-y-6">
    {% block page_footer %}{% endblock %}
</div>
```

### Select a FastAPI icon

Open the [S11 Fast API Logo Options](../Session-11/S11-FastAPI-Logo-Options.md) Markdown document, and select the FastAPI Logo variant you wish to use.

You are NOT to use the Standard Green version, that is for these notes only.

Update the `header.html` to use your logo choice... below is an example with the standard FastAPI green:

```html
<h1 class="self-center text-xl font-semibold whitespace-nowrap flex flex-row-reverse content-center">
    <span class="pl-2">FastAPI</span>
    <img src="{{ url_for('img', path='FastAPI-Standard.png') }}" class="max-w-6 max-h-6"/>
</h1>
```

Update the `app.py` file to add a new `app.mount()` with settings below:

- endpoint will be `/img`
- directory of `static/img`
- name will be `img`


Refresh your home page and check all is working (You may need to clear your browser cache for it to pick up the changes).



## Update Home page (and About)

Edit the Home page (`templates/pages/home.html`) to read:

```html
{% extends "base.html" %}

{% block title %}Home{% endblock title %}

{% block page_title %}
<h2 class="mx-4 
	       text-3xl text-zinc-700 text-left 
	       font-medium uppercase title-font">
    <i class="fa-solid fa-home text-zinc-500"></i>
    Fast API and OAuth
</h2>
{% endblock %}

{% block page_content %}
<section class="container mx-auto border grow 
			    h-full shadow-md p-4 pb-8 
			    rounded space-y-2">
    <h2 class="text-2xl text-zinc-50 bg-zinc-600 
			   p-4 pb-6 mb-6 -mx-4 -mt-4 rounded-t">
        Session Control using Open Authentication 
    </h2>

    <h3 class="text-xl text-zinc-500">To Do Checklist:</h3>
    <div class="text-zinc-700 
			    grid grid-cols-6 md:grid-cols-12
			    items-start gap-y-8">
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
            <p>Update the About page so the heading is "About this Security Demo 2 App"</p>
        </div>

        <i class="text-2xl text-red-700 fa-regular fa-square min-w-6 col-span-1"></i>
        <div class="col-span-5 md:col-span-11">
            <h4 class="font-bold">Step 2:</h4>
            <p>...</p>
        </div>

        <i class="text-2xl text-red-700 fa-regular fa-square min-w-6 col-span-1"></i>
        <div class="col-span-5 md:col-span-11">
            <h4 class="font-bold">Step 3:</h4>
            <p>...</p>
        </div>

        <i class="text-2xl text-red-700 fa-regular fa-square min-w-6 col-span-1"></i>
        <div class="col-span-5 md:col-span-11">
            <h4 class="font-bold">Step 4:</h4>
            <p>...</p>
        </div>

        <i class="text-2xl text-red-700 fa-regular fa-square min-w-6 col-span-1"></i>
        <div class="col-span-5 md:col-span-11">
            <h4 class="font-bold">Step 5:</h4>
            <p>...</p>
        </div>

    </div>

</section>
{% endblock %}
```

### Update the About page

On the about page add "OAuth (via Python JOSE)" with a Python icon to the list of technologies.

## Add Required Packages for OAuth

Open a _third_ Bash CLI (or split the screen as you wish).

In this terminal, first make sure you are in your `Source/Repos` folder.

As before, we need to activate Python in the application's folder.

Run the following:

```shell
cd xxx-fastapi-security-oauth/
source ./.venv/Scripts/activate
```

Now we install the `requests`, `python-jose` & `python-multipart` packages:

```shell
pip install python-jose python-multipart requests
```

Let's backup the requirements document, and then freeze all the updated packages into the requirements file:

```shell
cp requirements.txt requirements-old.txt
pip freeze > requirements.txt
```


## Create policies files and folders

Before we add the Casbin code, create a folder (and required files) for the policies

```bash
mkdir policies
touch policies/{rebac_model.conf,rebac_policy.csv,.gitignore}
```

## Updating the Application

We now need to do a little work on the `app.py` file before we start.

Open the file and start by reorganising/removing/adding lines at the top of the file:

```python
import os  
from pathlib import Path  
from datetime import timedelta, date, datetime  
import dateutil  

from dotenv import load_dotenv  
  
import requests  
from jose import jwt
from fastapi import FastAPI, Request, HTTPException, Depends  
from fastapi.responses import HTMLResponse  
from fastapi.staticfiles import StaticFiles  
from fastapi.templating import Jinja2Templates  
from fastapi.security import OAuth2PasswordBearer  

```

These are the various packages/libraries we will be using in our application.


### Reorganise Templates and other Items

Next we put all the parts for the application to be loaded, and the static files to be accessed.

Open the `app.py` file and update the main section to read:

```python
app = FastAPI(title="FastAPI Templating")  
oauth2_scheme = OAuth2PasswordBearer(tokenUrl="token")  
load_dotenv(".env")

app.mount("/static", StaticFiles(directory="static"), name="static")
app.mount("/css", StaticFiles(directory="static/css"), name="css")
app.mount("/js", StaticFiles(directory="static/js"), name="js")

# Application Constants
BASE_PATH = Path(__file__).resolve().parent
TEMPLATES = Jinja2Templates(directory="templates")
LOGGED_IN = "Logged in"

```

# What is Open Authentication



# Create Google OAuth2 Application

You will need a `google.com` account for this.

Feel free to create an account and use the TAFE email as a backup...

We will wait for you...

![](CleanShot%202024-09-27%20at%2014.59.24.png)

Ok now that is completed...

Whilst logged into your Google Account, click this link to open the Google Cloud Console: [https://console.cloud.google.com/](https://console.cloud.google.com/).

Once you have logged in you should be presented with a Google Cloud console.

![](CleanShot%202024-09-27%20at%2015.04.22.png)

Click on Select a project

![](CleanShot%202024-09-27%20at%2015.02.56.png)


Then on the dialog box click the New Project link

![](CleanShot%202024-09-27%20at%2015.03.15.png)

The dialog will now as for you to complete teh detailed for the project.

![](CleanShot%202024-09-27%20at%2015.06.53.png)

We will name ours `ICT50220-InterRIoT-24S2`

> **Note:** The 24S2 will be 25S1, 25S2, 26S1, etc as each year and semester changes

![](CleanShot%202024-09-27%20at%2015.09.15.png)

We are not going to create an organisation for this example, so we are now able to continue and click create.

![](CleanShot%202024-09-27%20at%2015.10.24.png)

Once created you may select your project, and you'll be welcomed by the project dashboard.

![](../assets/CleanShot%202024-09-27%20at%2015.11.06.png)

Scroll down until you find the Getting Started and the API "Explore and enable APIs".

![](CleanShot%202024-09-27%20at%2015.20.21.png)

Click this to go to the APIs screen, and click the Credentials menu option.

![](CleanShot%202024-09-27%20at%2015.21.46.png)

Now click on the Create Credentials link to open up a list of options...

![](CleanShot%202024-09-27%20at%2015.22.40.png)

Select the OAuth Client ID option from the drop down...

![](CleanShot%202024-09-27%20at%2015.23.59.png)

It then tells you about creating the consent screen for your applicaiton...

![](CleanShot%202024-09-27%20at%2015.25.30.png)

To the right a button is waiting for you to click...

![](CleanShot%202024-09-27%20at%2015.26.14.png)

Now we get to set the application settings.

Remember we will be working with our local system, not on a remote, so we will use `127.0.0.1` or `localhost` as the hostname, and the port will be `8000`.

For the purposes of our work, we will use the External option... note that we could have set up an organisation and added other people to the organisation.

![](CleanShot%202024-09-27%20at%2015.28.54.png)

So it's time to fill out the details for the Application...

![](CleanShot%202024-09-27%20at%2015.30.10.png)

The App Name should be 


The User Support Email should be your TAFE Email Address, or the Gmail account address.


![](CleanShot%202024-09-27%20at%2016.50.57.png)

The logo - we have created several variants FastAPI logos to use for this example... lots to choose from here... [S11-FastAPI-Logo-Options](Session-11/S11-FastAPI-Logo-Options.md).

![](CleanShot%202024-09-27%20at%2017.15.51.png)

In the App Domain section we need to add the details as shown:

| Item                              | Value                           | Direct Link (for testing)     |
| --------------------------------- | ------------------------------- | ----------------------------- |
| Application home page             | `http://127.0.0.1:8000`         | http://127.0.0.1:8000         |
| Application privacy link          | `http://127.0.0.1:8000/privacy` | http://127.0.0.1:8000/privacy |
| Application Terms of Service link | `http://127.0.0.1:8000/terms`   | http://127.0.0.1:8000/terms   |


Once you have added this, and the developer's email (your email) then we are ready to click save.

![](CleanShot%202024-09-27%20at%2018.10.55.png)

Add your email address, plus the lecturer's Gmail Account email.

![](CleanShot%202024-09-27%20at%2018.21.57.png)





# Conclusion

There are many flaws in this tutorial, such as the routes not being in separate files, but the main purpose is to
discover how to use Policy Based Access Control with FastAPI.

# END

Next up - [LINK TEXT](#)
