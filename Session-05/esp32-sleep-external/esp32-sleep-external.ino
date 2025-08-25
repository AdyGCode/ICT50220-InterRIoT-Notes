/**
 * ESP32 Sleepy Modes
 *
 * See Also: 
 *
 */

#define BUTTON_PIN_BITMASK 0x200000000  // 2^33 in hex

RTC_DATA_ATTR int bootCount = 0;


void setup() {
  Serial.begin(115200);
  delay(1000);

  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  print_wakeup_reason();

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 1); // 1 = high

  Serial.println("Going to sleep now...");
  delay(1000);
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

