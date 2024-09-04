
#define RETRY_PERIOD 1000
#define RETRY_ADJUSTMENT 500
#define MAX_ATTEMPTS 5

#define LED_ON_PERIOD 100
#define LED_RED_1   18

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode (LED_RED_1, OUTPUT);

  Serial.begin (115200);

  xTaskCreatePinnedToCore (
    loop2,     // Function to implement the task
    "loop2",   // Name of the task
    1000,      // Stack size in bytes
    NULL,      // Task input parameter
    0,         // Priority of the task
    NULL,      // Task handle.
    0          // Core where the task should run
  );
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite (LED_RED_1, HIGH);
  delay (LED_ON_PERIOD);  
  digitalWrite (LED_RED_1, LOW);
  delay (LED_ON_PERIOD);
}

// the loop2 function also runs forver but as a parallel task
void loop2 (void* pvParameters) {
  while (1) {
    Serial.print ("Hello");
    delay (500); 
    Serial.println (" World");
    delay (500); 
  }
}
