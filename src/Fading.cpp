#include <Arduino.h>
#include "Fading.h"

Fading::Fading(byte pwmPin, byte minVal = 0, byte maxVal = 255, unsigned int fadeTime = 2000)
{
    _pwmPin = pwmPin;
    _minVal = minVal;
    _maxVal = maxVal;
    _fadeTime = fadeTime;
    _brightness = minVal;

    calculateTimerPeriod();

    pinMode(pwmPin, OUTPUT);
    analogWrite(pwmPin, _brightness);
}

void Fading::setMinVal(byte minVal) 
{
    _minVal = minVal;
    calculateTimerPeriod();
}
byte Fading::getMinVal() { return _minVal; }

void Fading::setMaxVal(byte maxVal)
{
    _maxVal = maxVal;
    calculateTimerPeriod();
}
byte Fading::getMaxVal() { return _maxVal; }

void Fading::setFadeTime(unsigned int fadeTime)
{
    _fadeTime = fadeTime;
    calculateTimerPeriod();
}

unsigned int Fading::getFadeTime() { return _fadeTime; }

void Fading::transition(bool transition) {
    if (isInProgress() || _state != transition){
        _state = transition;
        if (millis() - _fadeTimer >= _timerPeriod) {
            analogWrite(_pwmPin, _state ? _brightness++ : --_brightness);
            _fadeTimer = millis();
        }
    }
};

void Fading::calculateTimerPeriod() {
    byte delta = _maxVal - _minVal;
    _timerPeriod = _fadeTime / delta;
};

byte Fading::getBrightness() { return _brightness; };

bool Fading::isInProgress() { return !(_brightness == _minVal || _brightness == _maxVal); }