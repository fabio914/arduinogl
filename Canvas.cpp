/*
	Canvas.h - Simple canvas.
 */

#include "Arduino.h"
#include "Canvas.h"

#define CANVAS_WIDTH 84
#define CANVAS_HEIGHT 48

Canvas::Canvas(void) {
}

void Canvas::clear(void) {
    
    for(int i = 0; i < (CANVAS_WIDTH * CANVAS_HEIGHT)/8; i++)
        _displayMap[i] = 0x00;
}

int Canvas::width(void) {
    
    return CANVAS_WIDTH;
}

int Canvas::height(void) {
    
    return CANVAS_HEIGHT;
}

char * Canvas::bitmap(void) {
    
    return (char *)_displayMap;
}

void Canvas::setPixel(int x, int y, bool on) {
    
    if((x >= 0) && (x < CANVAS_WIDTH) && (y >= 0) && (y < CANVAS_HEIGHT)) {
        
        byte shift = y % 8;
        
        if(on)
            _displayMap[x + (y/8)*CANVAS_WIDTH] |= 1<<shift;
        
        else
            _displayMap[x + (y/8)*CANVAS_WIDTH] &= ~(1<<shift);
    }
}

void Canvas::drawLine(int startX, int startY, int endX, int endY) {
    
    int diffX = (endX - startX);
    int diffY = (endY - startY);
    
    if(abs(diffX) > abs(diffY)) {
        
        float dy = diffY/(float)diffX;
        
        if(endX > startX) {
            
            for(int x = startX; x <= endX; x++) {
                
                this->setPixel(x, floor(startY + dy*(x - startX)), HIGH);
            }
        }
        
        else {
            
            for(int x = startX; x >= endX; x--) {
                
                this->setPixel(x, floor(startY + dy*(x - startX)), HIGH);
            }
        }
    }
    
    else {
        
        float dx = diffX/(float)diffY;
        
        if(endY > startY) {
            
            for(int y = startY; y <= endY; y++) {
                
                this->setPixel(floor(startX + dx*(y - startY)), y, HIGH);
            }
        }
        
        else {
            
            for(int y = startY; y >= endY; y--) {
                
                this->setPixel(floor(startX + dx*(y - startY)), y, HIGH);
            }
        }
    }
}

void Canvas::drawCircle(int centreX, int centreY, int radius) {
    
    radius = abs(radius);
    
    for(float angle = 0; angle < 2*M_PI; angle+=(M_PI/(4*radius))) {
        
        this->setPixel(centreX + cos(angle)*radius, centreY + sin(angle)*radius, HIGH);
    }
}

void Canvas::drawSquare(int startX, int startY, int endX, int endY) {
    
    this->drawLine(startX, startY, startX, endY);
    this->drawLine(startX, endY, endX, endY);
    this->drawLine(endX, endY, endX, startY);
    this->drawLine(endX, startY, startX, startY);
}

void Canvas::drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    
    this->drawLine(x1, y1, x2, y2);
    this->drawLine(x2, y2, x3, y3);
    this->drawLine(x3, y3, x1, y1);
}
