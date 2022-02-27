/*
 * Stampa su standard output le informazioni base della scheda grafica e di OpenGL.
 * Inoltre, effettua il log delle funzioni di callback.
 */

#include <iostream>
#include <GL/glut.h>
using namespace std;

void init();
void display();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);

int counter = 0;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Esercitazione 1");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;
}

void init() {
    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
    cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
    cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
    cout << "Extensions: " << glGetString(GL_EXTENSIONS) << endl;
    GLboolean stereo;
    glGetBooleanv(GL_STEREO, &stereo);
    if (stereo) {
        cout << "STEREO ENABLED" << endl;
    } else {
        cout << "STEREO DISABLED" << endl;
    }
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display() {
    cout << ++counter << " DISPLAY" << endl;
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void reshape(int w, int h) {
    cout << ++counter << " RESHAPE[width=" << w << ", height=" << h << "]" << endl;
    glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y) {
    cout << ++counter << " KEYBOARD[key=" << key << ", x=" << x << ", y=" << y << "]" << endl;
}

void mouse(int button, int state, int x, int y) {
    cout << ++counter << " MOUSE[button=" << button << ", state=" << state << ", x=" << x << ", y=" << y << "]" << endl;
}

void motion(int x, int y) {
    cout << ++counter << " MOTION[x=" << x << ", y=" << y << "]" << endl;
}