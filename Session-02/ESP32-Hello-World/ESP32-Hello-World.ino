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

void ledOn(int ledPin){
  digitalWrite(ledPin, HIGH);
  delay(TIME_ON);
}

void ledOff(int ledPin){
  digitalWrite(ledPin, LOW);
  delay(TIME_ON);
}