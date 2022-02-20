#include <Arduino.h>
#include <mSecTimer.h>


class Beep {

    public:
        Beep(uint8_t beepChannel, double freq, uint8_t resolution, uint8_t BeepPin);
        void StartBeep1(unsigned int len);
        void StartBeep2(unsigned int len, unsigned int pause);
        void StartBeep3(unsigned int len, unsigned int pause, unsigned int count);
        void CheckBeeps(void);
    private:
    
};
