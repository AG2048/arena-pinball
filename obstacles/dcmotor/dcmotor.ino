/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-dc-motor
 */

// constants won't change
const int ENA_PIN = 9; // the Arduino pin connected to the EN1 pin L298N
const int IN1_PIN = 6; // the Arduino pin connected to the IN1 pin L298N
const int IN2_PIN = 5; // the Arduino pin connected to the IN2 pin L298N
const int max = 150;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins as outputs.
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(IN1_PIN, HIGH); // control motor A spins clockwise
  digitalWrite(IN2_PIN, LOW);  // control motor A spins clockwise

  for (int speed = 0; speed <= max; speed++) {
    analogWrite(ENA_PIN, speed); // control the speed
    //delay(10);
  }

  delay(2000); // rotate at maximum speed 1 seconds in in clockwise direction

  // change direction
  digitalWrite(IN1_PIN, LOW);   // control motor A spins anti-clockwise
  digitalWrite(IN2_PIN, HIGH);  // control motor A spins anti-clockwise
 
  delay(2000); // rotate at maximum speed 1 seconds in in anti-clockwise direction

  for (int speed = max; speed >= 0; speed--) {
    analogWrite(ENA_PIN, speed); // control the speed
    //delay(10);
  }

  delay(2000); // stop motor 1 second
}
