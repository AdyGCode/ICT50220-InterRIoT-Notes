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
  - Internet
  - of
  - Things
  - InterRIoT
  - IoT
  - Robotics
  - Python
  - Arduino
  - ESP-32
  - C
  - C++
date created: 25 July 2025
date modified: 10 July 2024
---

# Notes and Research


Follow the steps below to create a version controlled repository for:
- notes
- code
- other useful information

## Set Up The CLI

Set up the MS Terminal ready for future sessions.

Follow the steps contained in:

- https://help.screencraft.net.au/hc/1299211922/65/add-git-bash-to-microsoft-terminal


## Ensure Git on the Windows Path

Follow these instructions to use Laragon v6 to add git to your user defined environment variables and path.

- https://help.screencraft.net.au/hc/1299211922/36/adding-laragon-to-the-system-path

Also use these instructions if Git asks for your username and password:

- https://help.screencraft.net.au/hc/1299211922/89/stop-git-asking-for-my-username-and-password

## Add CLI Aliases for future work

Follow these instructions to add aliases to the CLI:

- https://help.screencraft.net.au/hc/1299211922/66/add-bash-command-line-aliases-for-git


## Check your Configuration

If you have not done so, close your terminal completely and reopen it with current settings.

Check git is accessible using:

```shell
git --version
```

It should respond with something similar to this:

```text
$ git --version
git version 2.43.0.windows.1
```

If not, make sure you have followed the steps previously.

Next we want to verify we are in the Source Repos folder.

Execute:
```shell
pwd
```

You should see something like:

```text
/c/Users/adriangould/Source/Repos
```

If the above shows `source/repos` at the end, then you are already set up with the required folder and ready to work.

Case does not matter on a Windows system.

## Create a new repository on GitHub

Got to https://github.com and log in to your personal GitHub account. 

If you do not have a GitHub account then create one.

Once you have logged in, create a new repository with the following details:

| Item            | Value                                     | Notes                                                           |
| --------------- | ----------------------------------------- | --------------------------------------------------------------- |
| Repository Name | ICT50220-InterRIoT-Notes-and-Research-xxx | Replace xxx with YOUR initials!                                 |
| ReadMe          | Yes                                       | Create a readme                                                 |
| License         | No                                        |                                                                 |
| Git Ignore      | None                                      |                                                                 |
| Private?        | Yes                                       | This is up to you. We would recomnment that this is set to YES. |


Once created, note the URL of the repo.

```text
https://github.com/AdyGCode/ICT50220-InterRIoT-Notes-and-Research-ajg.git
```

![](vivaldi_YsKjQI1dsN.mp4)


### Clone the Repository

Clone your repository to the Source Repos folder:

```shell
git clone https://github.com/AdyGCode/ICT50220-InterRIoT-Notes-and-Research-ajg.git
```

Replace the URL above with your own.

Change into the folder:

```shell
cd ICT50220-InterRIoT-Notes-and-Research-ajg
```

You are now ready to add notes, code and other research.

### Create and Commit Recommended Structure

We would recommend a week by week (session-by-session) folder structure to keep work organised.

To quickly create the required folder structure, ignore files, check in and push the structure to the remote, use the following commands:

```shell
git branch -m main

mkdir -p session-{0,1}{0,1,2,3,4,5,6,7,8,9}/code

touch session-{0,1}{0,1,2,3,4,5,6,7,8,9}/{.gitignore,code/.gitignore}

git add .

git commit -m "chore: set up folder structure"

git push origin main
```

Download the following compressed file, and un-compress its contents into your repository folder:

- FILE: ![Obsidian Starter Files](obsidian.7z)

We have provided you with a starter configuration for notes, code, and other requirements using Obsidian as a markdown editor.

## Community Plugins

We have selected the following community plugins:
- Git
- Reminder
- Global Search and Replace
- Persistent Links
- Advanced Tables

We have not turned on the extensions, or configured them.

To do so, use <kbd>CTRL</kbd>+<kbd>,</kbd>

## Using Obsidian and Other Info

For details on how to use templates in Obsidian, please check the following links:

- https://facedragons.com/productivity/obsidian-templates-with-examples/
- https://blog.obsibrain.com/other-articles/obsidian-for-students
- https://publish.obsidian.md/aidanhelfant/Extras/Templates/Uni+Course+Template
- https://medium.com/@dianademco/7-obsidian-templates-to-streamline-your-notes-ab3a3c8757be
- https://forum.obsidian.md/t/16-obsidian-templates-for-zettelkasten-to-start-with/49098
- https://github.com/llZektorll/Template_Hub
- https://facedragons.com/personal-development/obsidian-for-students/
- https://github.com/AdamJeddy/Bunch-of-Obsidian-Templates

