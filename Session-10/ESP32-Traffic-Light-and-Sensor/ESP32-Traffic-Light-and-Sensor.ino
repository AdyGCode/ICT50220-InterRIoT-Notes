#define TRIG_PIN 32
#define ECHO_PIN 33
#define LED_RED 18
#define LED_YELLOW 19
#define LED_GREEN 21

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void loop() {
  // Send a short pulse on the trigger pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the time it takes for the pulse to return
  long duration = pulseIn(ECHO_PIN, HIGH);
  Serial.println(duration);
  // Convert the time into a distance
  float distance = duration * 0.034 / 2;

  // If a vehicle is detected
  if (distance < 100) {
    // Turn off the green light
    digitalWrite(LED_GREEN, LOW);

    // Wait for some time before turning on the red light
    delay(5000);

    // Turn on the red light
    digitalWrite(LED_RED, HIGH);

    // Wait for some time before turning off the red light
    delay(5000);

    // Turn off the red light
    digitalWrite(LED_RED, LOW);

    // Wait for some time before turning on the yellow light
    delay(3000);

    // Turn on the yellow light
    digitalWrite(LED_YELLOW, HIGH);

    // Wait for some time before turning off the yellow light
    delay(3000);

    // Turn off the yellow light
    digitalWrite(LED_YELLOW, LOW);

    // Wait for some time before turning on the green light
    delay(5000);

    // Turn on the green light
    digitalWrite(LED_GREEN, HIGH);
  } else {
    // If no vehicle is detected, keep the green light on
    digitalWrite(LED_GREEN, HIGH);
  }
}
