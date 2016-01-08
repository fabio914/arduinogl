/*
    PDC8544.h - Simple PDC8544 display controller.
 */

#ifndef PDC8544_h
#define PDC8544_h

#include "Arduino.h"

class PDC8544 {
    
public:
    PDC8544(int scePin, int resetPin, int dcPin, int sdinPin, int sclkPin, int ledPin);
    void begin();
    void clear();
    void setBrightness(int brightness); // 0..255
    
    void gotoXY(int x, int y);
    
    void putch(char ch);
    void puts(char * str);
    void printBitmap(char * bitmap); // char[504]
    
    int width();
    int height();
    
private:
    int _scePin;
    int _resetPin;
    int _dcPin;
    int _sdinPin;
    int _sclkPin;
    int _ledPin;
    
    void write(byte dc, byte data);
};

#endif
