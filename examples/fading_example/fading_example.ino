#define LED_PIN 3

#include "Fading.h"
Fading fading(LED_PIN, 10, 255, 1000);

unsigned long timer;
bool flag;
byte curBrightness;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (millis() - timer >= 3000)
  {
    flag = !flag;
    timer = millis();
  }

  fading.transition(flag);
  
  if (curBrightness != fading.getBrightness()){
    curBrightness = fading.getBrightness();
    Serial.println(fading.getBrightness());
  }
}