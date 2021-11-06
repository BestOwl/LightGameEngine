// Text and Transformations

#define FREEGLUT_STATIC
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include "windows.h"
#define MAX_CHAR 128

GLdouble x_p = 0; // parameter to define camera position in x-direction
GLdouble z_p = 6; // parameter to define camera position in z-direction
int flag = 1; // flag for value ranges for x_p and z_p

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;
	if (isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}

void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION); //projection transformation
	glLoadIdentity();// clear the matrix
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	gluLookAt(x_p, 0, z_p, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW); // back to modelview matrix
	glLoadIdentity(); // clear the matrix
	glColor3f(1.0, 1.0, 1.0);
	//draw Torus
	glPushMatrix();
	glTranslated(1.5, -1.0, 0.0);
	glutWireTorus(0.5, 1, 12, 12); // inner radius, out radius, number of sides for each 
	 // radial section, number of radial divisions
	glPopMatrix();
	glPushMatrix();
	glTranslated(-1.5, -1.0, 0.0);
	glutSolidTorus(0.5, 1, 12, 12);
	glPopMatrix();
	//Draw 2D text
	selectFont(48, ANSI_CHARSET, "Comic Sans MS");
	glRasterPos2f(0.0, 1.0);
	drawString("Torus");
	glFlush();
}

void myinit(void) {
	glShadeModel(GL_FLAT);
}

void myReshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h); // define the viewport
}

void mouse_input(int button, int state, int x, int y) { // mouse interaction
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		if (x_p < 6 && x_p >= 0 && flag == 1) {
			x_p = x_p + 1;
			z_p = sqrt(36 - x_p * x_p);
		}
		else if (x_p == 6 && flag == 1) {
			x_p = x_p - 1;
			z_p = -sqrt(36 - x_p * x_p);
			flag = 2;
		}
		else if (x_p < 6 && x_p>0 && flag == 2) {
			x_p = x_p - 1;
			z_p = -sqrt(36 - x_p * x_p);
		}
		else if (x_p == 0 && flag == 2) {
			x_p = x_p - 1;
			z_p = -sqrt(36 - x_p * x_p);
			flag = 3;
		}
		else if (x_p > -6 && x_p < 0 && flag == 3) {
			x_p = x_p - 1;
			z_p = -sqrt(36 - x_p * x_p);
		}
		else if (x_p == -6 && flag == 3) {
			x_p = x_p + 1;
			z_p = sqrt(36 - x_p * x_p);
			flag = 4;
		}
		else if (x_p > -6 && x_p < 0 && flag == 4) {
			x_p = x_p + 1;
			z_p = sqrt(36 - x_p * x_p);
		}
		else if (x_p == 0 && flag == 4) {
			x_p = x_p + 1;
			z_p = sqrt(36 - x_p * x_p);
			flag = 1;
		}
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Text and Transformations");
	myinit();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutMouseFunc(mouse_input);
	glutMainLoop();
}