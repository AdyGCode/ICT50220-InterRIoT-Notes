/**
 * ESP32 Wi-Fi Scanner
 *
 * A small wi-fi scnner for the esp32
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


// Constants


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
  DEBUG_BEGIN(115200); // higher serial port speed 
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  DEBUG_PRINTLN("Set-up complete");
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

  DEBUG_PRINTLN("Starting scan...");

  int networkCount = WiFi.scanNetworks();
  DEBUG_PRINTLN("Scan done.");

  if (networkCount == 0){
    DEBUG_PRINTLN("No networks found.");
  } else {
    DEBUG_PRINT(networkCount);
    DEBUG_PRINTLN(" networks found.");

    for (int count = 0; count < networkCount; count++){
      DEBUG_PRINT(count+1);
      DEBUG_PRINT(": ")
      DEBUG_PRINT(WiFi.SSID(count));
      DEBUG_PRINT(" (");
      DEBUG_PRINT(WiFi.RSSI(count));
      DEBUG_PRINT("dB) ");
      bool wifiOpen = WiFi.encryptionType(count) == WIFI_AUTH_OPEN;
      DEBUG_PRINTLN(wifiOpen ? " " : "Secured");
      delay(10);
    } // end for
  } // end if

  DEBUG_PRINTLN("");
  delay(5000);
}

/**--------------------------------------------------------------------------
 * Functions & Helper Code
 *---------------------------------------------------------------------------*/

