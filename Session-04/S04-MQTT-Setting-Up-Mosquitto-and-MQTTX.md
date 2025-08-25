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
# Setting Up Mosquitto & MQTTX

> We use the 7-Zip application to compress our files. Please install this quick and powerful compression application from https://7-zip.org.

## Adding Mosquitto to Laragon

You can install Mosquitto via an installer downloadable from https://mosquitto.org.

We, though, recommend using the 7-zipped up executable downloaded from here: [Mosquitto 7z](../assets/mosquitto.7z) or [GitHub Direct Download of 7z file](https://github.com/AdyGCode/ICT50220-InterRIoT-Notes/raw/refs/heads/main/assets/mosquitto.7z).

We will update this file every semester, so it may be a version or three behind the official downloads.

Once downloaded do the following steps...

Open the compressed file (mosquitto.7z) using the 7-zip application.

Open a second Windows File Explorer <kbd>WIN</kbd>+<kbd>E</kdb> and locate the Laragon folder:

- TDM Network: `C:\Laragon\`
- TAFE Network: `C:\ProgramData\Laragon`

Navigate into the Laragon `bin` folder.

Drag and drop the `mosquitto` folder from the compressed folder into the `bin` folder.

This adds Mosquitto to the available programs.

We need to create a configuration file before we use it.

### Mosquitto Configuration

Create a new folder in your `Source/Repos` folder called `mosquitto`, and move/change into it.

```shell
mkdir mosquitto
cd mosquitto
```

Check the IP Address for the local computer (not 127.0.0.1 in this case):

```shell
ipconfig 
```

You will get details similar to this:

```text
Ethernet adapter Ethernet:

   Connection-specific DNS Suffix  . : 
   IPv4 Address. . . . . . . . . . . : 10.25.35.101
   Subnet Mask . . . . . . . . . . . : 255.255.255.0
   Default Gateway . . . . . . . . . : 10.25.35.1

Ethernet adapter Ethernet 3:

   Connection-specific DNS Suffix  . :
   IPv4 Address. . . . . . . . . . . : 192.168.56.1
   Subnet Mask . . . . . . . . . . . : 255.255.255.0
   Default Gateway . . . . . . . . . :
```

Selecting the correct IP address is important.

### Create the Config File

Now we need a new `mosquitto.conf` file.

```shell
touch mosquitto.conf
nano mosquitto.conf
```

`touch` creates an empty file, or if it exists, tells the operating system to update the last change date/time.

`nano` opens the CLI based micro-editor with the file named.

> You may also use `code mosquitto.conf` to edit the file using VSCode.

Add to the `mosquitto.conf` file:

```ini
# Personal Mosquitto Config

# Allow for anonymous connections
allow_anonymous true

# Save the in memory database to disc every 15 minutes
autosave_interval 900

# Save the subscription changes
autosave_on_changes true

# Persistent data (connection, subscription, message, et al)
persistence true

# Persistence Filename
persistence_file mosquitto-persist.db

# Perisitent Client Clean Up
persistent_client_expiration 14d

# Listeners (most specific first)
# listen on port 1883 on IP address 10.25.35.101
#
# Use ipconfig (on Windows) to find out the local
# machine IP Address and update the value here.
# If you have more than one network connection, 
# duplicate the line and update the IP address
# for each one
listener 1883 10.25.35.101

# listen on port 1883 on all IP addresses of 
# this machine this usually works for all network 
# connections, but we are adding as a fallback option.
listener 1883 0.0.0.0

# maximum number of clients that may connect to the broker
max_connections 16
```

Use <kbd>CTRL</kbd> + <kbd>X</kbd> to exit nano.

It will ask if you wish to save the modified buffer? Press <kbd>Y</kbd>

It will now ask if you want to change the filename, we do not so press <kbd>ENTER</kbd>.


For the lazy - direct link: [mosquitto.conf](mosquitto.conf).

### Executing Mosquitto

We installed Mosquitto in the `c:\Laragon\Bin\Mosquitto` folder, so now we can execute it using our config file:

```shell
/c/laragon/bin/mosquitto/mosquitto -v -c ./mosquitto.conf
```

This will run Mosquitto in the foreground, and show a verbose message output, ideal for debugging and quick monitoring of the system.

## Installing MQTTX

Download MQTTX using our pre-compressed version [MQTTX.7z](../assets/mqttx.7z) or [GitHub Direct Download MQTTX.7z](https://github.com/AdyGCode/ICT50220-InterRIoT-Notes/raw/refs/heads/main/assets/MQTTX.7z).

Once downloaded use 7-zip to open the archive.

Inside there is a MQTTX folder.

![](../assets/Pasted%20image%2020250811152615.png)

Open a Windows File Explorer if you have not done so already, and navigate to the `C:\laragon\bin` folder.

Drag and drop the MQTTX files into this `bin` folder.

### Running MQTTX

To run MQTTX, locate the mqttx.exe file in the MQTTX folder and double click.

This reveals the welcome screen, plus often a version information pop-up:

![](../assets/Pasted%20image%2020250811154402.png)

Close the info dialog if it is shown.

![](../assets/Pasted%20image%2020250811154713.png)

To create a New MQTT connection to our copy of Mosquitto, we do the following:

Click on New Connection, to show the new connection dialog.

We are concerned with the top part of the dialog at this time:

![](../assets/Pasted%20image%2020250811154902.png)

Update / Add details as described below:

| Item            | Default        | Typical/Example                                |
| --------------- | -------------- | ---------------------------------------------- |
| Name            | -empty-        | Mosquitto 35.101                               |
| Host (protocol) | mqtt://        |                                                |
| Host (address)  | broker.emqx.io | 10.25.35.101<br>localhost<br>l306-25.tdm.local |
| Port            | 1883           |                                                |
| Client ID       | -empty-        | L306-25-A<br>ESP32-25-1                        |
| Username        | -empty-        |                                                |
| Password        | -empty-        |                                                |
| SSL/TLS         | Off            |                                                |

Example settings:

![](../assets/Pasted%20image%2020250811163138.png)

Click on Connect.

This should connect to the MQTT server you identified:

![](../assets/Pasted%20image%2020250811163201.png)

## MQTT Topics

In MQTT, data is sent via topics.

Topics are like channels in Discord, Facebook, etc.

Topics may have sub-topics as well.

You subscribe to Topics to be able to receive data, and you Publish to topics to send data.

### Subscription

To subscribe in MQTTX, we clikc the "New Subscription" button:

![](../assets/Pasted%20image%2020250811163456.png)

This presents:

![](../assets/Pasted%20image%2020250811163516.png)

We complete the settings using a configuration similar to the example below:

| Item                     | Default          | Typical/Example |
| ------------------------ | ---------------- | --------------- |
| Topic                    | testtopic/#      | iot/test        |
| QoS                      | 0 (At most once) |                 |
| Colour                   | #9CE29B          | #9CE29B         |
| Alias                    | -empty-          |                 |
| Subscription Identifier  | -empty-          |                 |
| No Local Flag            | false            |                 |
| Retain as Published Flag | false            |                 |
| Retain Handling          | 0                |                 |

Here is an example configuration:

![](../assets/Pasted%20image%2020250811163832.png)

Clicking Confirm will subscribe to that topic:

![](../assets/Pasted%20image%2020250811164801.png)

### Publishing to a Topic

To publish data to a topic we use the bottom section of the live connection page:

![](../assets/Pasted%20image%2020250811164838.png)

To send a topic fill out the values as needed:

| Item    | Default                    | Typical/Example                                      |
| ------- | -------------------------- | ---------------------------------------------------- |
| Topic   | -empty-                    | iot/test                                             |
| QoS     | 0                          | 0                                                    |
| Retain  | Off                        | Off                                                  |
| Meta    | -                          | _no changes_                                         |
| Message | {<br>  "msg": "hello"<br>} | {<br>  "client": "ESP2-25-A",<br>  "LED_1": "1"<br>} |

Once you fill out the data, you click the send button:

![](../assets/Pasted%20image%2020250811165210.png)

When you send the message payload will go to the broker (MQTT Server, aka mosquitto). The broker then will send the message to ALL clients who have subscribed to the topic.

On MQTTX we see:

![](../assets/Pasted%20image%2020250811165324.png)

If you change the Plaintext to JSON, you get syntax highlighted responses:

![](../assets/Pasted%20image%2020250811165357.png)


