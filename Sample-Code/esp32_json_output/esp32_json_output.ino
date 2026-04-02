/**
 * ESP32 JSON Output
 *
Filter your search...
Type:

All
Topic:

All





 * Demo of:
 * - Displaying data as JSON
 *
 * Use case:
 * - Useful for sending data via MQTT or similar
 *
 * Filename:        esp32_json_output.ino
 *
 * Assessment Name: n/a
 * Due:             n/a
 * Name:            Adrian Gould
 *
 */


/**--------------------------------------------------------------------------
 * External Source, Package, Module includes
 *---------------------------------------------------------------------------*/
#include <ArduinoJson.h>

/**--------------------------------------------------------------------------
 * Declarations 
 *---------------------------------------------------------------------------*/

// Debugging Macros
//   1 = Debugging on
//   0 = Debugging off
#define DEBUG 1

#if DEBUG
#define DEBUG_BEGIN(speed) \
  Serial.begin(speed); \
  while (!Serial) {}
#define DEBUG_PRINT(data) \
  Serial.print(data); \
  Serial.print(" ");
#define DEBUG_PRINTF(ifsh, ...) Serial.printf(ifsh, ##__VA_ARGS__)
#define DEBUG_PRINTLN(data) Serial.println(data);
#define DEBUG_FLUSH() Serial.flush();
#else
#define DEBUG_BEGIN(speed)
#define DEBUG_PRINT(debug)
#define DEBUG_PRINTLN(debug)
#define DEBUG_PRINTF(ifsh, ...)
#define DEBUG_FLUSH()
#endif

// Macros
#define MQTT_CLIENTNAME "ESP32-L306-25-AG"

// Constants


// Variables
char* reason;

/**--------------------------------------------------------------------------
 * Hardware/Software Configuration
 *---------------------------------------------------------------------------*/

void setup() {
 
  DEBUG_BEGIN(115200);                // Higher serial port speed 115200
  delay(1000);                      // Allow the Serial port to connect
  DEBUG_PRINTLN("");

  reason = "Woke on button";
  sendSensorData(reason, MQTT_CLIENTNAME);

}

/**--------------------------------------------------------------------------
 * Master/Main Loop
 *---------------------------------------------------------------------------*/
void loop() {
 
}

/**--------------------------------------------------------------------------
 * Functions & Helper Code
 *---------------------------------------------------------------------------*/

void sendSensorData( const char* reason, const char* deviceId) {
    JsonDocument doc;
    doc["device_id"] = deviceId;
    doc["wake"] = reason;
    doc["timestamp"] = millis();
    
    // Add nested object
    JsonObject location = doc["location"].to<JsonObject>();
    location["city"] = "Perth";
    location["state"] = "WA";
    
    // Serialize to string
    String output;
    serializeJson(doc, output);
    Serial.println(output);
    // Output: {"device_id":"esp32-01","temperature":32.5,...}

    // Send via MQTT
    // TODO: Send via MQTT
}