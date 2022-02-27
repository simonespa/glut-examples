/* 
 * File:   main.cpp
 * Author: saimon
 *
 * Created on 24 September 2012, 12:00
 * 
 * This program shows how to composite modeling transformations
 * to draw translated and rotated models.
 * Interaction:  pressing the d and y keys (day and year)
 * alters the rotation of the planet around the sun.
 */

#include <GL/glut.h>

static int year = 0, day = 0, year2 = 0, day2 = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SMOOTH);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(1.0, 20, 16); /* draw sun */

    glPushMatrix();
    glRotatef((GLfloat) year, 0.0, 1.0, 0.0);
    glTranslatef(3.0, 0.0, 0.0);

    glColor3f(0.0, 1.0, 1.0);

    glPushMatrix();
    glRotatef((GLfloat) day, 0.0, 1.0, 0.0);
    glutSolidSphere(0.2, 10, 8); /* draw smaller planet */
    glPopMatrix();

    glRotatef((GLfloat) year2, 0.0, 1.0, 0.0);
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat) day2, 0.0, 1.0, 0.0);
    glutSolidSphere(0.1, 10, 8); /* draw satellite */
    glPopMatrix();

    glPushMatrix();
    glRotatef((GLfloat) year, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 1.0, 0.0);

    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
    glRotatef((GLfloat) day, 1.0, 0.0, 0.0);
    glutSolidSphere(0.2, 10, 8); /* draw smaller planet */
    glPopMatrix();

    glRotatef((GLfloat) year2, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 1.0, 0.0);
    glRotatef((GLfloat) day2, 1.0, 0.0, 0.0);
    glutSolidSphere(0.1, 10, 8); /* draw satellite */
    glutSolidTeapot(10);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'd':
            day = (day + 10) % 360;
            glutPostRedisplay();
            break;
        case 'D':
            day2 = (day2 - 10) % 360;
            glutPostRedisplay();
            break;
        case 'y':
            year = (year + 5) % 360;
            glutPostRedisplay();
            break;
        case 'Y':
            year2 = (year2 - 5) % 360;
            glutPostRedisplay();
            break;
        case 'b':
            day = (day - 10) % 360;
            year = (year + 5) % 360;
            day2 = (day2 - 10) % 360;
            year2 = (year2 + 5) % 360;
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
    glutInitWindowSize(640, 360);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}