#include <Arduino.h>
#include "Fading.h"

// Constructor
Fading::Fading(unsigned int minVal = 0, unsigned int maxVal = 255, unsigned int fadeTime = 2000)
{
    _minVal = minVal;
    _maxVal = maxVal;
    _fadeTime = fadeTime;
    _currentValue = minVal;

    calculateTimerPeriod();
}

void Fading::setMinVal(unsigned int minVal) 
{
    _minVal = minVal;
    calculateTimerPeriod();
}
unsigned int Fading::getMinVal() { return _minVal; }

void Fading::setMaxVal(unsigned int maxVal)
{
    _maxVal = maxVal;
    calculateTimerPeriod();
}
unsigned int Fading::getMaxVal() { return _maxVal; }

void Fading::setFadeTime(unsigned int fadeTime)
{
    _fadeTime = fadeTime;
    calculateTimerPeriod();
}

unsigned int Fading::getFadeTime() { return _fadeTime; }

void Fading::transition(bool transition) {
    if (isInProgress() || _state != transition){
        _state = transition;

        bool isReady = _timerScale == TimerScale::milSec
            ? millis() - _fadeTimer >= _timerPeriod
            : micros() - _fadeTimer >= _timerPeriod;

        if (isReady) {
            _state ? ++_currentValue : --_currentValue;

            if (_transitionCallback) {
                _transitionCallback(_currentValue);
            }

            _timerScale == TimerScale::milSec
            ? _fadeTimer = millis()
            : _fadeTimer = micros();
        }
    }
};

void Fading::calculateTimerPeriod() {
    unsigned int delta = _maxVal - _minVal;

    // timer scaling
    if (delta > _fadeTime) {
        _timerScale = TimerScale::micSec;
        _timerPeriod = _fadeTime * 1000 / delta;
    } else
    {
        _timerScale = TimerScale::milSec;
        _timerPeriod = _fadeTime / delta;
    }
};

unsigned int Fading::getCurrentValue() { return _currentValue; };

// indicates whether the transition is in progress or not
bool Fading::isInProgress() { return !(_currentValue == _minVal || _currentValue == _maxVal); }

void Fading::setTransitionCallback(TransitionCallback transitionCallback){
    _transitionCallback = transitionCallback;
};