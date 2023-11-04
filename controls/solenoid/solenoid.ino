// the setup function runs once when you press reset or power the board
int solState;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(8, OUTPUT);
  pinMode(9, INPUT_PULLUP);
  solState = LOW;

}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(9)) {
    solState = LOW;
  } else {
    solState = HIGH;
  }
  digitalWrite(8, solState);  // turn the LED on (HIGH is the voltage level)
  // delay(500);                      // wait for a second
}
