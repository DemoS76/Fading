// Button pin number.
#define BTN_PIN 8
// Led pin number (must be PWM).
#define LED_PIN 3

// Connects the lib.
#include "Fading.h"

// Creates Fading object and configs it.
// Params: minimal value, maximum value, transition time from minimum to maximum value.
Fading fading(10, 255, 1000);

void setup() {
  Serial.begin(9600);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  // Inits LED value
  analogWrite(LED_PIN, fading.getCurrentValue());

  // Sets a callback for fading process
  fading.setTransitionCallback(transitionHandler);
}

void transitionHandler(byte curVal){
  analogWrite(LED_PIN, curVal);
  Serial.println(curVal);
}

void loop() {
  // Makes to start the transition from min to max value if the parameter is true.
  fading.transition(!digitalRead(BTN_PIN));
}