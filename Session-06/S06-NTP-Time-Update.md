# Getting Accurate Time

This code demonstrates how to get an accurate time from a Network Time Protocol Server, and send the data to the Serial port for monitoring.

This code uses just the ESP32, and no electronics.

# Libraries

To begin you will need to add some Libraries:

You will need the Wi-Fi and UDP Wi-Fi libraries that are library from the ESP32 standard libraries. The Wi-Fi UDP library provides the communication via UDP rather than TCP.

The last library for this is Stefan Staub's Network Time Protocol library.

Use the Arduino IDE Library manager to locate the NTP library by Stefan Staub, and install this.

# Code

Outline of the code's function etc.

```c
/**
 * NTP Time Update
 * 
 * Requires connection to the Internet
 *
 * Details on how Wi-Fi connection is accomplished
 * are available in previous tutorials
 *
 * Filename:  wifi-ntp-update.ino
 * Author:    Adrian Gould <adrian.gould@nmtafe.wa.edu.au>
 * Version:   1.0
 */
```

Define the required libraries...

```c
/* 
 * Libraries
 */ 
#include <WiFi.h>
#include "WiFiUdp.h"
#include "NTP.h"
```

Define any C macros, constants and variables, plus initialise the UDP connection to NTP servers.

```c
/* 
 * Macros
 */ 
#define RETRY_PERIOD 1000  

/* 
 * Constants
 */ 
const char* ssid = "NMT-IoT";
const char* password = "Do Not Share M3!";

/* 
 * Variables
 */ 
WiFiUDP wifiUdp;
NTP ntp(wifiUdp);
```

Time to set up the hardware, and to set the rules for daylight saving.

Then start the NTP communication.

```
/* 
 * Setup and Initialise the hardware
 */ 
void setup() {
  Serial.begin(115200);
  wiFiConnect();

  /* If you need to define daylight saving start
   * and end points then we use the following...
   *  ...
   * For Daylight Savings to Start on
   *     The last Sunday in March
   *     At 2:00AM
   *     For Central European Summer Time
   *     +120min (+1 GMT + 1h summertime offset)
   * and End on:
   *     The last Sunday in October 
   *     At 3:00AM
   *     For Central European Time
   *     +60min (+1 GMT)
   */
  ntp.ruleDST("CEST", Last, Sun, Mar, 2, 120); 
  ntp.ruleSTD("CET", Last, Sun, Oct, 3, 60);

  ntp.begin();

  Serial.println("start NTP");
}
```

The work loop simply gets the current time from the NTP server and then prints the data and time to the serial monitor.

```c
/* 
 * The work loop
 */ 
void loop() {
  ntp.update();

  // Output current date & time to the serial monitor
  Serial.println(ntp.formattedTime("%d. %B %Y"));
  Serial.println(ntp.formattedTime("%A %T"));

  // (Blocking) wait for 1 second
  delay(1000);
}
```

The Wi-Fi Connect function is a cut down version of the one we have created before, as it does not have a maximum number of tries, and does not 'back-off' when it fails to connect.

```c
/* 
 * Wi-Fi Connection Function
 */ 
void wiFiConnect() {
  // Configure WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");

  // Loop until connected, delaying by
  // RETRY_PERIOD between attempts
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(RETRY_PERIOD);
  }
```

The connection details is optional, but always nice to see when starting this form of project...

```c
  // Output connection details
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
```


[Back to Session 06...](ReadMe.md)
