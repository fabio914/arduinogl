
<img src="/arduinogl.png?raw=true" width="150">

# ArduinoGL : OpenGL for Arduino

This is a very small subset of OpenGL 1.0 written for Arduino UNO (although it should run on other more powerful Arduinos as well). This library also includes code to draw the frame buffer on a PCD8544 LCD display (Nokia 5110 display).

This is just a proof of concept, it is not meant to run fast or suit any application.

## Features

It is able to draw 2D and 3D wireframes! It has **no** backface culling, **no** frustum culling, **no** colours, **no** depth/z buffer, **no** textures, **no** lighting, **no** shading, etc...

`glBegin(mode)` only supports `GL_POINTS`, `GL_POLYGON` and `GL_TRIANGLE_STRIP`.
Since Arduino UNO has only 2 Kb of RAM, there is a limit to the number of matrices on the stack (`#define MAX_MATRICES 8`) and vertices being processed (`#define MAX_VERTICES 24`) .

## Hookup

Follow this [sparkfun guide](https://learn.sparkfun.com/tutorials/graphic-lcd-hookup-guide) to hookup your PCD8544 display. Before running any example, check if your wiring is correct!

## Installation

Create an `ArduinoGL` directory inside your `~/Arduino/libraries/` directory, then copy all the contents of this repository to that new directory. After that you will be able to compile and run all the examples on the Arduino IDE.

## Example

This example reads an angle from analog pin `A0`, uses a camera with a perspective projection (`gluPerspective(...)`), and draws a rotated and scaled cube.

### Code
```c
#include <ArduinoGL.h>
#include <Canvas.h>
#include <PCD8544.h>

PDC8544 display(7, 6, 5, 11, 13, 9);
Canvas c;

void drawCube() {                

  glBegin(GL_POLYGON);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);
  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
  glEnd();
}

void setup() {

  display.begin();
  display.clear();
  
  glUseCanvas(&c);
  glClear(GL_COLOR_BUFFER_BIT);
    
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(30.0, c.width()/c.height(), 0.1f, 9999.f);
    
  glMatrixMode(GL_MODELVIEW);
}

void loop() {
  
  float angle = analogRead(0)/1024.f * 360.f;
  glClear(GL_COLOR_BUFFER_BIT); 
  
  glLoadIdentity();
  gluLookAt(10, 8, -10, 0, 0, 0, 0, 1, 0);
    
  glRotatef(angle, 0.f, 1.f, 0.f);
  glScalef(2.5f, 2.5f, 2.5f);
  
  drawCube();
  
  display.printBitmap(c.bitmap());
  delay(1);
}
```

### Result

<img src="/cube.jpg?raw=true" width="200">

## 3D Models

You can use the `STL_converter` tool to convert any **small** STL model into a format that can be used with `ArduinoGL`. 

<img src="/stanford_bunny.jpg?raw=true" width="200">

*Stanford Bunny*

## Developer
[Fabio de Albuquerque Dela Antonio](http://fabio914.blogspot.com)


