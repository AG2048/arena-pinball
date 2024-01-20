/*
 * This code is for any slave microcontroller that will only receive information FROM the master, this is DIFFERENT naming convention from the i2c.md file.
 */
#include <Wire.h>

/*
 * GLOBAL VARIABLES: SETUP FOR ALL DEVICES:
 */
const int SLAVE_BUS_ADDRESS = 8;
// Update this function to update global variables based on user input
void input_update_global_variables(uint8_t list[], size_t list_size){
  // TODO
  return;
}; 

void setup() {
  // Start the I2C connection using the specific address
  Wire.begin(SLAVE_BUS_ADDRESS);  
  // Define the interrupt onReceive function
  Wire.onReceive(receiveEvent); 
  // Serial Connection
  Serial.begin(9600);           
}

void loop() {
  // Perform Normal Function Here
  delay(100)
}

// Interrupt function run whenever this slave received information from master.
// Records all bytes of information in a byte array, and process them into global variable using the input_update_global_variables() function.
void receiveEvent(int howMany) {
  uint8_t input_data[howMany];
  int index = 0;
  while(Wire.available()) {
    input_data[index++] = Wire.read(); // receive byte
  }
  input_update_global_variables(input_data, list_size);
}