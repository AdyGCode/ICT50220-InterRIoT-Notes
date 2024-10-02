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


# DO NOT USE


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

```py
from pathlib import Path  
  
from fastapi import FastAPI, Request, HTTPException  
from fastapi.responses import HTMLResponse  
from fastapi.staticfiles import StaticFiles  
from fastapi.templating import Jinja2Templates  
  
app = FastAPI(title="FastAPI Templating")  
  
BASE_PATH = Path(__file__).resolve().parent  
  
app.mount("/static", StaticFiles(directory="static"), name="static")  
TEMPLATES = Jinja2Templates(directory="templates")  
  
print(BASE_PATH)  
  
@app.get("/", response_class=HTMLResponse)  
async def home(request: Request):  
    return "HELLO!"
```


## Start the (FastAPI) Engines...

```shell
fastapi dev app.py
```


When you open a web browser and head to `http://localhost:8000` or `http://127.0.0.1` you should see a blank page with "HELLO".


# Create a base template

Go back to the CLI and enter:

```shell
touch base.html
```

Open the file in your editor.

Add the following to create a base template file.

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <meta name="viewport"  
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">  
    <meta http-equiv="X-UA-Compatible" content="ie=edge">  
    <title>{% block title %} DEFAULT TITLE {% endblock %}</title>  
  
    <!-- TailwindCSS include -->  
    <link href="{{ url_for('static', path='/css/site.css') }}" rel="stylesheet">  
  
</head>  
<body class="bg-gray-200 font-sans leading-normal tracking-normal">  
<div class="flex flex-col w-full min-h-screen bg-white ">  
  
    <!-- https://www.creative-tim.com/twcomponents/u/denver-edwards -->  
    <header class="w-full">  
        <nav class="border border-gray-700 py-2.5 bg-gray-800 shadow">  
            <div class="container flex flex-wrap justify-between items-center mx-auto">  
                <a href="/" class="flex items-center">  
                    <h1 class="self-center text-xl font-semibold whitespace-nowrap text-white">  
                        FastAPI  
                    </h1>  
                </a>  
  
                <div class="flex items-center">  
                    <button  
                            id="menu-toggle"  
                            type="button"  
                            class="inline-flex items-center p-2 ml-3 text-sm text-zinc-300 rounded-lg hover:bg-gray-100 focus:outline-none focus:ring-2 focus:ring-gray-200 dark:text-gray-400 dark:hover:bg-gray-700 dark:focus:ring-gray-600 md:hidden"  
                    >  
                        <span class="sr-only">Open main menu</span>  
                        <!-- Hamburger icon -->  
                        <svg class="h-6 w-6" fill="none" viewBox="0 0 24 24" stroke="currentColor">  
                            <path  
                                    stroke-linecap="round"  
                                    stroke-linejoin="round"  
                                    stroke-width="2"  
                                    d="M4 6h16M4 12h16m-7 6h7"  
                            />  
                        </svg>  
                    </button>  
                </div>  
  
                <div class="w-full md:block md:w-auto hidden"  
                     id="mobile-menu">  
                    <ul class="flex flex-col mt-4 md:flex-row md:space-x-8 md:mt-0 md:text-sm md:font-medium">  
                        <li>  
                            <a href="#"  
                               class="block py-2 pr-4 pl-3 text-white bg-blue-700 rounded md:bg-transparent md:text-blue-500 md:p-0 dark:text-white"  
                               aria-current="page">  
                                Home  
                            </a>  
                        </li>  
                        <li>                            <a href="#"  
                               class="block py-2 pr-4 pl-3 text-zinc-300 border-b border-gray-100 hover:bg-gray-50 md:hover:bg-transparent md:border-0 md:hover:text-blue-500 md:p-0  dark:border-gray-700">  
                                About  
                            </a>  
                        </li>  
                        <li>                            <a href="#"  
                               class="block py-2 pr-4 pl-3 text-zinc-300 border-b border-gray-100 hover:bg-gray-50 md:hover:bg-transparent md:border-0 md:hover:text-blue-500 md:p-0  dark:border-gray-700">  
                                Services  
                            </a>  
                        </li>  
                        <li>                            <a href="#"  
                               class="block py-2 pr-4 pl-3 text-zinc-300 border-b border-gray-100 hover:bg-gray-50 md:hover:bg-transparent md:border-0 md:hover:text-blue-500 md:p-0  dark:border-gray-700">  
                                Pricing  
                            </a>  
                        </li>  
                        <li>                            <a href="#"  
                               class="block py-2 pr-4 pl-3 text-zinc-300 hover:bg-gray-50 md:hover:bg-transparent md:border-0 md:hover:text-blue-500 md:p-0 ">  
                                Contact  
                            </a>  
                        </li>  
                    </ul>  
                </div>  
  
            </div>  
        </nav>  
  
  
        {% block base_navigation %}  
        {% endblock %}  
    </header>  
  
    <main class="container grow mx-auto p-8">  
        {% block main%}  
        ...  
        {% endblock%}  
    </main>  
  
    <!-- based on https://www.creative-tim.com/twcomponents/component/tailwind-css-footer-1-->  
    <footer class="w-full text-zinc-300 bg-gray-100 body-font text-sm">  
        <div class="flex flex-col flex-wrap flex-grow mt-10 w-full">  
  
            <section class="px-4 w-full ">  
                {% block base_footer %}  
                <p class="text-left mx-2 font-medium uppercase title-font"> When shown: Additional footer items not part  
                    of the main footer below</p>  
                {% endblock %}  
            </section>  
  
            <nav class="px-4 grid grid-cols-8">  
                <h2 class="text-left mx-2 font-medium tracking-widest text-gray-600 uppercase title-font">About</h2>  
                <a class="text-left mx-2 text-zinc-400 cursor-pointer hover:text-gray-900">Company</a>  
                <a class="text-left mx-2 text-zinc-400 cursor-pointer hover:text-gray-900">Careers</a>  
                <a class="text-left mx-2 text-zinc-400 cursor-pointer hover:text-gray-900">Blog</a>  
            </nav>  
  
            <nav class="px-4 grid grid-cols-8">  
                <h2 class="text-left mx-2 text-sm font-medium tracking-widest text-gray-600 uppercase title-font">  
                    Support</h2>  
                <a class="text-left mx-2 text-zinc-400 cursor-pointer hover:text-gray-900">Contact Support</a>  
                <a class="text-left mx-2 text-zinc-400 cursor-pointer hover:text-gray-900">Help Resources</a>  
                <a class="text-left mx-2 text-zinc-400 cursor-pointer hover:text-gray-900">Release Updates</a>  
            </nav>  
        </div>  
        <div class="bg-gray-300 w-full px-5 py-4 mx-auto mt-4">  
            <p class="text-sm text-zinc-700 capitalize xl:text-center">© 2020 All rights reserved </p>  
        </div>  
    </footer>  
  
</div>  
<script>  
    const menuToggle = document.getElementById('menu-toggle');  
    const mobileMenu = document.getElementById('mobile-menu');  
  
    menuToggle.addEventListener('click', function () {  
        mobileMenu.classList.toggle('hidden');  
    });  
</script>  
</body>  
</html>
```

Refresh your browser to see something like this:

![](brave_wkoOLwtcfO.png)

Create a new folder:

```shell
mkdir static/components
touch static/components/.gitignore
```


# END

Next up - [LINK TEXT](#)
