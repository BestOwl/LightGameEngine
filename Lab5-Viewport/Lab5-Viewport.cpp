#define FREEGLUT_STATIC
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>

GLint scale = 1;
GLint stepx = 0;
GLint stepy = 0;
GLint width = 500;
GLint height = 500;

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glutWireTeapot(0.5); // draw a wireframe teapot
	glFlush();
}

void idleDisplay() {
	if (scale == 0)
		scale = 1;
	glViewport(stepx, stepy, width / scale, height / scale);
	glutPostRedisplay();
}

void keyboard_input(unsigned char key, int x, int y) { // keyboard interaction
	if (key == 'q' || key == 'Q')
		exit(0);
	else if (key == 'l' || key == 'L') // move the viewport to the left
		stepx--;
	else if (key == 'u' || key == 'U') // move the viewport up
		stepy++;
	else if (key == 'r' || key == 'R') // move the viewport to the right
		stepx++;
	else if (key == 'd' || key == 'D') // move the viewport down
		stepy--;
	else if (key == 's' || key == 'S') // shrink the viewport
		scale++;
	else if (key == 'e' || key == 'E') // enlarge the viewport
		scale--;
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(width, height);
	glutCreateWindow("Teapot");
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(keyboard_input);
	glutIdleFunc(idleDisplay);
	glutMainLoop();
}