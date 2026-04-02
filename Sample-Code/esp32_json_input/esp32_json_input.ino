/**
 * ESP32 JSON Input 1
 *
 * Demo of:
 * - Parsing JSON Data
 *
 * Use case:
 * - Useful for parsing commands from MQTT Subscription
 *
 * Filename:        esp32_json_parse_input.ino
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
#define MICRO_S_TO_S_FACTOR 1000000 /* microseconds per second */
#define TIME_TO_SLEEP  5       /* seconds */

// Constants
RTC_DATA_ATTR int bootCount = 0;


// Variables


/**--------------------------------------------------------------------------
 * Hardware/Software Configuration
 *---------------------------------------------------------------------------*/

void setup() {
 
  DEBUG_BEGIN(115200);                // Higher serial port speed 115200
  delay(1000);                      // Allow the Serial port to connect
  DEBUG_PRINTLN("");

// Example: JSON response from a sensor API
    const char* json = R"(
        {
            "sensor": "DHT11",
            "temperature": 32.5,
            "humidity": 65,
            "location": "Mumbai",
            "readings": [31.8, 32.1, 32.5]
        }
    )";
  
  JsonDocument doc;
    DeserializationError error = deserializeJson(doc, json);

    if (error) {
        Serial.print("Parse failed: ");
        Serial.println(error.c_str());
        return;
    }

    // Access fields
    const char* sensor   = doc["sensor"];      // "DHT11"
    float temperature    = doc["temperature"]; // 32.5
    int humidity         = doc["humidity"];    // 65
    const char* location = doc["location"];   // "Mumbai"

    Serial.printf("Sensor: %sn", sensor);
    Serial.printf("Temp: %.1f°C, Humidity: %d%%n", temperature, humidity);

    // Access array
    JsonArray readings = doc["readings"];
    for (float r : readings) {
        Serial.printf("Reading: %.1fn", r);
    }
}

/**--------------------------------------------------------------------------
 * Master/Main Loop
 *---------------------------------------------------------------------------*/
void loop() {
 
}

/**--------------------------------------------------------------------------
 * Functions & Helper Code
 *---------------------------------------------------------------------------*/
