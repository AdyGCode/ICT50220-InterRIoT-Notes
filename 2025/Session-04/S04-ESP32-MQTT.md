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
# Setting Up

To set up Mosquitto and MQTTX, see [S04-MQTT-Setting-Up-Mosquitto-and-MQTTX](S04-MQTT-Setting-Up-Mosquitto-and-MQTTX.md).


Create a folder in your `Source/Repos` folder called `mosquitto` and move/change into it.

```shell
mkdir mosquitto
cd mosquitto
```

You will need the IP Address of the computer for the configuration. To get this use (on a Windows machine with Git Bash):

```shell
ipconfig | grep IPv4
```

On a Linux or Mac you will use:

```shell
ifconfig | grep inet
```

The output will look similar to:
```text
   IPv4 Address. . . . . . . . . . . : 10.25.35.101
   IPv4 Address. . . . . . . . . . . : 192.168.56.1
```

Now we need a new `mosquitto.conf` file.

```shell
touch mosquitto.conf
nano mosquitto.conf
```

`touch` creates an empty file, or if it exists, tells the operating system to update the last change date/time.

`nano` opens the CLI based micro-editor with the file named.

In this file enter:
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
# Use ipconfig (on Windows) to find out the local machine
# IP Address and update the value here. If you have more
# than one network connection, duplicate the line and
# update the IP address for each one
listener 1883 NNN.NNN.NNN.NNN

# listen on port 1883 on all IP addresses of this machine
# this usually works for all network connections, but we
# are adding as a fall back.
listener 1883 0.0.0.0

# maximum number of clients that can connect to the broker
max_connections 16
```

Use <kbd>CTRL</kbd> + <kbd>X</kbd> to start to exit nano.

It will ask if you wish to save the modified buffer? Press <kbd>Y</kbd>

It will now ask if you want to change the filename, we do not so press <kbd>ENTER</kbd>.


For the lazy - direct link: [mosquitto.conf](mosquitto.conf).

### Executing Mosquitto

We installed Mosquitto in the `c:\Laragon\Bin\Mosquitto` folder, so now we can execute it using our config file:

```shell
/c/laragon/bin/mosquitto/mosquitto -v -c ./mosquitto.conf
```

This will run Mosquitto in the foreground, and show a verbose message output, ideal for debugging and quick monitoring of the system.

# Circuit

TODO: Add circuit diagram and photo


# Code!

```c++
/**
 * ESP32 WiFi & MQTT Connection v1
 *
 * Sketch Name: WiFi-MQTT-1.ino
 * Author:      Adrian Gould
 *
 * Description: This sketch attempts to:
 *  - create a connection to a given WiFi SSID
 *  - if the WiFi is connected then
 *    attempts to connect to a given MQTT Broker/Server.
 *
 * Use the Library Manager to install:
 *  - Adafruit MQTT Library
 *
 * See also:
 * https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
 *
 *
 * --------------------------------------------------------------------
 * Sample output from ESP32 in Debug Mode
 *
 * ets Jul 29 2019 12:21:46
 *
 * rst:0x1 (POWERON_RESET),boot:0x13 (SPI_FAST_FLASH_BOOT)
 * configsip: 0, SPIWP:0xee
 * clk_drv:0x00,q_drv:0x00,d_drv:0x00,cs0_drv:0x00,hd_drv:0x00,wp_drv:0x00
 * mode:DIO, clock div:1
 * load:0x3fff0030,len:4916
 * load:0x40078000,len:16436
 * load:0x40080400,len:4
 * ho 8 tail 4 room 4
 * load:0x40080404,len:3524
 * entry 0x400805b8
 * Connecting to WiFi...
 * .
 * WiFi Connected.
 *
 * Local IP:        10.25.35.152
 * Gateway IP:      10.25.35.1
 * Signal Strength: -52
 * Hostname:        esp32-65465C
 *
 * Connecting to MQTT Broker/Server...
 * ...
 * MQTT Connected.
 */
  
/**
 * Include the required Libraries for MQTT and WiFi
 */
#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
  
/**
 * Define Macros for constant values
 *
 * - MQTT Connection details 
 *   (update the SERVER address to the current IP)
 * - Retry values
 * - Component Pins
 */
#define MQTT_USERNAME ""
#define MQTT_PASSWORD ""
#define MQTT_SERVER "10.25.35.101"
#define MQTT_SERVERPORT 1883
  
#define RETRY_PERIOD 1000
#define RETRY_ADJUSTMENT 500
#define MAX_ATTEMPTS 5
 
#define LED_RED_1 25
#define LED_GREEN_1 26
#define LED_BLUE_1 27

/* Set to FALSE if you do not want the Serial port output */
#define DEBUG true
 
/**
 * Define the WiFi SSID and Password
 */
const char* ssid = "NMT-IoT";
const char* password = "Its!Working";
 
/**
 * Create the WiFi Client and MQTT Client for connections
 */
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_PASSWORD);

/**
 * The setup code is executed EVERY time the ESP32 restarts.
 * This includes on:
 *   - Inital power up
 *   - Hard reset of device
 *   - On wake from sleep
 */
void setup() {

  /**
   * Serial port connection is being used as a method of DEBUGging only.
   */
  if (DEBUG) {
    Serial.begin(115200);
  }

 
  pinMode(LED_RED_1, OUTPUT);
  pinMode(LED_GREEN_1, OUTPUT);
  pinMode(LED_BLUE_1, OUTPUT);

 
  digitalWrite(LED_RED_1, HIGH);
  digitalWrite(LED_GREEN_1, LOW);
  digitalWrite(LED_BLUE_1, LOW);

  
  bool wiFiConnected = wiFiConnect();
  
  if (wiFiConnected) {
    if (DEBUG) {
      Serial.println("WiFi Connected.");
    }
 
    digitalWrite(LED_RED_1, LOW);
    digitalWrite(LED_GREEN_1, HIGH);
    digitalWrite(LED_BLUE_1, LOW);

    if (DEBUG) {
	    wiFiDetails();
	}
	
    bool mqttConnected = mqttConnect();
  
    if (mqttConnected) {
      if (DEBUG) {
        Serial.println("MQTT Connected.");
      }
 
      digitalWrite(LED_BLUE_1, HIGH);
      delay(RETRY_PERIOD);
      digitalWrite(LED_BLUE_1, LOW);
    } else {
      if (DEBUG) {
        Serial.println("MQTT Connection Failed.");
      }
  
      digitalWrite(LED_RED_1, HIGH);
      digitalWrite(LED_GREEN_1, LOW);
      digitalWrite(LED_BLUE_1, LOW);
    }
  
  } else {
    if (DEBUG) {
      Serial.println("WiFi Connection Failed.");
    }
  }
}
  
void loop() {
  // put your main code here, to run repeatedly:
}
  

bool wiFiConnect() {
  int attempts = 0;
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  if (DEBUG) {
    Serial.println("Connecting to WiFi...");
  }
  
  while (WiFi.status() != WL_CONNECTED && attempts < MAX_ATTEMPTS) {
  
    if (DEBUG) {
      Serial.print(".");
    }

    delay(RETRY_PERIOD + RETRY_ADJUSTMENT * attempts);
    attempts++;
  }
 
  return attempts < MAX_ATTEMPTS;
}

  
bool mqttConnect() {
  
  uint8_t attempts = 0;
  int8_t mqttConnectionResult;
  
  if (DEBUG) {
    Serial.println();
    Serial.println("Connecting to MQTT Broker/Server...");
  }
 
  while ((mqttConnectionResult = mqtt.connect()) != 0 && attempts < MAX_ATTEMPTS) {
  
    if (DEBUG) {
      Serial.print(".");
    }
  
    delay(RETRY_PERIOD + RETRY_ADJUSTMENT * attempts);
    attempts++;
  
    if (mqttConnectionResult != 0) {
      mqtt.disconnect();
    }
  }
  
  return attempts < MAX_ATTEMPTS;
}
  
 
  
void wiFiDetails() {
  if (DEBUG) {
    Serial.println();
    Serial.print("Local IP:        ");
    Serial.println(WiFi.localIP());
    Serial.print("Gateway IP:      ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Signal Strength: ");
    Serial.println(WiFi.RSSI());
    Serial.print("Hostname:        ");
    Serial.println(WiFi.getHostname());
  }
}
```

### Save, Compile and Upload

Save the new sketch (WiFi-MQTT-1.ino) and compile it and upload to your ESP32.

The code should connect to the Wi-Fi, then to MQTT. When it does this the LEDs will be used to indicate the state of the connections.

[Back to Session 04...](ReadMe.md)
