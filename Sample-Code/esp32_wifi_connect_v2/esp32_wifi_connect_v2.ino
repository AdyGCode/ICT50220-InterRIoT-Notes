/**
 * ESP32 Wi-Fi Connection v2
 *
 * Demo of connecting to a Wi-Fi Network.
 * Has maximum attempts before giving up.
 * Back-Off period ensures not "swamping" Access 
 * Point with connection attempts
 *
 * Filename:        esp32_wifi_connect_v2.ino
 *
 * Assessment Name: n/a
 * Due:             n/a
 * Name:            Adrian Gould
 *
 */

/**--------------------------------------------------------------------------
 * External Source, Package, Module includes
 *---------------------------------------------------------------------------*/
// Includes
#include "WiFi.h"



/**--------------------------------------------------------------------------
 * Declarations 
 *---------------------------------------------------------------------------*/

// Debugging Macros
//   1 = Debugging on
//   0 = Debugging off
#define DEBUG 1

#if DEBUG
  #define DEBUG_PRINT(data) Serial.print(data); Serial.print(" ");
  #define DEBUG_PRINTLN(data) Serial.println(data)
  #define DEBUG_BEGIN(speed) Serial.begin(speed); while(!Serial) {}
#else
  #define DEBUG_PRINT(debug)
  #define DEBUG_PRINTLN(debug)
  #define DEBUG_BEGIN(speed)
#endif

// Macros
#define MAX_ATTEMPTS 5
#define RETRY_PERIOD 1000
#define RETRY_BACKOFF 500

// Constants

const char* WIFI_SSID = "NMT-IoT";
const char* WIFI_PASS = "Its!Working";

// Variables


/**--------------------------------------------------------------------------
 * Hardware/Software Configuration
 *---------------------------------------------------------------------------*/
// Setting Up Hardware

void setup()
{
/**
 * This code executes ONCE per Power-up or Wake 
 */
  DEBUG_BEGIN(9600);  // Higher serial port speed 115200
  delay(2000);        // Allow the Serial port to connect
  int connected_wifi = initWiFi();         // Call the Connect to Wi-Fi function
  
  DEBUG_PRINTLN("");

  if (!connected_wifi) {
    DEBUG_PRINT("No Wi-fi Connection");
  } else {
    DEBUG_PRINT("Hostname:");
    DEBUG_PRINTLN(WiFi.getHostname());

    DEBUG_PRINT("SSID:");
    DEBUG_PRINTLN(WIFI_SSID);

    DEBUG_PRINT("Signal Strength:");
    DEBUG_PRINTLN(WiFi.RSSI());

    DEBUG_PRINT("Ip Address:");
    DEBUG_PRINTLN(WiFi.localIP());
  
    //DEBUG_PRINT("Encryption Type:");
    //DEBUG_PRINTLN(WiFi.encryptionType()); // TKIP (WPA) = 2 WEP = 5 CCMP (WPA) = 4 NONE = 7 AUTO = 8

    DEBUG_PRINTLN("Set-up complete");
  }
  DEBUG_PRINTLN();

}

/**--------------------------------------------------------------------------
 * Master/Main Loop
 *---------------------------------------------------------------------------*/
void loop()
{
  /**
   * This code executes for as long as the hardware
   * is turned on, or not asleep
   */

  
}

/**--------------------------------------------------------------------------
 * Functions & Helper Code
 *---------------------------------------------------------------------------*/

bool initWiFi() {
  int attempts = 0; // current attempt count

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(10);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  DEBUG_PRINT("Connecting to Wi-Fi ");
  while (WiFi.status() != WL_CONNECTED && attempts < MAX_ATTEMPTS) {
    DEBUG_PRINT(".");
    delay(RETRY_PERIOD + RETRY_BACKOFF * attempts);
    attempts++;
  }

  return attempts < MAX_ATTEMPTS;
}
