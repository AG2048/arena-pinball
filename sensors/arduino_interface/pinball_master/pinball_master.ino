/*
 * This code is for the master i2c microcontroller
 */
#include <Wire.h>

// Define the function signature
typedef void (*FunctionPointer)();

/* 
 * GLOBAL VARIABLES: SETUP FOR EACH SLAVE DEVICES
 */
// Different states the slave microcontroller should
// Store the information output from each slave
// One int per slave
// The index matches the index variable in each SampleSlave... function
const int[] SLAVE_STATES = {

}

// Functions used for slaves (One for each)
void sampleSlaveInputFromMaster() {
  int address = 8;
  int informationByteLength = 5; // how many bytes long is each transmission
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
  /*wire.write(that)*/
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Wire.write() function goes here
  // Wire.write() function goes here
  Wire.endTransmission();
}
void sampleSlaveOutputToMaster() {
  int address = 9;
  int informationByteLength = 5; // how many bytes long is each transmission
  int index = address-8; // because address starts on 8

  // Request and read data from slave
  Wire.requestFrom(address, informationByteLength);
  while (Wire.available()){ // Slave may send less than informationByteLength
    // data = Wire.read();
  }
  // After data received, we can update states of other slaves
  // SLAVE_STATES[index_of_slave_affected] = whatever
}

// Number of slave boards to connect to
const int NUMBER_OF_SLAVES = 2; 
// Array of functions to execute when processing each slave microcontroller
// We will iterate through this array and run each function
const FunctionPointer SLAVE_FUNCTIONS = {
  // Input slave may and should receive diff inputs if gamestate changes (e.g.
  // paddle should not work during idle state)
  sampleSlaveInputFromMaster,
  sampleSlaveOutputToMaster
};



void setup() {
  // Start the I2C connection as the master
  Wire.begin();
  // Serial Connection
  Serial.begin(9600);
}

void loop() {
  // MOVE FSM HERE
  /*FSM state change code*/
  /*the loop thru all funciosn and run them*/
  /*each function - will call the state and figure out what they should do based on the state*/
  for(int i = 0; i < NUMBER_OF_SLAVES; i++){
    SLAVE_FUNCTIONS[i]();
  }
}
