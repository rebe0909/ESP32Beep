#include <Arduino.h>
#include "beep.h"


mSecTimer msBeepTimer;

uint8_t _beepChannel = 0;
bool BeepIsRunning = false;
char beep_count = 0;
unsigned int beep_len = 0; 
unsigned int beep_pause = 0; 
const int duty = 125;

Beep::Beep(uint8_t beepChannel, double freq, uint8_t resolution, uint8_t BeepPin)
{
    _beepChannel = beepChannel;

    ledcSetup(_beepChannel, freq, resolution);
    ledcAttachPin(BeepPin, _beepChannel);
}

void Beep::StartBeep1(unsigned int len)
{
    StartBeep3(len, 0, 1);
}
void Beep::StartBeep2(unsigned int len, unsigned int pause)
{
    StartBeep3(len, pause, 2);
}
void Beep::StartBeep3(unsigned int len, unsigned int pause, unsigned int count)
{
    beep_len = len;
    beep_pause = pause;
    beep_count = count+(count-1);
    msBeepTimer.startTimer(1);
    ledcWrite(_beepChannel, duty);
    BeepIsRunning = true;
}

void Beep::CheckBeeps(void)
{
    if(msBeepTimer.hasElapsedAndStarted() && BeepIsRunning)
        {
            ledcWrite(_beepChannel, 0);
            if(beep_count % 2)
            {
                msBeepTimer.startTimer(beep_len);
                beep_count--;
                ledcWrite(_beepChannel, duty); 
            }
            else
            {
                msBeepTimer.startTimer(beep_pause);
                if(beep_count) beep_count--;
                else BeepIsRunning = false;
            }
        }

}
