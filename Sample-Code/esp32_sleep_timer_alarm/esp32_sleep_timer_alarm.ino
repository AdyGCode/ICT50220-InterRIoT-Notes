/**
 * ESP32 Sleepy Time 3
 *
 * Demo of:
 * - Putting ESP32 to sleep
 * - Waking up ESP32 using Real Time Clock
 *
 * Filename:        esp32_sleep_timer_alarm.ino
 *
 * Assessment Name: n/a
 * Due:             n/a
 * Name:            Adrian Gould
 *
 */


/**--------------------------------------------------------------------------
 * External Source, Package, Module includes
 *---------------------------------------------------------------------------*/


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

  ++bootCount;
  DEBUG_PRINTLN("Boot number: " + String(bootCount));

  print_wakeup_reason();

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * MICRO_S_TO_S_FACTOR);
  DEBUG_PRINTLN("Sleeping every " + String(TIME_TO_SLEEP) + "seconds.");

  DEBUG_PRINTLN("In 1 second I will sleeeeeeeeep...");
  delay(1000);
  DEBUG_FLUSH();
  
  esp_deep_sleep_start();

  DEBUG_PRINTLN("If this displays then something is definitely WRONG!");
}

/**--------------------------------------------------------------------------
 * Master/Main Loop
 *---------------------------------------------------------------------------*/
void loop() {
 
}

/**--------------------------------------------------------------------------
 * Functions & Helper Code
 *---------------------------------------------------------------------------*/

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeupReason;

  wakeupReason = esp_sleep_get_wakeup_cause();

  switch (wakeupReason) {
    case ESP_SLEEP_WAKEUP_EXT0:
      DEBUG_PRINTLN("Wakeup caused by external signal using RTC_IO");
      break;
    case ESP_SLEEP_WAKEUP_EXT1:
      DEBUG_PRINTLN("Wakeup caused by external signal using RTC_CNTL");
      break;
    case ESP_SLEEP_WAKEUP_TIMER:
      DEBUG_PRINTLN("Wakeup caused by timer");
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      DEBUG_PRINTLN("Wakeup caused by touchpad");
      break;
    case ESP_SLEEP_WAKEUP_ULP:
      DEBUG_PRINTLN("Wakeup caused by ULP program");
      break;
    default:
      Serial.printf("Wakeup not caused by deep sleep: %d",wakeupReason);
      break;
  }
}


void print_wakeup_touchpad(){
  int wakeupTouch = esp_sleep_get_touchpad_wakeup_status();

  #if CONFIG_IDF_TARGET_ESP32
  switch(wakeupTouch) {
    case 0:
      DEBUG_PRINTLN("Touch detected on GPIO 4");
      break;
    case 1:
      DEBUG_PRINTLN("Touch detected on GPIO 0");
      break;
    case 2:
      DEBUG_PRINTLN("Touch detected on GPIO 2");
      break;
    case 3:
      DEBUG_PRINTLN("Touch detected on GPIO 15");
      break;
    case 4:
      DEBUG_PRINTLN("Touch detected on GPIO 13");
      break;
    case 5:
      DEBUG_PRINTLN("Touch detected on GPIO 12");
      break;
    case 6:
      DEBUG_PRINTLN("Touch detected on GPIO 14");
      break;
    case 7:
      DEBUG_PRINTLN("Touch detected on GPIO 27");
      break;
    case 8:
      DEBUG_PRINTLN("Touch detected on GPIO 33");
      break;
    case 9:
      DEBUG_PRINTLN("Touch detected on GPIO 32");
      break;
    default:
      DEBUG_PRINTLN("Wakeup not by touchpad");
      break;
  }
  #else
    if (wakeupTouch < TOUCH_PAD_MAX) {
      Serial.printf("Touch detected on GPIO %d\n", touchPin);
    } else {
      DEBUG_PRINTLN("Wakeup not by touchpad");
    }
  #endif
}





