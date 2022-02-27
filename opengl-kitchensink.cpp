/* 
 * File:   kitchensink.cpp
 * Author: Simone Spaccarotella
 *
 * Created on 27 September 2012, 15:52
 */
#include <GL/glut.h>
#include <iostream>
#include "structures.h"
#include "CxImage/ximage.h"
using std::cout;
using std::endl;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Kitchensink");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialFunc);
    glutKeyboardFunc(keyboard);
    setup();
    glutMainLoop();
    return 0;
}

/**
 * Resetta i parametri di rotazione, traslazione e scaling del modello.
 */
void reset() {
    eye.x = eye.y = center.x = center.y = up.x = up.z = 0;
    rot.x = rot.y = rot.z = tra.x = tra.y = tra.z = 0;
    eye.z = 15;
    center.z = -1;
    up.y = sca.x = sca.y = sca.z = 1;
    specialKey = 'r';
}

/**
 * Effettua il setup iniziale degli stati OpenGL
 */
void setup() {
    reset();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    
    CxImage image;
    image.Load("face.jpg", CXIMAGE_FORMAT_JPG);
    if (image.IsValid()) {
        cout << "image is valid" << endl;
    }
}

GLvoid normal(GLfloat v1[], GLfloat v2[], GLfloat v3[], GLfloat normal[]) {
    GLfloat p[3];
    GLfloat q[3];
    for (int i = 0; i < 3; i++) {
        p[i] = v2[i] - v1[i];
        q[i] = v3[i] - v1[i];
    }
    normal[0] = p[1] * q[2] - p[2] * q[1];
    normal[1] = p[2] * q[0] - p[0] * q[2];
    normal[2] = p[0] * q[1] - p[1] * q[0];
}

/**
 * Viene richiamata ogniqualvolta la finestra è ridimensionata.
 * @param w la larghezza della wieport.
 * @param h l'altezza della viewport.
 */
void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLsizei) w / h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

/**
 * Effettua il rendering della scena, utilizzando il double buffering.
 */
void display() {
    // resetta il colore di background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    lookAt(eye, center, up);

    // SETTING LIGHT
//    GLfloat position[] = {eye.x, eye.y, eye.z, 0};
//    glLightfv(GL_LIGHT0, GL_POSITION, position);
//    GLfloat direction[] = {center.x, center.y, center.z};
//    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);

    GLfloat ambient[] = {0.2, 0.2, 0.1, 1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
//    GLfloat diffuse[] = {0.2, 0.2, 0.2, 1};
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
//    GLfloat specular[] = {0.2, 0.2, 0.2, 1};
//    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    // Set Material properties to follow glColor values
    //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    transform();
    drawManualCube();
    glutSwapBuffers();
}

/**
 * Il cubo viene disegnato manualmente, definendo esplicitamente le coordinate.
 * Il cubo è centrato rispetto all'origine degli assi cartesiani.
 */
void drawManualCube() {
    glBegin(GL_QUADS);
    // top
    glVertex3f(3, 3, 3);
    glVertex3f(3, 3, -3);
    glVertex3f(-3, 3, -3);
    glVertex3f(-3, 3, 3);
    // bottom
    glVertex3f(3, -3, 3);
    glVertex3f(-3, -3, 3);
    glVertex3f(-3, -3, -3);
    glVertex3f(3, -3, -3);
    // front
    glVertex3f(3, -3, 3);
    glVertex3f(3, 3, 3);
    glVertex3f(-3, 3, 3);
    glVertex3f(-3, -3, 3);
    // back
    glVertex3f(3, -3, -3);
    glVertex3f(-3, -3, -3);
    glVertex3f(-3, 3, -3);
    glVertex3f(3, 3, -3);
    // left
    glVertex3f(-3, -3, 3);
    glVertex3f(-3, 3, 3);
    glVertex3f(-3, 3, -3);
    glVertex3f(-3, -3, -3);
    // right
    glVertex3f(3, -3, 3);
    glVertex3f(3, -3, -3);
    glVertex3f(3, 3, -3);
    glVertex3f(3, 3, 3);
    glEnd();
}

/**
 * Trasforma il modello 3D.
 */
void transform() {
    glTranslatef(tra.x, tra.y, tra.z);
    glScalef(sca.x, sca.y, sca.z);
    glRotatef(rot.x, 1, 0, 0);
    glRotatef(rot.y, 0, 1, 0);
    glRotatef(rot.z, 0, 0, 1);
}

/**
 * Disegna due cubi di dimensioni diverse.
 */
void drawTwoSolidCube() {
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(6);

    glColor3f(0.0, 1.0, 0.0);
    glTranslatef(6, 0, 0);
    glRotatef(rot.y, 0, 1, 0);
    glutSolidCube(3);
}

/**
 * Disegna un unico cubo.
 */
void drawSolidCube() {
    glColor3f(1.0, 1.0, 0.0);
    glutSolidCube(4);
}

/**
 * Disegna la bandiera italiana, utilizzando i poligoni "stripped",
 * cambiando colore ad ogni coppia di punti.
 */
void drawItalianFlag() {
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 10, 0);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(10, 0, 0);
    glVertex3f(10, 10, 0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(20, 0, 0);
    glVertex3f(20, 10, 0);
    glEnd();
}

/**
 * Funzione di utilità, per facilitare il posizionamento del punto di vista.
 * 
 * @param eye il punto di applicazione della camera.
 * @param center il punto verso il quale la camera osserva.
 * @param up il punto che definisce la normale al piano passante per il segmento definito
 *           da 
 */
void lookAt(Eye eye, Center center, Up up) {
    gluLookAt(eye.x, eye.y, eye.z, center.x, center.y, center.z, up.x, up.y, up.z);
}

/**
 * Ruota il modello. 
 * @param key il tasto speciale premuto.
 */
void rotate(int key) {
    switch (key) {
        case GLUT_KEY_UP:
            rot.x -= rotOffset;
            if (rot.x < 0) {
                rot.x = 360 + rot.x;
            }
            break;
        case GLUT_KEY_DOWN:
            rot.x = (rot.x + rotOffset) % 360;
            break;
        case GLUT_KEY_LEFT:
            rot.y -= rotOffset;
            if (rot.y < 0) {
                rot.y = 360 + rot.y;
            }
            break;
        case GLUT_KEY_RIGHT:
            rot.y = (rot.y + rotOffset) % 360;
            break;
        case GLUT_KEY_PAGE_UP:
            rot.z -= rotOffset;
            if (rot.z < 0) {
                rot.z = 360 + rot.z;
            }
            break;
        case GLUT_KEY_PAGE_DOWN:
            rot.z = (rot.z + rotOffset) % 360;
            break;
    }
}

/**
 * Trasla il modello.
 * @param key il tasto speciale premuto.
 */
void translate(int key) {
    switch (key) {
        case GLUT_KEY_UP:
            tra.y += traOffset;
            break;
        case GLUT_KEY_DOWN:
            tra.y -= traOffset;
            break;
        case GLUT_KEY_LEFT:
            tra.x -= traOffset;
            break;
        case GLUT_KEY_RIGHT:
            tra.x += traOffset;
            break;
        case GLUT_KEY_PAGE_UP:
            tra.z -= traOffset;
            break;
        case GLUT_KEY_PAGE_DOWN:
            tra.z += traOffset;
            break;
    }
}

/**
 * Scala il modello.
 * @param key il tasto speciale premuto.
 */
void scale(int key) {
    switch (key) {
        case GLUT_KEY_UP:
            sca.y += scaOffset;
            break;
        case GLUT_KEY_DOWN:
            sca.y -= scaOffset;
            break;
        case GLUT_KEY_LEFT:
            sca.x -= scaOffset;
            break;
        case GLUT_KEY_RIGHT:
            sca.x += scaOffset;
            break;
        case GLUT_KEY_PAGE_UP:
            sca.z += scaOffset;
            break;
        case GLUT_KEY_PAGE_DOWN:
            sca.z -= scaOffset;
            break;
    }
}

/**
 * Muove il punto di applicazione della telecamera.
 * @param key il tasto speciale premuto.
 */
void moveEye(int key) {
    switch (key) {
        case GLUT_KEY_UP:
            eye.y += cameraOffset;
            break;
        case GLUT_KEY_DOWN:
            eye.y -= cameraOffset;
            break;
        case GLUT_KEY_LEFT:
            eye.x -= cameraOffset;
            break;
        case GLUT_KEY_RIGHT:
            eye.x += cameraOffset;
            break;
        case GLUT_KEY_PAGE_UP:
            eye.z += cameraOffset;
            break;
        case GLUT_KEY_PAGE_DOWN:
            eye.z -= cameraOffset;
            break;
    }
}

/**
 * Muove il punto verso la quale la telecamera è puntata.
 * @param key il tasto speciale premuto.
 */
void moveCenter(int key) {
    switch (key) {
        case GLUT_KEY_UP:
            center.y += cameraOffset;
            break;
        case GLUT_KEY_DOWN:
            center.y -= cameraOffset;
            break;
        case GLUT_KEY_LEFT:
            center.x -= cameraOffset;
            break;
        case GLUT_KEY_RIGHT:
            center.x += cameraOffset;
            break;
        case GLUT_KEY_PAGE_UP:
            center.z += cameraOffset;
            break;
        case GLUT_KEY_PAGE_DOWN:
            center.z -= cameraOffset;
            break;
    }
}

/**
 * Muove il punto della normale al piano della telecamera.
 * @param key il tasto speciale premuto.
 */
void moveUp(int key) {
    switch (key) {
        case GLUT_KEY_UP:
            up.y += cameraOffset;
            break;
        case GLUT_KEY_DOWN:
            up.y -= cameraOffset;
            break;
        case GLUT_KEY_LEFT:
            up.x -= cameraOffset;
            break;
        case GLUT_KEY_RIGHT:
            up.x += cameraOffset;
            break;
        case GLUT_KEY_PAGE_UP:
            up.z += cameraOffset;
            break;
        case GLUT_KEY_PAGE_DOWN:
            up.z -= cameraOffset;
            break;
    }
}

/**
 * Funzione di callback che viene invocata come ascoltatore ogniqualvolta
 * viene premuto un tasto alfanumerico della tastiera.
 * @param key il tasto premuto
 * @param mouseX la coordinata X del puntatore del mouse.
 * @param mouseY la coordinata Y del puntatore del mouse.
 */
void keyboard(unsigned char key, int mouseX, int mouseY) {
    specialKey = key;
    if (specialKey == 'l' || specialKey == 'L') {
        reset();
        glutPostRedisplay();
    }
}

/**
 * Funzione di callback che viene invocata come ascoltatore ogniqualvolta
 * viene premuto un tasto speciale.
 * @param key
 * @param mouseX
 * @param mouseY
 */
void specialFunc(int key, int mouseX, int mouseY) {
    if (specialKey == 't' || specialKey == 'T') {
        cout << "TRASLAZIONE(" << specialKey << "): ";
        translate(key);
        cout << tra.x << ", " << tra.y << ", " << tra.z << endl;
    } else if (specialKey == 's' || specialKey == 'S') {
        cout << "SCALING(" << specialKey << "): ";
        scale(key);
        cout << sca.x << ", " << sca.y << ", " << sca.z << endl;
    } else if (specialKey == 'e' || specialKey == 'E') {
        cout << "MOVING EYE(" << specialKey << "): ";
        moveEye(key);
        cout << eye.x << ", " << eye.y << ", " << eye.z << endl;
    } else if (specialKey == 'c' || specialKey == 'C') {
        cout << "MOVING CENTER(" << specialKey << "): ";
        moveCenter(key);
        cout << center.x << ", " << center.y << ", " << center.z << endl;
    } else if (specialKey == 'u' || specialKey == 'U') {
        cout << "MOVING UP(" << specialKey << "): ";
        moveUp(key);
        cout << up.x << ", " << up.y << ", " << up.z << endl;
    } else {
        specialKey = 'r';
        cout << "ROTAZIONE(" << specialKey << "): ";
        rotate(key);
        cout << rot.x << ", " << rot.y << ", " << rot.z << endl;
    }
    glutPostRedisplay();
}