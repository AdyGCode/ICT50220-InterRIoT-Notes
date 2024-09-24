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

# Python, FastAPI and Templating

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
-

Chapter content

## Setting Up

We will do this manually, then open PyCharm for development.

Open terminal with the Bash CLI.

> **Note:**
> If you need to set up Bash and aliases then please refer to:
> - Adding Bash to Windows Terminal [link]
> - Aliases to simplify your work with Bash [link]


Ensure you are in your Source/Repos folder.

Create project folder, and change into it:

```shell
mkdir xxx-fastapi-templating
cd xxx-fastapi-templating
```

> **Remember:** `xxx` is replaced by your initials!

Create python virtual environment, and activate it:

```bash
python -m venv .venv
source ./venv/Scripts/activate
```

Create base files & folders:

```bash
mkdir templates static src 
touch ReadMe.md .gitignore src/source.css
touch {src,templates,static}/.gitignore
```

Initialise version control

```bash
git init .
git add src templates static
git add ReadMe.md .gitignore
git status
```

Use the git status command to check that the following are new files:

```text
new file:   .gitignore
new file:   ReadMe.md
new file:   src/.gitignore
new file:   src/source.css
new file:   static/.gitignore
new file:   templates/.gitignore
```

# PyCharm, Plugins and The Project

Open PyCharm professional and then use the Menu->File->Open to open the `xxx-fastapi-templating` folder as a new
project.

## Adding Plugins

Once the project is open, Use <kbd>CTRL</kbd>+<kbd>ALT</kbd>+<kbd>S</kbd> to open the settings (<kbd>
CMD</kbd>+<kbd>,</kbd> on MacOS).

Locate the Plugins section on the left side of the dialog.

In the Marketplace tab, locate and install the following plugins:

- .ignore
- Rainbow Brackets
- .env
- Key Promoter X
- CSV Editor
- Conventional Commit
- Pydantic
- Python Security

You will need to restart you PyCharm Professional IDE.

## Update the Git Ignore file

Now we need to update the `.gitignore` file.

Use the following steps:

- click on the `.gitignore` file in the root folder.
- Menu -> File -> New -> `.ignore` -> `.gitignore`

Add the following templates:

- Backup
- JetBrains+all
- JetBrains+iml
- Linux
- MacOS
- Windows
- Python
- VirtualEnv
- VisualStudioCode
- esp-idf
- Node

We suggest generating without duplicates and optionally without comments and empty lines.

Update the stashed files in git (including your PyCharm settings):

```shell
git add .gitignore .idea

git status
```

You should now see these listed as new files:

```text
.gitignore
.idea/.gitignore
.idea/inspectionProfiles/profiles_settings.xml
.idea/misc.xml
.idea/modules.xml
.idea/vcs.xml
.idea/xxx-fastapi-templating.iml
ReadMe.md
src/.gitignore
src/source.css
static/.gitignore
templates/.gitignore
```

Now commit these files:

```bash
git commit -m "init: Set Up Project"
```

# Set Up FastAPI & Jinja2

Install FastAPI and Jinja2 using:

```shell
pip install "fastapi[standard]" jinja2
```

Create a `requirements.txt` file using:

```shell
pip freeze > requirements.txt
```

# Set Up Tailwind CSS & FontAwesome

Seeing as we already have encountered TailwindCSS we may as well also include it in this project.

We will also add Font Awesome, a brilliant web icon collection providing 32000 icons of which over 2500 are free to use.

```shell
npm install tailwindcss
```

Initialise the TailwindCSS configuration file:

```
./node_modules/.bin/tailwindcss init
```

If you want to make this easier for the future you could add an alias to the command.
See https://help.screencraft.net.au/hc/2680392001/66/add-bash-command-line-aliases-for-git for more details.

Open the `tailwind.config.js` file (it will be in the root of the project) and update it so it contains:

```js
/**
 * Tailwind Configuration File
 *
 * Filename:        tailwind.config.js
 * Location:        /
 * Project:         SaaS-Vanilla-MVC
 * Date Created:    20/08/2024
 *
 * Author:          Your Name
 */

/** @type {import('tailwindcss').Config} */
module.exports = {
    content: [
        "static/**/*.{js,html,py}",
        "templates/**/*.{js,html,py}",
        "app.py",
        ],
    theme: {
        extend: {},
    },
    plugins: [],
}
```

Open the `src/source.css` file and add:

```css
@tailwind base;
@tailwind components;
@tailwind utilities;
```

### FontAwesomne

Now we need to download FontAwesome.

We have provided a minimal installation with all the web fonts and the required CSS files for the free version of FontAwesome 6.0.0.

If you want to grab the latest then head to the [FontAwesome.com](https://FontAwesome.com) website and download the web version from there.

Download our minimal installation file from here: 

- [FontAwesome-6-Minimal.7z](../assets/FontAwesome-6-Minimal.7z)
or
- [FontAwesome-6-Minimal.zip](../assets/FontAwesome-6-Minimal.zip)

Extract the contents and copy the `webfonts` and the `css` folders into the `static` folder in your project.

We will add these to our base template later...

### Watching the files...

Open a new Bash CLI.

Presuming you are in the Source/Repos folder we now change into the project folder, and start the Tailwind build &
watch:

```bash
tailwind -i src/source.css -o static/css/site.css --watch
```

# Creating A Home Page

Create a Python 'app.py' file:

```shell
touch app.py
```

Now edit it in PyCharm...

Add the following:

```python
from fastapi import FastAPI, Request, HTTPException

app = FastAPI(title="FastAPI Templating")

@app.get("/")
async def home(request: Request):
    return "{'greeting':'Hello World'}"
```

## Start the (FastAPI) Engines...

```shell
fastapi dev app.py
```

### Visit your new little application at:

```text
http://127.0.0.1:8000
```

You should see a very simple "Hello World" message (which happens to be in JSON format).

## Add Static file & Template Pages & Components Folders

Open a new CLI and make sure you have `cd`-ed into the project folder, and then activated Python:

```shell
cd xxx-fastapi-templating
```

Run the following commands to create `.gitignore` files in new `js`, `img`, and `files` folders.

```shell
mkdir -P static/{img,files,js} templates/{pages,components}
touch static/{img,files,js}/.gitignore
touch templates/{pages,components}/.gitignore
```

## Commit the work So Far

```shell
git add .
git commit -m "feat(start): Start of the application

- Add static/js folder
- Add static/img folder
- Add static/files folder
- Add templates/pages folder
- Add templates/components folder
- Create simple application
"
```

Note the multi-line comment is entered on the command line by only using the `"` close quotes after
the final line of the comment. A neat little trick when working at the CLI.

# Adding an HTML Template

We are, at the moment, more interested in creating a small web site, so here goes.

Use the command line to create empty files for number of pages and other files.

```shell
touch templates/pages/home.html
touch templates/pages/about.html
touch templates/base.html
touch templates/components/{header,navigation,footer}.html
touch static/js/menu.js
```

We are getting the HTML files ready (even if they are blank) for adding their content.

Open the base page and add the following:

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>{% block title %} DEFAULT TITLE {% endblock %}</title>

    <!-- TailwindCSS include -->
    <link href="{{ url_for('static', path='css/site.css') }}" rel="stylesheet">
    
    <!-- FontAwesome include -->
    <link href="{{ url_for('static', path='css/all.css') }}" rel="stylesheet">
    
</head>
<body>

<div class="flex flex-col w-full min-h-screen bg-zinc-100 ">

    {% include "components/header.html" %}

    <main class="container grow h-full mx-auto p-8 flex flex-col ">
        {% block page_title %}{% endblock %}

        {% block main%}
        ...
        {% endblock%}
    </main>

    {% include "components/footer.html" %}

</div>
<script src="{{ url_for('static',path='js/menu.js') }}" defer></script>
</body>
</html>
```

Important items:

- `{% block BLOCK_NAME %} DEFAULT_CONTENT {% endblock %}`

This denotes a Jinja2 template "content block" that may be replaced in the pages that use the template.

To replace the default content we use `{% block title %} NEW CONTENT {% endblock %}` in the page that is
extending the base (or other) template.

- `{% include "FILE_PATH_AND_NAME" %}`

This statement tells the Jinja2 templating engine to include the file contained at the
location `FILE_PATH_AND_NAME`.

The path is relative to the application's location.

- `{{ url_for('LOCATION_ALIAS',path='FILE_PATH_AND_NAME') }}`

The Jinja2 templating engine will generate the full relative path name based on the `LOCATION_ALIAS` to
the file `FILE_PATH_AND_NAME` that is contained on the `LOCATION_ALIAS`.

Ok, so we had better update the `app.py` to start off with.

## Update `app.py` to add the static locations...

We will need a few new includes to start of with:

```python
from pathlib import Path

from fastapi import FastAPI, Request, HTTPException
from fastapi.responses import HTMLResponse
from fastapi.staticfiles import StaticFiles
from fastapi.templating import Jinja2Templates
```

This adds the various static file and template handling methods, plus the HTML Response class.

```python
app = FastAPI(title="FastAPI Templating")
```

The "app" line has not changed.

```python
BASE_PATH = Path(__file__).resolve().parent
```

We grab the application's home folder location, for debugging purposes.

```python
app.mount("/static", StaticFiles(directory="static"), name="static")

TEMPLATES = Jinja2Templates(directory="templates")
```

Here we are creating the static location alias that is used in the templates.

We could add these aliases specific to each of the folders if we wanted:

```python
app.mount("/static", StaticFiles(directory="static"), name="static")
app.mount("/css", StaticFiles(directory="static/css"), name="css")
app.mount("/js", StaticFiles(directory="static/js"), name="js")
```

This can be useful in reducing the code in the templates if needed.

```python
print(BASE_PATH)
```

This is just a debugging line, and does not affect the application's output.

Now we update the "home" route to return the home page...

```python
@app.get("/", response_class=HTMLResponse)
async def home(request: Request):
    return TEMPLATES.TemplateResponse(
        request=request, name="pages/home.html"
    )
```

### Preview page

How about refreshing the http://127.0.0.1:8000 page and seeing what you get?

Hopefully no errors...

## Create the Home Page Content

Ok, now open the `templates/pages/home.html` file and edit.

Add the following:

```html
{% extends "base.html" %}
```

This tells the Jinja2 engine that this content is based on (extends) the `base.html` template page.

```html
{% block title %}Home{% endblock title %}
```

We now tell the Jinja engine that the "title" of the page is `Home` and it will insert this into the
template's "title" block replacing the default title.

We then tell Jinja2 that we want to have an empty secondary navigation section. This is one way of us easily inserting
an additional navigation bar if we needed to.

```html
{% block page_title %}{% endblock %}
```

One of the beautiful parts of Jinja2 is that you can define the replacement content in any order you wish.

So, as the footer is short, we will add it after the extra content navigation.

```html
<!-- Footer of Page -->
{% block base_footer %}
<p class="text-zinc-500 text-left px-2 font-medium uppercase title-font mb-4 border-b border-zinc-500 w-full">
    Home Page
</p>
{% endblock %}
```

Finally we add the main content.

We are showing just some placeholder items at the moment.

```html
{% block main %}
<section class="container mx-auto border grow h-full shadow-md p-4 rounded space-y-2">
    <h2 class="bg-zinc-500 text-zinc-100 p-4 mb-4 -mx-4 -mt-4 rounded-t">Home Page</h2>
    <p>MAIN CONTENT</p>

    <ul class="list-disc list-inside">
        <li>List Item</li>
        <li>List Item</li>
        <li>List Item</li>
        <li>List Item</li>
        <li>List Item</li>
    </ul>

</section>
{% endblock %}
```

We should see a bit more from the page if you now refresh the browser.

## Create the components

We need header, footer and navigation components to begin with.

### header.html component

Let's get the Header component created.

Open the `templates/components/header.html` file and add:

```html

<header class="bg-zinc-900 w-full">

    {% include "components/navigation.html" %}

</header>
```


### footer.html component

Next the footer component...

We have a fairly large chunk of code for this footer. it is split into two parts:

- a footer navigation/links section
- a copyright / other info section

The footer/navigation section is split into lines that are related to each other, and each 
item is spaced out based on a 'grid'.

The copyright section is a simple set of paragraphs.

```html
<!-- Page Footer -->
<!-- based on https://www.creative-tim.com/twcomponents/component/tailwind-css-footer-1-->
<footer class="w-full text-zinc-700 bg-zinc-300 body-font text-sm">
    <div class="px-16 py-6 flex flex-col flex-wrap flex-grow w-full bg-zinc-200 ">

        <nav class="grid grid-cols-4 md:grid-cols-8 ">
            <h2 class="text-left mx-2 font-medium tracking-widest text-zinc-500 uppercase title-font">About</h2>
            <a href="{{ url_for('home') }}"
               class="text-left mx-2 text-zinc-400 cursor-pointer hover:text-zinc-600">Company</a>
            <a href="{{ url_for('home') }}"
               class="text-left mx-2 text-zinc-400 cursor-pointer hover:text-zinc-600">Careers</a>
            <a href="{{ url_for('home') }}"
               class="text-left mx-2 text-zinc-400 cursor-pointer hover:text-zinc-600">Blog</a>
        </nav>

        <nav class="grid grid-cols-4 md:grid-cols-8 pb-4">
            <h2 class="text-left mx-2 text-sm font-medium tracking-widest text-zinc-500 uppercase title-font">
                Support</h2>
            <a href="{{ url_for('home') }}"
               class="text-left mx-2 text-zinc-400 cursor-pointer hover:text-zinc-600">Contact Support</a>
            <a href="{{ url_for('home') }}"
               class="text-left mx-2 text-zinc-400 cursor-pointer hover:text-zinc-600">Help Resources</a>
            <a href="{{ url_for('home') }}"
               class="text-left mx-2 text-zinc-400 cursor-pointer hover:text-zinc-600">Release Updates</a>
        </nav>
    </div>
    <div class="w-full px-16 py-4 mx-auto mt-4">
        <p class="text-xs text-zinc-500 capitalize">
            © Copyright 2024 YOUR NAME. All rights reserved
        </p>
    </div>
</footer>
```

### navigation.html component

Finally, the navigation, which is quite a bit more complex.

Open the `templates/components/footer.html` file and add:

```html
<!-- Layout based on https://www.creative-tim.com/twcomponents/u/denver-edwards -->
<nav class="border border-zinc-300 py-2.5 bg-zinc-200 shadow-md shadow-zinc-900/50">
    <div class="container flex flex-wrap justify-between items-center mx-auto">
        <!-- Brand -->
        <a href="{{ url_for('home') }}" class="flex items-center">
            <h1 class="self-center text-xl font-semibold whitespace-nowrap flex flex-row-reverse">
                <span class="pl-2">
                    FastAPI
                </span>
                <span>
                    <i class="fa-brands fa-python text-zinc-500"></i>
                    <i class="fa-solid fa-truck-fast text-zinc-500"></i>
                </span>
            </h1>
        </a>

        <!-- Mobile/Responsive Navigation button -->
        <div class="flex items-center">
            <button
                    id="menu-toggle"
                    type="button"
                    class="inline-flex items-center p-2 ml-3 rounded-md text-sm text-zinc-500
                           hover:text-red-500 hover:bg-zinc-100
                           focus:outline-none focus:ring-2 focus:ring-zinc-200
                           md:hidden"
            >
                <span class="sr-only">Open main menu</span>
                <!-- Hamburger icon -->
                <svg class="h-6 w-6 " fill="none" viewBox="0 0 24 24" stroke="currentColor">
                    <path
                            stroke-linecap="round"
                            stroke-linejoin="round"
                            stroke-width="2"
                            d="M4 6h16M4 12h16m-7 6h7"
                    />
                </svg>
            </button>
        </div>

        <!-- Actual Navigation -->
        <div class="w-full md:block md:w-auto hidden"
             id="mobile-menu">
            <ul class="flex flex-col mt-4 md:flex-row md:space-x-8 md:mt-0 md:text-sm md:font-medium">
                <li>
                    <a href="{{ url_for('home') }}"
                       class="block py-2 pr-4 pl-3 md:p-0
                              text-zinc-700 hover:text-red-700
                              hover:bg-zinc-50 md:hover:bg-transparent
                              border-b border-zinc-100 md:border-0"
                       aria-current="page">
                        Home
                    </a>
                </li>
                <li>
                    <a href="{{ url_for('home') }}"
                       class="block py-2 pr-4 pl-3 md:p-0
                              text-zinc-700 hover:text-red-700
                              hover:bg-zinc-50 md:hover:bg-transparent
                              border-b border-zinc-100 md:border-0">
                        About
                    </a>
                </li>
                <li>
                    <a href="{{ url_for('home') }}"
                       class="block py-2 pr-4 pl-3 md:p-0
                              text-zinc-700 hover:text-red-700
                              hover:bg-zinc-50 md:hover:bg-transparent
                              border-b border-zinc-100 md:border-0">
                        Link
                    </a>
                </li>
                <li>
                    <a href="{{ url_for('home') }}"
                       class="block py-2 pr-4 pl-3 md:p-0
                              text-zinc-700 hover:text-red-700
                              hover:bg-zinc-50 md:hover:bg-transparent
                              border-b border-zinc-100 md:border-0">
                        Link
                    </a>
                </li>
                <li>
                    <a href="{{ url_for('home') }}"
                       class="block py-2 pr-4 pl-3 md:p-0
                              text-zinc-700 hover:text-red-700
                              hover:bg-zinc-50 md:hover:bg-transparent
                              border-b border-zinc-100 md:border-0">
                        Link
                    </a>
                </li>
            </ul>
        </div>

    </div>
</nav>

```

Once these are completed then refreshing the browser should show something similar to:

![FastAPI-2024-09-24-1@2x.png](../assets/FastAPI-2024-09-24-1%402x.png)



# END

Next up - [LINK TEXT](#)
