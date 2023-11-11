#include "esp_camera.h"

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#define RED_THRESHOLD 50

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_RGB565;
  
  config.frame_size = FRAMESIZE_VGA;
  config.jpeg_quality = 4;
  config.fb_count = 2;
  
  
  // Initialize the Camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x. Rebooting...\n", err);
    ESP.restart();
  }
}

void loop() {
  // Capture a frame
  camera_fb_t * fb = NULL;
  fb = esp_camera_fb_get();
  
  if(!fb) {
    Serial.println("Camera capture failed");
    delay(1000);
    return;
  }
  Serial.println("START");
  
  int width = fb->width;
  int height = fb->height;
  int sum_x = 0, sum_y = 0, num_red_pixels = 0;
  int cnt = 0;

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      int index = y*2*width + 2*x;
      uint8_t leftPixVal = fb->buf[index];
      uint8_t rightPixVal = fb->buf[index+1];
      uint16_t sixteenBit = (leftPixVal << 8) | rightPixVal;

      uint8_t r = sixteenBit >> 11;
      uint8_t g = (sixteenBit >> 5) & 0x3F;
      uint8_t b = sixteenBit & 0x1F;
      // r = r << 3;  // Shift left 3 bits to scale from 5 bits to 8 bits
      // g = g << 2;  // Shift left 2 bits to scale from 6 bits to 8 bits
      // b = b << 3;  // Shift left 3 bits to scale from 5 bits to 8 bits
      cnt++;

      if (x == width-1 && y == height-1) {
        // Serial.printf("RGB: %d %d %d, %d\n", red, green, blue, sixteenBit);
        // Serial.printf("%02x%02x = %04x, CNT:%d\n", leftPixVal, rightPixVal, sixteenBit, cnt);
      }

      if(r >= 14 && r <= 31 && g <= 14 && b <= 14){
        sum_x += x;
        sum_y += y;
        num_red_pixels++;
      }
    }
  }

  // Ave red pixels = sum (x * red pixel location) / sum x
  if (num_red_pixels > 0) {
    int avg_x = sum_x / num_red_pixels;
    int avg_y = sum_y / num_red_pixels;

    int ave_x_rel_pos = avg_x / (width / 10);
    int ave_y_rel_pos = avg_y / (height / 10);

    for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
        if(i == ave_y_rel_pos && j == ave_x_rel_pos)
          Serial.print("X");
        else Serial.print(".");
      }
      Serial.print("\n");
    }
  
    Serial.print("Average location of red pixels: (");
    Serial.print(avg_x);
    Serial.print(", ");
    Serial.print(avg_y);
    Serial.println(")");
  } else {
    for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
	Serial.print(".");
      }
      Serial.print("\n");
    }
    Serial.println("No red pixels found");
  }
  /*
  ..........
  ..........
  .....X....
  ..........
  ..........
  ..........
  ..........
  */


  // Once you're done with the frame buffer data, return it back to the driver
  esp_camera_fb_return(fb);

  // Add a delay between frames
  delay(100);
}

