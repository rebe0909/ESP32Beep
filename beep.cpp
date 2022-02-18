#include <Arduino.h>
#include "beep.h"


mSecTimer msBeep1Timer;
mSecTimer msBeep2Timer;
mSecTimer msBeep3Timer;

uint8_t _beepChannel = 0;
bool Beep1 = false;
bool Beep2 = false;
bool Beep3 = false;
char beep2_count = 0;
unsigned int beep2_len = 0; 
unsigned int beep2_pause = 0; 
char beep3_count = 0;
unsigned int beep3_len = 0; 
unsigned int beep3_pause = 0; 
const int duty = 125;

Beep::Beep(uint8_t beepChannel, double freq, uint8_t resolution, uint8_t BeepPin)
{
    _beepChannel = beepChannel;

    ledcSetup(_beepChannel, freq, resolution);
    ledcAttachPin(BeepPin, _beepChannel);
}

void Beep::StartBeep1(unsigned int len)
{
    msBeep1Timer.startTimer(len);
    ledcWrite(_beepChannel, duty);
    Beep1 = true;
}
void Beep::StartBeep2(unsigned int len, unsigned int pause)
{
    beep2_len = len;
    beep2_pause = pause;
    msBeep2Timer.startTimer(len);
    ledcWrite(_beepChannel, duty);
    Beep2 = true;
    beep2_count = 2;
}
void Beep::StartBeep3(unsigned int len, unsigned int pause, unsigned int count)
{
    beep3_len = len;
    beep3_pause = pause;
    beep3_count = count+(count-1);
    msBeep3Timer.startTimer(1);
    ledcWrite(_beepChannel, duty);
    Beep3 = true;
}

void Beep::CheckAllBeeps(void)
{
    if(msBeep1Timer.hasElapsedAndStarted() && Beep1)
        {
            ledcWrite(_beepChannel, 0);
            Beep1 = false;
        }
    if(msBeep2Timer.hasElapsedAndStarted() && Beep2)
        {
            ledcWrite(_beepChannel, 0);
            switch (beep2_count)
            {
            case 2: //Pause
                msBeep2Timer.startTimer(beep2_pause);
                beep2_count--;
                break;
            case 1:
                msBeep2Timer.startTimer(beep2_len);
                beep2_count--;
                ledcWrite(_beepChannel, duty); 

            break;
            default:
                Beep2 = false;
                break;
            }

        }
    if(msBeep3Timer.hasElapsedAndStarted() && Beep3)
        {
            ledcWrite(_beepChannel, 0);
            if(beep3_count % 2)
            {
                msBeep3Timer.startTimer(beep3_len);
                beep3_count--;
                ledcWrite(_beepChannel, duty); 
            }
            else
            {
                msBeep3Timer.startTimer(beep3_pause);
                if(beep3_count) beep3_count--;
                else Beep3 = false;
            }
        }

}
