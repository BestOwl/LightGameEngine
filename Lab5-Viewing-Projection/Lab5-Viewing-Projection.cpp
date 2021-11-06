// Viewing/Projection Functions

#define FREEGLUT_STATIC
#include <math.h>
#include <iostream>
#include <gl/freeglut.h>

// A teapot for viewing
void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glutWireTeapot(2); // draw a wireframe teapot
	glFlush();
}

void myinit(void) {
	glShadeModel(GL_FLAT);
}

void myReshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h); // define viewport
	glMatrixMode(GL_PROJECTION); // projection transformation
	glLoadIdentity(); // clear the matrix
	glFrustum(0, 1.0, 0, 1.0, 1.5, 20.0);
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW); // back to modelview matrix
	glLoadIdentity(); // clear the matrix
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Teapot");
	myinit();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMainLoop();
}