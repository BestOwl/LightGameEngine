// File ID: Lab04a.cpp
// Title: Geometric Transformations
// Author:

#define FREEGLUT_STATIC
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>

int width = 400;
int height = 300;
float t = 0.0;
float r = 0.0;
float s = 1.0;

void when_in_mainloop() { // idle callback function
	glutPostRedisplay(); // force OpenGL to redraw the current window
}

void keyboard_input(unsigned char key, int x, int y) {// keyboard interaction
	if (key == 'q' || key == 'Q')
		exit(0);
	else if (key == 't' || key == 'T')
		t += 0.05;
	else if (key == 'b' || key == 'B')
		t -= 0.05;
	else if (key == 'r' || key == 'R')
		r--;
	else if (key == 'a' || key == 'A')
		r++;
	else if (key == 'i' || key == 'I')
		s += 0.01;
	else if (key == 'd' || key == 'D')
		s -= 0.01;

	glutPostRedisplay();
}

void DrawTriangles()
{
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 0.5);
	glVertex2f(0.5, 0);
	glEnd();
}

void display(void)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	//Draw reference axes
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(-1, 0); // start location
	glVertex2f(1, 0); // end location
	glVertex2f(0, -1); // start location
	glVertex2f(0, 1); // end location
	glEnd();

	glPushMatrix();
	glTranslatef(t, 0, 0); // the order of these transformations may affect the result
	glScalef(s, s, 0); // because of the non-commutative features
	glRotatef(r, 0, 0, 1); // here the translation is applied last
	DrawTriangles();
	glPopMatrix();

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Lab04 Demo");

	glutDisplayFunc(display);
	//glutIdleFunc(when_in_mainloop);
	glutKeyboardFunc(keyboard_input);

	glutMainLoop();
}