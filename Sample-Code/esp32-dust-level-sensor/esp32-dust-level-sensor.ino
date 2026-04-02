#include "debug.h"
#include "secrets.h"

int pin = 14;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 30000;  //sampe 30s ;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup() {
  DEBUG_BEGIN(9600);
  DEBUG_PRINTLN("Starting dust sensing")
  pinMode(pin, INPUT);
  starttime = millis();  //get the current time;
}

void loop() {
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy + duration;

  if ((millis() - starttime) > sampletime_ms)  //if the sampel time == 30s
  {
    // Integer percentage 0=>100
    ratio = lowpulseoccupancy / (sampletime_ms * 10.0);

    // using spec sheet curve
    concentration = 1.1 * pow(ratio, 3) - 3.8 * pow(ratio, 2) + 520 * ratio + 0.62;

    DEBUG_PRINT(lowpulseoccupancy);
    DEBUG_PRINT(",");
    DEBUG_PRINT(ratio);
    DEBUG_PRINT(",");
    DEBUG_PRINTLN(concentration);

    lowpulseoccupancy = 0;
    starttime = millis();
  }
}
