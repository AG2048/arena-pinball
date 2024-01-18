/*
send() and receive() for the slave

send():
	on request

receive():
	on transmission
	or on receive

Global variable: RECEIVED_INFORMATION: false

A universal recieve function for all the slaves
- the recieve is going to be the same for every slave anyways

For each individual slave we write a parsing function

set 2 global variables before setup()
RECEIVED_INFORMATION = false;
INFORMATION = 

if INFORMATION true:
	process information()

for user input:
	atmega
*/

#include <Wire.h>

// Global flags
int RECEIVED_INFORMATION = false;
int INFORMATION = 0;

void processInformation() {
  if (RECEIVED_INFORMATION) {
    for (int i = 0; i < INFORMATION; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
    INFORMATION = 0;
  }
}

void receiveEvent() {
  // Receive the number of blinks from the master
  INFORMATION = Wire.read();
  Serial.print("Received instruction to blink ");
  Serial.println(INFORMATION);
	// Master: hey I would like this info back
	// *50ms*
	// Master: hey what is the information I wanted
	// So process info ASAP
	RECEIVED_INFORMATION = true;
}

void setup() {
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// void loop() {
// 	if (RECEIVED_INFORMATION) {
// 		// Act according to the information
// 	}
// 	// Check if information is true,
// 	// if it is true, set it to false, process the information
// 	// Process information
// }
