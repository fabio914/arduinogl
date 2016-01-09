/*
 * Cube.ino
 * Created by Fabio de Albuquerque Dela Antonio
 * fabio914 at gmail.com
 * 
 * An OpenGL example that draws a rotated and scaled cube.
 */

#include <ArduinoGL.h>
#include <Canvas.h>
#include <PCD8544.h>

/* 
   PDC8544 display 
   
   SCE -> digital 7
   RESET -> digital 6
   DC -> digital 5
   SDIN -> digital 11
   SCLK -> digital 13
   LED -> digital 9
 */
PDC8544 display(7, 6, 5, 11, 13, 9);

/* Canvas: a frame buffer where everything is drawn */
Canvas c;

void setup() {
  display.begin();

  display.clear();
  display.puts("OpenGL Test!");
  delay(1000);

  /* Pass the canvas to the OpenGL environment */
  glUseCanvas(&c);
  
  glClear(GL_COLOR_BUFFER_BIT);
  glPointSize(4);
    
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

//  glOrtho(-5, 5, -5, 5, 0.1, 999.f);
  gluPerspective(30.0, c.width()/c.height(), 0.1f, 9999.f);
    
  glMatrixMode(GL_MODELVIEW);
}

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

void loop() {

  /* Read the rotation angle from a potentiometer attached to pin A0 */
  float angle = analogRead(0)/1024.f * 360.f;
  const float scale = 2.5;

  glClear(GL_COLOR_BUFFER_BIT); 
  
  glLoadIdentity();
  gluLookAt(10, 8, -10, 0, 0, 0, 0, 1, 0);
    
  glRotatef(angle, 0.f, 1.f, 0.f);
  glScalef(scale, scale, scale);
  
  drawCube();
  
  /* Ask the PDC8544 display to print our frame buffer */
  display.printBitmap(c.bitmap());
  
  delay(1);
}
