# ESP32Beep
Beep Routines for controlling a Beep via ESP32
important: uses msecTimer from rebe0909/msecTimer
Beep Routines for controlling a Beep via ESP32


Usage:

const int BeepPin = 23;
const int freq = 2800; 
const int beepChannel = 0; 
const int resolution = 8;

Beep myBeep(beepChannel, freq, resolution, BeepPin);

