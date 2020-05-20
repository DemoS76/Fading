#pragma once
#include <Arduino.h>

class Fading
{
    public:
        Fading(byte pwmPin, byte minVal = 0, byte maxVal = 255, unsigned int fadeTime = 2000);
        void setMinVal(byte minVal);
        void setMaxVal(byte maxVal);
        void setFadeTime(unsigned int fadeTime);
        void transition(bool transition);
        byte getMinVal();
        byte getMaxVal();
        byte getBrightness();
        unsigned int getFadeTime();
    private:
        byte _pwmPin;
        byte _minVal;
        byte _maxVal;
        byte _brightness;
        unsigned int _fadeTime;
        unsigned int _timerPeriod;
        unsigned long _fadeTimer;
        bool _state;

        void calculateTimerPeriod();
        bool Fading::isInProgress();
};