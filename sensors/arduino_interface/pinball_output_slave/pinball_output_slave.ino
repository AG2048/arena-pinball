/*
 * This code is for any slave microcontroller that will only output information TO the master, this is DIFFERENT naming convention from the i2c.md file.
 */
#include <Wire.h>

/*
 * GLOBAL VARIABLES: SETUP FOR ALL DEVICES:
 */

// Yes if button is pressed
// No if button is not pressed
bool button_state = false;
int FAKE_BUTTON_PIN = 2;


// The address the slave joins the bus
const int SLAVE_BUS_ADDRESS = 8; // 8-127 is available address
// The number of bytes the master will request every time
const int OUTPUT_BYTE_SIZE = 1;

// Update this function to create uint8_t array to be sent, based on global variables.
uint8_t* output_from_global_variables(){
    static uint8_t output_data[OUTPUT_BYTE_SIZE];
    // Fill data...
    output_data[0] = button_state;
    return output_data;
}


void setup() {
  // Start the I2C connection using the specific address
  Wire.begin(SLAVE_BUS_ADDRESS);  
  // Define the interrupt onRequest function
  Wire.onRequest(requestEvent); 
  // Serial Connection
  Serial.begin(9600);
  pinMode(FAKE_BUTTON_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);         
}

void loop() {
  // Perform Normal Function Here
  delay(100);
  button_state = digitalRead(FAKE_BUTTON_PIN);
  Serial.println(button_state);
  digitalWrite(LED_BUILTIN, button_state);
}

// Interrupt function run whenever this slave is requested information from master.
// Prepare output information of size OUTPUT_BYTE_SIZE using output_from_global_variables based on global variables.
void requestEvent() {
  uint8_t* outputData = output_from_global_variables();
  Wire.write(outputData, OUTPUT_BYTE_SIZE);
}