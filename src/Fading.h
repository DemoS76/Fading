#pragma once
#include <Arduino.h>

using TransitionCallback = void (*)(byte);

enum TimerScale {
    milSec,
    micSec
};

class Fading
{
    public:
        Fading(unsigned int minVal = 0, unsigned int maxVal = 255, unsigned int fadeTime = 2000);
        void setMinVal(unsigned int minVal);
        void setMaxVal(unsigned int maxVal);
        void setFadeTime(unsigned int fadeTime);
        void transition(bool transition);
        void setTransitionCallback(TransitionCallback transitionCallback);
        unsigned int getMinVal();
        unsigned int getMaxVal();
        unsigned int getCurrentValue();
        unsigned int getFadeTime();
    private:
        unsigned int _minVal;
        unsigned int _maxVal;
        unsigned int _currentValue;
        unsigned int _fadeTime;
        unsigned int _timerPeriod;
        unsigned long _fadeTimer;
        bool _state;
        TransitionCallback _transitionCallback;
        TimerScale _timerScale;

        void calculateTimerPeriod();
        bool isInProgress();
};