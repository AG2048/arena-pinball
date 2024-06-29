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

void cameraSlaveOutputToMaster() {
  const int address = 10;
  const int informationByteLength = 11;
  // TODO: So each index correspond to one slave?
  const int index = address-8; // because address starts on 8
  const int buf_size = informationByteLength * 6;
  const int X_MAX = 1640;
  const int Y_MAX = 1232;

  char buf[buf_size] = {0};
  do {
    Wire.requestFrom(address, informationByteLength); 
    int i = 0;
    while (Wire.available()) { // While data is available to read
      char c = Wire.read(); // Read a byte from the I2C buffer
      buf[i] = c;
      i++;
    }
    buf[i] = NULL;
    Serial.print("Received from camera slave: ");
    Serial.print(buf);
    Serial.print("\n");
    if (i != informationByteLength) {
      Serial.println("Camera is not responding");
      return;
    }

    // RaspPi i2c is unreliable, so we check to see the msg is in correct format
    if (buf[0] == ':' && buf[6] == ':') {
      break;
    } 

    // Otherwise "overconsume" the pigpiod buffer to reset it
    Wire.requestFrom(address, informationByteLength * 5); 
    Serial.print("Resetting buffer of camera slave\n");
    while (Wire.available()) {
      char c = Wire.read();
      Serial.print(c);
    }
    Serial.print("\n");
  } while (true);

  buf[6] = NULL;
  const int x_coord = String(buf + 1).toInt();
  const int y_coord = String(buf + 7).toInt();
  Serial.print("Parsed coordinates from camera slave: ");
  Serial.print(x_coord);
  Serial.print(";");
  Serial.println(y_coord);

  // TODO: For now we just set SLAVE_STATES[0] to a new value (whatever SLAVE_STATES even means)
  SLAVE_STATES[0] = x_coord > X_MAX * 0.8;
}
// Number of slave boards to connect to
const int NUMBER_OF_SLAVES = 3; 
// Array of functions to execute when processing each slave microcontroller
// We will iterate through this array and run each function
const FunctionPointer SLAVE_FUNCTIONS[NUMBER_OF_SLAVES] = {
  // Input slave may and should receive diff inputs if gamestate changes (e.g.
  // paddle should not work during idle state)
  sampleSlaveInputFromMaster,
  sampleSlaveOutputToMaster,
  cameraSlaveOutputToMaster
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

  // counter++;
  // if (counter % 1000 == 0) {
  //   SLAVE_STATES[0] = !SLAVE_STATES[0];
  // } 

  /*FSM state change code*/
  /*the loop thru all funciosn and run them*/
  /*each function - will call the state and figure out what they should do based on the state*/
  for(int i = 0; i < NUMBER_OF_SLAVES; i++){
    SLAVE_FUNCTIONS[i]();
  }
  digitalWrite(LED_BUILTIN, SLAVE_STATES[0]);
  delay(1);
}


