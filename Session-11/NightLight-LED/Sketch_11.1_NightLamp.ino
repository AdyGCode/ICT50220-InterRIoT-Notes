/**********************************************************************
  Filename    : NightLamp
  Description : Controlling the brightness of LED by photoresistor.
  Auther      : www.freenove.com
  Modification: 2024/06/18
**********************************************************************/
#define PIN_ANALOG_IN   4
#define PIN_LED         12
#define CHAN            0
#define LIGHT_MIN       372
#define LIGHT_MAX       2048
void setup() {
  ledcAttachChannel(PIN_LED, 1000, 12, CHAN);
  Serial.begin(9600);
}

int oldADC = 0;

void loop() {
  int adcVal = analogRead(PIN_ANALOG_IN); //read adc
  int pwmVal = 4095-map(constrain(adcVal, LIGHT_MIN, LIGHT_MAX), LIGHT_MIN, LIGHT_MAX, 0, 4095);  // adcVal re-map to pwmVal
  ledcWrite(PIN_LED, pwmVal);    // set the pulse width.
  delay(10);

  if (oldADC != adcVal) {
    oldADC = adcVal;
    Serial.print(adcVal);
    Serial.print("/t");
    Serial.println(pwmVal);
  }

}
