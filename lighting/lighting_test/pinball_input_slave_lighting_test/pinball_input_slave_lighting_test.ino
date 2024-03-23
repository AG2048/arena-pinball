/*
 * This code is for any slave microcontroller that will only receive information FROM the master, this is DIFFERENT naming convention from the i2c.md file.
 */
#include <Wire.h>
#include <FastLED.h>

const int len = 8, numLedStrips = 4;
int state = 0;
int pos[2];
struct CRGB leds[numLedStrips][len];

/*
 * GLOBAL VARIABLES: SETUP FOR ALL DEVICES:
 */
const int SLAVE_BUS_ADDRESS = 9; // 8-127 is available address
// Update this function to update global variables based on user input
void input_update_global_variables(uint8_t list[], size_t list_size){
  // TODO
  state = list[0];
  pos[0] = (list[1] << 8) | list[2];
  pos[1] = (list[3] << 8) | list[4];
  return;
}; 

void setup() {
  // Start the I2C connection using the specific address
  Wire.begin(SLAVE_BUS_ADDRESS);  
  // Define the interrupt onReceive function
  Wire.onReceive(receiveEvent); 
  // Serial Connection
  pinMode(LED_BUILTIN, OUTPUT);

  LEDS.addLeds<WS2812B, 13, GRB>(leds[0], len);
  LEDS.addLeds<WS2812B, 12, GRB>(leds[1], len);
  LEDS.addLeds<WS2812B, 11, GRB>(leds[2], len);
  LEDS.addLeds<WS2812B, 10, GRB>(leds[3], len);

  Serial.begin(9600);           
}

void loop() {
  digitalWrite(LED_BUILTIN, state);
  // Perform Normal Function Here

  for (int i = 0; i < numLedStrips; i++) for (int j = 0; j < len; j++) leds[i][j] = CRGB(0, 0, 0);
  leds[pos[0]][pos[1]] = CRGB(255, 0, 0);

  FastLED.show();

  delay(100);
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