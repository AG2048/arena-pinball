/*
 * This code is for any slave microcontroller that will only receive information FROM the master, this is DIFFERENT naming convention from the i2c.md file.
 */
#include <Wire.h>

int state = 0, solState = 0;

/*
 * GLOBAL VARIABLES: SETUP FOR ALL DEVICES:
 */
const int SLAVE_BUS_ADDRESS = 9; // 8-127 is available address
// Update this function to update global variables based on user input
void input_update_global_variables(uint8_t list[], size_t list_size){
  // TODO
  state = list[0];
  solState = list[1];
  return;
}; 

void setup() {
  // Start the I2C connection using the specific address
  Wire.begin(SLAVE_BUS_ADDRESS);  
  // Define the interrupt onReceive function
  Wire.onReceive(receiveEvent); 

  pinMode(8, OUTPUT);

  // Serial Connection
  Serial.begin(9600);           
}

void loop() {
  digitalWrite(LED_BUILTIN, state);

  if (!solState) {
    digitalWrite(8, LOW);
  } else {
    digitalWrite(8, HIGH);
  }

  delay(1000);
}

// Interrupt function run whenever this slave received information from master.
// Records all bytes of information in a byte array, and process them into global variable using the input_update_global_variables() function.
void receiveEvent(int howMany) {
  uint8_t input_data[howMany];
  int index = 0;
  while(Wire.available()) {
    input_data[index++] = Wire.read(); // receive byte
  }
  input_update_global_variables(input_data, howMany);
}