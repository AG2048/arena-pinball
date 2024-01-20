#include <FastLED.h>
#include <math.h>
#include <stdlib.h>

const int len = 20, numLed = 6, displayTiles = 5;
double pos[2]; // update
struct CRGB leds[numLed][len];
struct queue* display;

struct node {
  double valx;
  double valy;
  struct node* next;
};

struct queue {
  struct node *head, *tail;
};

void push(struct queue* q, double valx, double valy) {
  struct node* ptr = (struct node*)malloc(sizeof(struct node));
  ptr->valx = valx;
  ptr->valy = valy;
  ptr->next = nullptr;

  if (q->tail == nullptr) {
    q->head = q->tail = ptr;
  } else {
    q->tail->next = ptr;
    q->tail = ptr;
  }
}

void pop(struct queue* q) {
  if (q->head == nullptr) return;

  struct node* ptr = q->head;
  q->head = q->head->next;

  if (q->head == nullptr) q->tail = nullptr;

  free(ptr);
}

void print(struct queue* q) {
  struct node* ptr = display->head;
  
  while (ptr != nullptr) {
    Serial.print(ptr->valx);
    Serial.print(" ");
    Serial.println(ptr->valy);
    ptr = ptr->next;
  }
  Serial.println("---------");
}

void setup() {
  LEDS.addLeds<WS2812B, 13, GRB>(leds[0], len); // update below
  LEDS.addLeds<WS2812B, 12, GRB>(leds[1], len);
  LEDS.addLeds<WS2812B, 11, GRB>(leds[2], len);
  LEDS.addLeds<WS2812B, 10, GRB>(leds[3], len);
  LEDS.addLeds<WS2812B, 9, GRB>(leds[4], len);
  LEDS.addLeds<WS2812B, 8, GRB>(leds[5], len);
  Serial.begin(9600);

  display = (struct queue*)malloc(sizeof(struct queue));
  display->head = display->tail = nullptr;
  for (int i = 0; i < displayTiles; i++) push(display, 0, 0);
}

void loop() {
  pos[0] = rand()/((double) RAND_MAX); // update
  pos[1] = rand()/((double) RAND_MAX); // update
  
  push(display, pos[0], pos[1]); // update
  pop(display);
  print(display); // update

  for (int i = 0; i < numLed; i++) for (int j = 0; j < len; j++) leds[i][j] = CRGB(0, 0, 0);

  struct node* ptr = display->head;
  while (ptr != nullptr) {
    leds[round(ptr->valx*numLed)][round(ptr->valy*len)] = CRGB(0, 0, 255);
    ptr = ptr->next;
  }

  FastLED.show();
  delay(1000);
}
