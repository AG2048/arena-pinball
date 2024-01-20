#include <FastLED.h>

int score[2] = {0, 0}, t = 0, len = 6, fp = 3, diff = 2;
bool click[2] = {false, false};
struct CRGB leds[8];

void setup() {
  LEDS.addLeds<WS2812B, 11, GRB>(leds, len);
  pinMode(10, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if ((score[0] == fp && score[1] <= fp-diff) || (score[0]+score[1] >= fp*2 && score[0]-score[1] >= diff)) {
    if (t%50 < 25) {
      for (int i = 0; i < len; i++) leds[i] = CRGB(255, 0, 0);
    } else {
      for (int i = 0; i < len; i++) leds[i] = CRGB(0, 0, 0);
    }
  } else if ((score[1] == fp && score[0] <= fp-diff) || (score[0]+score[1] >= fp*2 && score[1]-score[0] >= diff)) {
    if (t%50 < 25) {
      for (int i = 0; i < len; i++) leds[i] = CRGB(0, 0, 255);
    } else {
      for (int i = 0; i < len; i++) leds[i] = CRGB(0, 0, 0);
    }
  } else {
    if (digitalRead(10) == HIGH) click[0] = true;
    if (digitalRead(10) == LOW && click[0]) {
      score[0]++;
      click[0] = false;
    }
    if (digitalRead(9) == HIGH) click[1] = true;
    if (digitalRead(9) == LOW && click[1]) {
      score[1]++;
      click[1] = false;
    }
    if (score[0]+score[1] <= fp*2) {
      for (int i = 0; i < score[0]; i++) leds[i] = CRGB(255, 0, 0);
      for (int i = (fp*2)-1; i > (fp*2)-1-score[1]; i--) leds[i] = CRGB(0, 0, 255);
    } else {
      for (int i = 0; i < score[0]-score[1]+fp; i++) leds[i] = CRGB(255, 0, 0);
      for (int i = (fp*2)-1; i >= score[0]-score[1]+fp; i--) leds[i] = CRGB(0, 0, 255);
    }
  }

  t++;
  FastLED.show();
  delay(20);
}