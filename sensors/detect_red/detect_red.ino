  int cnt = 0;
  for (int y = 0; y < fb->height; y++) {
    for (int x = 0; x < fb->width; x++) {
      int index = y*2*fb->width + 2*x;
      uint8_t leftPixVal = fb->buf[index];
      uint8_t rightPixVal = fb->buf[index+1];
      uint16_t sixteenBit = (leftPixVal << 8) | rightPixVal;

      uint8_t red = sixteenBit >> 11;
      uint8_t green = (sixteenBit >> 5) & 0x3F;
      uint8_t blue = sixteenBit & 0x1F;
      cnt++;
      if (x == fb->width-1 && y == fb->height-1)
        Serial.printf("RGB: %d %d %d, %d\n", red, green, blue, sixteenBit);
        // Serial.printf("%02x%02x = %04x, CNT:%d\n", leftPixVal, rightPixVal, sixteenBit, cnt);
    }
  }

