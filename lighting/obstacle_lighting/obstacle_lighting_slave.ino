/*
 * This code is for any slave microcontroller that will only receive information
 * FROM the master, this is DIFFERENT naming convention from the i2c.md file.
 */
#include <FastLED.h>
#include <Wire.h>

int len = 6, numStrips = 1;
int input[16], ledState[16];
int count[16], state;
struct CRGB leds[16][6], colour;

/*
 * GLOBAL VARIABLES: SETUP FOR ALL DEVICES:
 */
const int SLAVE_BUS_ADDRESS = 9;  // 8-127 is available address
// Update this function to update global variables based on user input
void input_update_global_variables(uint8_t list[], size_t list_size) {
  // TODO
  state = list[0];
  for (int i = 0; i < 2; i++) {  // make less confusing
    for (int j = 0; j < 8; j++) {
      input[(i * 8) + j] = (list[i + 1] >> (7 - j)) & 1;
    }
  }
  return;
}

bool isRed(int x) {
  if (x <= 7) return true;
  return false;
}

bool isPaddle(int x) {
  if (x <= 5 || (x >= 8 && x <= 13)) return true;
  return false;
}

bool isBumper(int x) {
  if (x == 6 || x == 7 || x == 14 || x == 15) return true;
  return false;
}

void sequentialLed(int i) {  // must set led state back to 0 after duration
  for (int j = 0; j < len; j++) {
    if (j == count[i]) {
      leds[i][j] = colour;
    } else {
      leds[i][j] = CRGB(255, 255, 255);
    }
  }

  count[i]++;

  if (count[i] >= len) {
    ledState[i] = 0;
  }
}

void blinkLed(int i) {
  if (count[i] % 2 == 0) {
    for (int j = 0; j < len; j++) {
      leds[i][j] = colour;
    }
  } else {
    for (int j = 0; j < len; j++) {
      leds[i][j] = CRGB(255, 255, 255);
    }
  }

  count[i]++;

  if (count[i] >= 5) {
    ledState[i] = 0;
  }
}

void idleLed(int i) {
  for (int j = 0; j < len; j++) {
    leds[i][j] = CRGB(0, 255, 0);
  }
  ledState[i] = 0;
}

void setup() {
  // Start the I2C connection using the specific address
  Wire.begin(SLAVE_BUS_ADDRESS);
  // Define the interrupt onReceive function
  Wire.onReceive(receiveEvent);
  // Serial Connection
  pinMode(LED_BUILTIN, OUTPUT);

  LEDS.addLeds<WS2812B, 6, GRB>(leds[0], len);

  for (int i = 0; i < len; i++) {
    ledState[i] = 0;
    count[i] = 0;
  }

  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED_BUILTIN, state);
  // Perform Normal Function Here
  if (state == 0) {  // game idle

  } else if (state == 1) {  // game ongoing
    for (int i = 0; i < numStrips; i++) {
      if (isRed(i)) {
        colour = CRGB(255, 0, 0);
      } else {
        colour = CRGB(0, 0, 255);
      }

      if (input[i] == 1) {
        ledState[i] = 1;
        count[i] = 0;
      }

      if (ledState[i] == 1) {
        if (isPaddle(i)) {
          sequentialLed(i);
        } else if (isBumper(i)) {
          blinkLed(i);
        } else {  // spinners and border
        }
      } else {
        idleLed(i);
      }
    }
  } else {  // other
  }

  FastLED.show();
  delay(500);
}

// Interrupt function run whenever this slave received information from
// master. Records all bytes of information in a byte array, and process them
// into global variable using the input_update_global_variables() function.
void receiveEvent(int howMany) {
  uint8_t input_data[howMany];
  int index = 0;
  while (Wire.available()) {
    input_data[index++] = Wire.read();  // receive byte
  }
  input_update_global_variables(input_data, howMany);
}
