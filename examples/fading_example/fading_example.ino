// led pin number (must be PWM)
#define LED_PIN 3

// connects the lib
#include "Fading.h"

// Creates Fading object and configs it.
// Params: LED(PWM) pin number, minimal value for PWM, maximum value for PWM, transition time from minimum to maximum value.
Fading fading(LED_PIN, 10, 255, 1000);

// timer for control of fading process
unsigned long timer;

// current state of the fading
bool flag;

// current PWM value
byte curBrightness;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // switching the state once per 3 sec
  if (millis() - timer >= 3000)
  {
    flag = !flag;
    timer = millis();
  }

  // makes start the transition from min to max value if parameter is true
  fading.transition(flag);
  
  // print current PWM value
  if (curBrightness != fading.getBrightness()){
    curBrightness = fading.getBrightness();
    Serial.println(fading.getBrightness());
  }
}