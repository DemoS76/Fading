// button pin number
#define BTN_PIN 8
// led pin number (must be PWM)
#define LED_PIN 3

// connects the lib
#include "Fading.h"

// Creates Fading object and configs it.
// Params: LED(PWM) pin number, minimal value for PWM, maximum value for PWM, transition time from minimum to maximum value.
Fading fading(LED_PIN, 10, 255, 1000);

// current PWM value
byte curBrightness;

void setup() {
  Serial.begin(9600);
  pinMode(BTN_PIN, INPUT_PULLUP);
}

void loop() {
  // makes start the transition from min to max value if parameter is true
  fading.transition(!digitalRead(BTN_PIN));

  // print current PWM value
  if (curBrightness != fading.getBrightness()){
    curBrightness = fading.getBrightness();
    Serial.println(fading.getBrightness());
  }
}