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

# Adafruit Account

Authors:
- Sander Huijsen (previous staff member)
- Adrian Gould (Perth campus)
- Murray Hay (Joondalup campus)


For sections of the classwork, portfolio and project work you will need an account with an external MQTT broker.

For this we are using a free Adafruit account.

The following steps will take you through creating such an account, as well as some of the basic sections of the pages you will use.


## Creating an Account

Open your browser and go to: https://adafruit.com

![](../Pasted%20image%2020250409151433.webp)

Click on the IO menu option.

![](../Pasted%20image%2020250409151407.webp)

Click on the "Get Started For Free" option on the right of the new menu bar:

![](../Pasted%20image%2020250409151506.webp)
Fill out the form using:
- Your given name
- The first initial of your surname
- Your student email address
- A suitable (TAFE appropriate) username
- A password

![](../Pasted%20image%2020250409151529.webp)

Click on Create Account.

It will set up your free account and then take you to your dashboard.

![](adafruit-dashboard-image.webp)



## Signing into Adafruit
If you are not logged into your account then you will need to sign in.

Follow these steps:

Open your browser and go to: https://adafruit.com

![](../Pasted%20image%2020250409151433.webp)

Click on the IO menu option.

![](../Pasted%20image%2020250409151407.webp)

Click on Sign In

![](../Pasted%20image%2020250409152413.webp)

Fill out the Sign In section using the email address and password you created previously.

Click Sign In.

![](../Pasted%20image%2020250409151307.webp)


## Adafruit Dashboard parts

### Overview
The overview shows account details and other information.

![](../Pasted%20image%2020250409153923.webp)

Part of the overview is a list of dashboards and feeds.

### Dashboards

![](../Pasted%20image%2020250409155320.webp)

### Feeds (aka topics)

![](../Pasted%20image%2020250409155332.webp)


### Adding Feeds

To add a feed you need to go into the Feeds section.

![](../Pasted%20image%2020250409155526.webp)

Click Feeds on the menu bar.

Click "New Feed" to create a new feed.

![](../Pasted%20image%2020250409155544.webp)


Enter the details into the modal dialog:

![](../Pasted%20image%2020250409155615.webp)

> ⚠️ Important
> 
> We **strongly** suggest you do NOT include spaces in the feed names (aka MQTT Topic Names).
> 
> Suitable names could be:
> - `NMT-IoT-LED/data`
> - `nmt-iot-led/data`
> - `NMT-IoT-LED-data`
> 
> Using a `/` makes it easier to identify a group of feeds/topics and their sub-topics.
> 
> If you enter a `/` then it is replaced by `-slash-`

Click Create once you have added at least the feed name.

When the feed is created, special characters are replaced by `-`.

The "**key**", or topic name, that you will use with MQTT is shown once the topic/feed is created:

![](../Pasted%20image%2020250409160324.webp)

#### Feed Information

You will need the feed information, including the key for any code you write for IoT device connection via MQTT to Adafruit.

Click the Feed name:

![](../Pasted%20image%2020250409160803.webp)

On the right you will see Feed Info:

![](../Pasted%20image%2020250409160824.webp)

Clicking on the Feed Info will show the API, Web and MQTT endpoint details:

![](../Pasted%20image%2020250409160911.webp)


## Adafruit Key Details

As this is a secured service you will need the Adafruit "My Key" that allows the logging into your Adafruit account and sending data to the topics/feeds.

Locate the Key icon and click:

![](../Pasted%20image%2020250409161212.webp)

A new dialog will show the username and active key for the account:

![](../Pasted%20image%2020250409161059.webp)


> ⚠️ **DO NOT SHARE THESE DETAILS**
> 
> - Handle this information with care.
> - Treat it like you treat your passwords.


## Items to consider

- Browse over the Adafruit account details
- Check out the plan and its limitations
	- E.g., mind the rate limit…

