#define LED_RED_1   13
#define PUSH_1      15
#define TIME_ON     5000

void setup() {
  pinMode(LED_RED_1, OUTPUT);
  pinMode(PUSH_1, INPUT);
  Serial.begin(9600);
}

void loop() {
  
  int switchStatus = digitalRead(PUSH_1);
  Serial.println(switchStatus);

  if (switchStatus == HIGH) {
    ledOn(LED_RED_1);
    ledOff(LED_RED_1);
  }

}

void redLedOn(int ledPin){
    ledOn(ledPin);
}

void ledOn(int ledPin){
  setLed(ledPin, HIGH);
  delay(TIME_ON);
}

void ledOff(int ledPin){
  setLed(ledPin, LOW);
  delay(TIME_ON);
}

void setLed(int ledPin, uint8 state){
    digitalWrite(ledPin, state);
}