/**
 * ESP32 Sleepy Modes
 *
 * See Also: 
 *
 */

#define uS_TO_S_FACTOR 1000000 /* microseconds per second */
#define TIME_TO_SLEEP 5        /* seconds */

RTC_DATA_ATTR int bootCount = 0;

void setup() {
  Serial.begin(9600);
  delay(1000);

  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  print_wakeup_reason();

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Set up ESP32 to sleep every " + String(TIME_TO_SLEEP) + " seconds");

  Serial.println("Going to sleep in 1 second...");
  delay(1000);
  Serial.flush();
  esp_deep_sleep_start();

  Serial.println("This will never get executed as I'm, already asleep");
}

void loop() {
  // put your main code here, to run repeatedly...
}

void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Wakeup caused by external signal using RTC_IO");
      break;
    case ESP_SLEEP_WAKEUP_EXT1:
      Serial.println("Wakeup caused by external signal using RTC_CNTL");
      break;
    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Wakeup caused by timer");
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      Serial.println("Wakeup caused by touchpad");
      break;
    case ESP_SLEEP_WAKEUP_ULP:
      Serial.println("Wakeup caused by ULP program");
      break;
    default:
      Serial.printf("Wakeup not caused by deep sleep: %d\n", wakeup_reason);
      break;
  }
}
