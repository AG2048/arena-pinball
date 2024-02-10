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

// TODO is enum better
#define POWER_ON 10
#define IDLE 20
#define GAME_INIT 30
#define GAME_PROCESS 40
#define GAME_OVER 50
#define WINNER 60
#define ERROR -99

bool start_button = 0;
int home = 0;  // Left or right goal
int away = 0;  // Left or right goal
int win = 0;  // If there is a winner
int current_state = POWER_ON;

#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
}

int x = 0;

void loop() {
  /*
  #define POWER_ON 10
  #define IDLE 20
  #define GAME_INIT 30
  #define GAME_PROCESS 40
  #define GAME_OVER 50
  #define WINNER 60
  #define ERROR -99
  */

  // FSM Control
  // TODO maybe no use for break, because it can be only in one case
  switch (current_state) {
    case IDLE:
      if (button)
        current_state = GAME_INIT;
      // Else, current_state = IDLE still
      break;
    case GAME_INIT:
      current_state = GAME_PROCESS;
      break;
    case GAME_PROCESS:
      // Either one true for score
      if (home || away) {
        current_state = GAME_OVER;
      }
      // Else, current_state = GAME_PROCESS
      break;
    case GAME_OVER:
      if (win)
        current_state = WINNER;
      else
        current_state = GAME_INIT;
      break;
    case WINNER:
      current_state = IDLE;
      break;
    default:
      current_state = IDLE;
      // code block
  }

  // FSM Action
  switch (current_state) {
    case IDLE:
      // Code for IDLE
      break;
    case GAME_INIT:
      // Code for GAME_INIT
      break;
    case GAME_PROCESS:
      // Code for GAME_PROCESS
      break;
    case GAME_OVER:
      // Code for GAME_OVER
      break;
    case WINNER:
      // Cod for WINNER
      break;
    default:
      // ???
  }
}

/*
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
*/
