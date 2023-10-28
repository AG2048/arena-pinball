#include <Servo.h>

Servo myservo;  // Create a Servo object

int servoPin = 9;      // Define the pin to which the servo is connected
int buttonPin = 2;     // Define the pin to which the button is connected
int servoAngle = 0;    // Current servo angle
int buttonState = 0;   // Current state of the button
int lastButtonState = 0; // Previous state of the button
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  myservo.attach(servoPin);  // Attach the servo to the specified pin
  pinMode(buttonPin, INPUT_PULLUP);  // Enable internal pull-up resistor for the button pin
}

void loop() {
  // Read the state of the button
  int reading = digitalRead(buttonPin);

  // Check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Check for button debouncing
  if (millis() - lastDebounceTime > debounceDelay) {
    // If the button state has changed, update the button state
    if (reading != buttonState) {
      buttonState = reading;

      // If the button is pressed, toggle the servo between 0 and 90 degrees
      if (buttonState == LOW) {
        if (servoAngle == 0) {
          servoAngle = 90;
        } else {
          servoAngle = 0;
        }
        myservo.write(servoAngle);
      }
    }
  }

  lastButtonState = reading;
}
