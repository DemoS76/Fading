// LED pin number (must be PWM).
#define LED_PIN 3

// Connects the lib.
#include "Fading.h"

// Creates Fading object and configs it.
// Params: minimal value, maximum value, transition time from minimum to maximum value.
Fading fading(10, 255, 1000);

// Timer for control of fading process.
unsigned long timer;

// Current state of the fading.
bool flag;

// Current PWM value.
byte curBrightness;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  // Inits LED value
  analogWrite(LED_PIN, fading.getCurrentValue());
}

void loop() {
  // Switching state once per 3 sec.
  if (millis() - timer >= 3000)
  {
    flag = !flag;
    timer = millis();
  }

  // Makes to start the transition from min to max value if the parameter is true.
  fading.transition(flag);

  // Print current PWM value
  if (curBrightness != fading.getCurrentValue()){
    curBrightness = fading.getCurrentValue();
    analogWrite(LED_PIN, curBrightness);
    Serial.println(curBrightness);
  }
}