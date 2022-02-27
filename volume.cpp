/* 
 * File:   main.cpp
 * Author: saimon
 *
 * Created on 24 September 2012, 10:20
 * Viene disegnato un cubo senza facce, che può roteare su
 * X e Y, e traslare su Z.
 */

#include <GL/glut.h>

static int year = 0, day = 0;

static float lx = 1000.0, ly = 1000.0, lz = 1000.0;
static int rotate_y = 0, rotate_x = 0;
static int rotate_angle = 360 / 100;
static int translate_z = 0;
static float translate_lenght;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    translate_lenght = lz / 100;
    glEnable(GL_POLYGON_SMOOTH);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 1.0, .0);

    glPushMatrix();
    glTranslatef(0, 0, translate_z);
    glRotatef(rotate_y, 0, 1, 0);
    glRotatef(rotate_x, 1, 0, 0);
    glutWireCube(lx);
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1, 2 * lx);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 2 * lx, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void SpecialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) rotate_y -= rotate_angle % 360;
    if (key == GLUT_KEY_RIGHT) rotate_y += rotate_angle % 360;
    if (key == GLUT_KEY_UP) rotate_x -= rotate_angle % 360;
    if (key == GLUT_KEY_DOWN) rotate_x += rotate_angle % 360;
    if (key == GLUT_KEY_PAGE_DOWN) translate_z -= translate_lenght;
    if (key == GLUT_KEY_PAGE_UP) translate_z += translate_lenght;

    /*GLfloat precisione = 20;
    GLubyte specialKey = glutGetModifiers();

    if (specialKey == GLUT_ACTIVE_ALT)
    {
            if(key == GLUT_KEY_LEFT)	deltaX -= delta_max/precisione;
            if(key == GLUT_KEY_RIGHT)	deltaX += delta_max/precisione;
            if(key == GLUT_KEY_UP)		deltaY += delta_max/precisione;
            if(key == GLUT_KEY_DOWN)	deltaY -= delta_max/precisione;
    }
    else
    {
            if(key == GLUT_KEY_LEFT)	zRot += 2.0f;
            if(key == GLUT_KEY_RIGHT)	zRot -= 2.0f;
            if(key == GLUT_KEY_UP)		xRot -= 2.0f;
            if(key == GLUT_KEY_DOWN)	xRot += 2.0f;		
    }

    //if(key == GLUT_KEY_PAGE_DOWN)	zoom -= 0.2f;
    //if(key == GLUT_KEY_PAGE_UP)	zoom += 0.2f;
    if(key == GLUT_KEY_PAGE_DOWN)	deltaZ -= delta_max/precisione;
    if(key == GLUT_KEY_PAGE_UP)		deltaZ += delta_max/precisione;
	
    if(key == GLUT_KEY_F1)			iSolid = (iSolid + 1) % 2;
    if(key == GLUT_KEY_F2)			iMorph = (iMorph + 1) % 2;
    if(key == GLUT_KEY_F3)			iThick = (iThick + 1) % 2;
    if(key == GLUT_KEY_F4)			iComp  = (iComp  + 1) % 2;*/

    // Refresh the Window
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'd':
            day = (day + 10) % 360;
            glutPostRedisplay();
            break;
        case 'D':
            day = (day - 10) % 360;
            glutPostRedisplay();
            break;
        case 'y':
            year = (year + 5) % 360;
            glutPostRedisplay();
            break;
        case 'Y':
            year = (year - 5) % 360;
            glutPostRedisplay();
            break;
        case 'b':
            day = (day - 10) % 360;
            year = (year + 5) % 360;
            glutPostRedisplay();
            break;
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}