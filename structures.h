/* 
 * File:   structures.h
 * Author: saimon
 *
 * Created on 26 September 2012, 19:52
 */

#ifndef STRUCTURES_H
#define	STRUCTURES_H

struct Eye {
    GLdouble x;
    GLdouble y;
    GLdouble z;
};

struct Center {
    GLdouble x;
    GLdouble y;
    GLdouble z;
};

struct Up {
    GLdouble x;
    GLdouble y;
    GLdouble z;
};

struct Rotate {
    GLint x;
    GLint y;
    GLint z;
};

struct Translate {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct Scale {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

// gluLookAt
Eye eye;
Center center;
Up up;

// servono per le trasformazioni
Rotate rot;
Translate tra;
Scale sca;

// indica il tasto che è stato premuto
unsigned char specialKey;

// dichiarazione di costanti
static const GLint rotOffset = 3;
static const GLint traOffset = 1;
static const GLfloat scaOffset = 0.01;
static const GLint cameraOffset = 1;

// dichiarazione delle funzioni idle di OpenGL
void setup();
void display();
void reshape(int, int);
void keyboard(unsigned char, int, int);
void specialFunc(int, int, int);

void reset();
void transform();
void drawTwoSolidCube();
void drawSolidCube();
void drawItalianFlag();
void drawManualCube();
void lookAt(Eye, Center, Up);
void rotate(int);
void translate(int);
void scale(int);
void moveEye(int);
void moveCenter(int);
void moveUp(int);

#endif	/* STRUCTURES_H */

