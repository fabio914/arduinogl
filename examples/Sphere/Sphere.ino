/*
 * Sphere.ino
 * Created by Fabio de Albuquerque Dela Antonio
 * fabio914 at gmail.com
 * 
 * An OpenGL example that draws a rotated and scaled sphere.
 * 
 * This example requires MAX_VERTICES of at least 24!
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

void drawSphere(float radius, float p) {

  float theta1 = 0.f, theta2 = 0.f, theta3 = 0.f;
  float ex, ey, ez;
        
  for(int i = 0; i < p/2; i++) {
            
    theta1 = i * (M_PI * 2.f)/p - M_PI_2;
    theta2 = (i + 1) * (M_PI * 2.f)/p - M_PI_2;
          
    glBegin(GL_TRIANGLE_STRIP);
    for(int j = 0; j <= p; j++) {
                
      theta3 = j * (M_PI * 2.f)/p;
      ex = cosf(theta2) * cosf(theta3);
      ey = sinf(theta2);
      ez = cosf(theta2) * sinf(theta3);
                
      glVertex3f(radius * ex, radius * ey, radius * ez);
      
      ex = cosf(theta1) * cosf(theta3);
      ey = sinf(theta1);
      ez = cosf(theta1) * sinf(theta3);
                
      glVertex3f(radius * ex, radius * ey, radius * ez);
    }
    glEnd();
  }
}

void loop() {

  /* Read the scale factor from a potentiometer attached to pin A0 */
  float scale = analogRead(0)/1024.f * 4.f;
  static int angle = 0.f;

  glClear(GL_COLOR_BUFFER_BIT); 
  
  glLoadIdentity();
  gluLookAt(10, 8, -10, 0, 0, 0, 0, 1, 0);
  
  glScalef(scale + 1.f, scale + 1.f, scale + 1.f);
  glRotatef(angle, 0.f, 1.f, 0.f);
  
  drawSphere(1.0, 10);
  
  /* Ask the PDC8544 display to print our frame buffer */
  display.printBitmap(c.bitmap());

  angle+=5;
  angle %= 360;
  
  delay(1);
}

