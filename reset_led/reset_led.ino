#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#define NUM_LEDS 1

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, GPIO_NUM_2, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
}

void loop() {
}
