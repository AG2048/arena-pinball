/*
Copy older code or rewrite it

send() and receive() for the master

Master handling user input and i2c

Master will be doing polling


2 arduinos:
- master blinks 5 times, and let slave blink 5 times
- After slave blinks 7 times, and let the master blink back that many time

Error code system
- e.g. if anything transmits all 1s, then its error
- Master: send me your location
- Master: what is your location
- Slave: ???
- Slave: respond the error code
*/

#define POWER_ON 10
#define IDLE 20
#define GAME_INIT 30
#define GAME_PROCESS 40
#define GAME_OVER 50
#define WINNER 60
#define ERROR -99

#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
}

int x = 0;

void loop()
{
  // First, blink 5 times
  // Is this to simulate polling?
  // Each time that it loops back to the beginning
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
  }

  // Instruct the slave to blink 5 times
  Wire.beginTransmission(4);
  Wire.write(5);            // Send the number of blinks to the slave
  Wire.endTransmission();

  // Wait for slave to return data
  int requested_data = 0;
  while (requested_data != 0) {
    // Request 1 byte from slave @ address 4
    requested_data = Wire.requestFrom(4, 1);
  }
  int slaveBlinkCount = Wire.read();

  for (int i = 0; i < slaveBlinkCount; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
  }

  // 5 second delay
  delay(5000);
}
