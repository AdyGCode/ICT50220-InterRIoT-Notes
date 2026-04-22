#include "Air_Quality_Sensor.h"

AirQualitySensor sensor(35);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while (!Serial);

    Serial.println("Waiting sensor to init...");
    delay(5000);

    if (sensor.init()) {
        Serial.println("Sensor ready.");
    } else {
        Serial.println("Sensor ERROR!");
    }
}

void loop() {
  // put your main code here, to run repeatedly:
    int quality = sensor.slope();

    Serial.print("Sensor value: ");
    Serial.println(sensor.getValue());

    if (quality == AirQualitySensor::FORCE_SIGNAL) {
        Serial.println("High pollution! Force signal active.");
    } else if (quality == AirQualitySensor::HIGH_POLLUTION) {
        Serial.println("High pollution!");
    } else if (quality == AirQualitySensor::LOW_POLLUTION) {
        Serial.println("Low pollution!");
    } else if (quality == AirQualitySensor::FRESH_AIR) {
        Serial.println("Fresh air.");
    }

    delay(1000);
}
