// Beeper pin numbe.
#define BEEP_PIN A5

// Connects the lib.
#include "Fading.h"

// Creates Fading object and configs it.
// Params: minimal value, maximum value, transition time (ms) from minimum to maximum value.
Fading fading(1000, 3000, 2000);

// Timer for control of fading process.
unsigned long timer;

// Current state of the fading.
bool flag;

void setup() {
  Serial.begin(9600);
  pinMode(BEEP_PIN, OUTPUT);

  // Inits beeper value
  tone(BEEP_PIN, fading.getCurrentValue());

  // Sets a callback for fading process
  fading.setTransitionCallback(transitionHandler);
}

void transitionHandler(unsigned int curVal){
  tone(BEEP_PIN, curVal);
  // Serial.println(curVal);
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
}