/*
    ArduinoGL.h - OpenGL subset for Arduino.
    Created by Fabio de Albuquerque Dela Antonio
    fabio914 at gmail.com
 */

#ifndef ArduinoGL_h
#define ArduinoGL_h

#include "Arduino.h"
#include "Canvas.h"

typedef enum {
    GL_NONE = 0,
    GL_POINTS,
    GL_POLYGON,
    GL_TRIANGLE_STRIP
} GLDrawMode;

typedef enum {
    GL_PROJECTION = 0,
    GL_MODELVIEW
} GLMatrixMode;

/* Masks */
#define GL_COLOR_BUFFER_BIT 0x1

typedef struct {
    float x, y, z, w;
} GLVertex;

/* Matrices */
void glMatrixMode(GLMatrixMode mode);
void glMultMatrixf(float * m);
void glLoadMatrixf(float * m);
void glLoadIdentity(void);

void glPushMatrix(void);
void glPopMatrix(void);

void glOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
void gluOrtho2D(float left, float right, float bottom, float top);
void glFrustum(float left, float right, float bottom, float top, float zNear, float zFar);
void gluPerspective(float fovy, float aspect, float zNear, float zFar);

void glRotatef(float angle, float x, float y, float z);
void glTranslatef(float x, float y, float z);
void glScalef(float x, float y, float z);
void gluLookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

/* Vertices */
void glVertex4fv(float * v);
void glVertex4f(float x, float y, float z, float w);
void glVertex3fv(float * v);
void glVertex3f(float x, float y, float z);

/* OpenGL */
void glUseCanvas(Canvas * c); /* <-- Arduino only */

void glPointSize(unsigned size);
void glClear(int mask);
void glBegin(GLDrawMode mode);
void glEnd(void);

#endif
