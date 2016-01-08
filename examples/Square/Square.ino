/*
 * Square.ino
 * Created by Fabio de Albuquerque Dela Antonio
 * fabio914 at gmail.com
 * 
 * An OpenGL example that draws a rotated and scaled square.
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
  gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
    
  glMatrixMode(GL_MODELVIEW);
}

void loop() {

  /* Read the rotation angle from a potentiometer attached to pin A0 */
  float angle = analogRead(0)/1024.f * 360.f;
  
  static float scale = 3.0, scaleInc = 0.4;
  const float maxScale = 8.0, minScale = 2.0;

  glClear(GL_COLOR_BUFFER_BIT); 
  
  glLoadIdentity();
  glRotatef(angle, 0.f, 0.f, 1.f);
  glScalef(scale, scale, 0.f);
  glTranslatef(-0.5f, -0.5f, 0.f);
  
//  glBegin(GL_POINTS);
//    glVertex3f(0.f, 1.f, 0.f);
//    glVertex3f(0.f, 0.f, 0.f);
//    glVertex3f(1.f, 0.f, 0.f);
//    glVertex3f(1.f, 1.f, 0.f);
//  glEnd();

  glBegin(GL_POLYGON);
    glVertex3f(0.f, 1.f, 0.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(1.f, 0.f, 0.f);
    glVertex3f(1.f, 1.f, 0.f);
  glEnd();

  /* Ask the PDC8544 display to print our frame buffer */
  display.printBitmap(c.bitmap());

  scale += scaleInc;

  if(scale > maxScale)
    scaleInc *= -1.f;

  if(scale < minScale)
    scaleInc *= -1.f;
  
  delay(1);
}

