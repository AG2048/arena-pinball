/*
 * This code is for any slave microcontroller that will only output information TO the master, this is DIFFERENT naming convention from the i2c.md file.
 */
#include <Wire.h>

/*
 * GLOBAL VARIABLES: SETUP FOR ALL DEVICES:
 */
// The address the slave joins the bus
const int SLAVE_BUS_ADDRESS = 8;
// The number of bytes the master will request every time
const int OUTPUT_BYTE_SIZE = 2;
// Update this function to create uint8_t array to be sent, based on global variables.
// Update the function argument to include ALL global variables
uint8_t* output_from_global_variables(){
    static uint8_t output_data[OUTPUT_BYTE_SIZE];
    // Fill data...
    return outputData;
}

void setup() {
  // Start the I2C connection using the specific address
  Wire.begin(SLAVE_BUS_ADDRESS);  
  // Define the interrupt onRequest function
  Wire.onRequest(requestEvent); 
  // Serial Connection
  Serial.begin(9600);           
}

void loop() {
  // Perform Normal Function Here
  delay(100)
}

// Interrupt function run whenever this slave is requested information from master.
// Prepare output information of size OUTPUT_BYTE_SIZE using output_from_global_variables based on global variables.
void requestEvent() {
  uint8_t* outputData = getStaticData();
  Wire.write(outputData);
}