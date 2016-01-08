/*
	Canvas.h - Simple canvas.
 */

#ifndef Canvas_h
#define Canvas_h

#include "Arduino.h"

class Canvas {
    
public:
    Canvas();
    void clear();
    void setPixel(int x, int y, bool on);
    
    void drawLine(int startX, int startY, int endX, int endY);
    void drawCircle(int centreX, int centreY, int radius);
    void drawSquare(int startX, int startY, int endX, int endY);
    void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
    
    char * bitmap();
    
    int width();
    int height();
    
private:
    byte _displayMap[504] = { 0x00 };
};

#endif

