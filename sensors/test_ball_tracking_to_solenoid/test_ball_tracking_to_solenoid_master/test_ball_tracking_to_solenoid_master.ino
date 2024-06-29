// Code copied from solenoid_test_master.ino
/*
 * This code is for the master i2c microcontroller
 */
#include <Wire.h>

// Define the function signature
typedef void (*FunctionPointer)();

// Enum for gamestates
enum stateType {
  POWER_ON,
  IDLE,
  GAME_INIT,
  GAME_PROCESS,
  SCORING,
  BALL_RETRIEVAL,
  WINNER,
  ERROR = -1
};

/* 
 * GLOBAL VARIABLES: SETUP FOR EACH SLAVE DEVICES
 */
// Different states the slave microcontroller should
// Store the information output from each slave
// One int per slave
// The index matches the index variable in each SampleSlave... function
bool SLAVE_STATES[1] = {false};

// Functions used for slaves (One for each)
void sampleSlaveInputFromMaster() {
  int address = 9;
  int informationByteLength = 1; // how many bytes long is each transmission
  int index = address-8; // because address starts on 8

  // Transmit to slave
  Wire.beginTransmission(address);
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Write state index address-8
  /*process SLAVE_STATES[index] into a sendable format*/
  Wire.write(SLAVE_STATES[0]);
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Wire.write() function goes here
  Wire.endTransmission();
}
void sampleSlaveOutputToMaster() {
  int address = 8;
  int informationByteLength = 1; // how many bytes long is each transmission
  int index = address-8; // because address starts on 8

  // Request and read data from slave
  Wire.requestFrom(address, informationByteLength);
  while (Wire.available()){ // Slave may send less than informationByteLength
    int data = Wire.read();
    SLAVE_STATES[index] = data;
  }
  // After data received, we can update states of other slaves
  // SLAVE_STATES[index_of_slave_affected] = whatever
}

// Number of slave boards to connect to
const int NUMBER_OF_SLAVES = 2; 
// Array of functions to execute when processing each slave microcontroller
// We will iterate through this array and run each function
const FunctionPointer SLAVE_FUNCTIONS[NUMBER_OF_SLAVES] = {
  // Input slave may and should receive diff inputs if gamestate changes (e.g.
  // paddle should not work during idle state)
  sampleSlaveInputFromMaster,
  sampleSlaveOutputToMaster
};


int counter = 0;
void setup() {
  // Start the I2C connection as the master
  Wire.begin();
  // Serial Connection
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() {
  // MOVE FSM HERE
  /*switch (current_state) {
    case POWER_ON:
      current_state = IDLE;
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
    case SCORING:
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
  }*/

  counter++;
  if (counter % 1000 == 0) {
    SLAVE_STATES[0] = !SLAVE_STATES[0];
  } 

  /*FSM state change code*/
  /*the loop thru all funciosn and run them*/
  /*each function - will call the state and figure out what they should do based on the state*/
  for(int i = 0; i < NUMBER_OF_SLAVES; i++){
    SLAVE_FUNCTIONS[i]();
  }
  digitalWrite(LED_BUILTIN, SLAVE_STATES[0]);
  delay(1);
}

// Old code used as arduino master with rasp pi camera slave
// const int SLAVE_ADDR = 9;
// const int BUF_SIZE = 64;
// const int NUM_BYTE_REQUEST = 11;

// void loop() {
//   char buf[BUF_SIZE] = {0};

//   Wire.requestFrom(SLAVE_ADDR, NUM_BYTE_REQUEST); 
//   int i = 0;
//   while (Wire.available()) { // While data is available to read
//     char c = Wire.read(); // Read a byte from the I2C buffer
//     buf[i] = c;
//     i++;
//   }
//   Serial.print("Received: ");
//   Serial.print(buf);
//   Serial.print("\n");

//   if (buf[0] != ':' || buf[6] != ':') {
//     Wire.requestFrom(SLAVE_ADDR, NUM_BYTE_REQUEST * 5); 
//     Serial.print("Resetting buffer\n");
//     int i = 0;
//     while (Wire.available()) { // While data is available to read
//       char c = Wire.read(); // Read a byte from the I2C buffer
//       Serial.print(c); // Print the byte to the serial monitor
//       i++;
//     }
//     Serial.print("\n");
//   }
  
//   delay(100); // Wait for 1 second before requesting data again
// }

