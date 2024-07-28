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
  LEFT_SCORING,
  RIGHT_SCORING,
  BALL_RETRIEVAL_IN_PROGRESS,
  GAME_OVER_LEFT_WIN,
  GAME_OVER_RIGHT_WIN,
  GAME_OVER_TIE,
  WINNER,
  NUM_STATES,
  ERROR = -1,
} current_state = POWER_ON;

int MAX_SCORE = 10;
bool start_button_pressed = 0;
bool timeout = 0;
bool ball_ready_dispensing = 0;
bool ball_pass_through_left_net = 0;
bool ball_pass_through_right_net = 0;
int left_score = 0;
int right_score = 0;
bool first_test = true;

/*
 * GLOBAL VARIABLES: SETUP FOR EACH SLAVE DEVICES
 */
// Different states the slave microcontroller should
// Store the information output from each slave
// One int per slave
// The index matches the index variable in each SampleSlave... function
uint8_t SLAVE_STATES[1] = {1};
uint8_t red = 0x00, blue = 0x00;

// Functions used for slaves (One for each)
void sampleSlaveInputFromMaster() {
  int address = 9;
  int informationByteLength = 1;  // how many bytes long is each transmission
  int index = address - 8;        // because address starts on 8

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
  Wire.write(red);
  Wire.write(blue);
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Wire.write() function goes here
  Wire.endTransmission();
}
void sampleSlaveOutputToMaster() {
  int address = 8;
  int informationByteLength = 1;  // how many bytes long is each transmission
  int index = address - 8;        // because address starts on 8

  // Request and read data from slave
  Wire.requestFrom(address, informationByteLength);
  while (Wire.available()) {  // Slave may send less than informationByteLength
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
    sampleSlaveInputFromMaster, sampleSlaveOutputToMaster};

int count = 0;

void setup() {
  // Start the I2C connection as the master
  Wire.begin();
  // Serial Connection
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  first_test = true;
}

void loop() {
  // MOVE FSM HERE
  if (!first_test) {
    red = 0b00000000;
    blue = 0b00000000;
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    red = 0b10000000;  // 128
    blue = 0b00000000;
    digitalWrite(LED_BUILTIN, LOW);
    first_test = false;
  }

  delay(1000);

  /*FSM state change code*/
  /*the loop thru all functions and run them*/
  /*each function - will call the state and figure out what they should do based
   * on the state*/
  for (int i = 0; i < NUMBER_OF_SLAVES; i++) {
    SLAVE_FUNCTIONS[i]();
  }
  digitalWrite(LED_BUILTIN, SLAVE_STATES[0]);
}
