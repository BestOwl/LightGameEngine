#define FREEGLUT_STATIC
#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include "windows.h"
#define MAX_CHAR 128

void displayFunc();
void draw();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("ArtBoard");

	glutDisplayFunc(displayFunc);
	//glutKeyboardFunc(keyboard_input);
	//glutIdleFunc(idleDisplay);

	glutMainLoop();
}

void drawCircle(GLfloat cx, GLfloat cy, GLfloat r, GLfloat startAngle = 0, GLfloat endAngle = 2.0f * M_PI) {
	GLfloat x, y, angle;

	glBegin(GL_POLYGON);
	for (angle = startAngle; angle <= endAngle; angle += 0.01f)
	{
		x = cx + r * sin(angle);
		y = cy + r * cos(angle);
		glVertex3f(x, y, 0.0f);
	}
	glEnd();
}

void drawString(const char* str, GLfloat x, GLfloat y) {

	HDC hdc = wglGetCurrentDC();
	glRasterPos2f(x, y);

	GLuint lists = glGenLists(MAX_CHAR);
	wglUseFontBitmaps(hdc, 0, MAX_CHAR, lists);


	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}

	glDeleteLists(lists, MAX_CHAR);
}

void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

void draw()
{
	selectFont(48, ANSI_CHARSET, "Comic Sans MS");
	drawString("Hello", 100, 100);

	selectFont(24, ANSI_CHARSET, "Comic Sans MS");
	drawString("Hello world!", 0, 0);
}

void wglTextTest()
{
	HDC hdc = wglGetCurrentDC();
	// create an OpenGL rendering context  
	HGLRC hglrc = wglCreateContext(hdc);

	// make it this thread's current rendering context  
	wglMakeCurrent(hdc, hglrc);

	// make the color a deep blue hue  
	glClearColor(0.0F, 0.0F, 0.4F, 1.0F);

	// make the shading smooth 
	glShadeModel(GL_SMOOTH);

	// clear the color buffers  
	glClear(GL_COLOR_BUFFER_BIT);

	// specify a red triangle  
	glBegin(GL_TRIANGLES);
	glColor3f(1.0F, 0.0F, 0.0F);
	glVertex2f(10.0F, 10.0F);
	glVertex2f(250.0F, 50.0F);
	glVertex2f(105.0F, 280.0F);
	glEnd();

	// create bitmaps for the device context font's first 256 glyphs  
	wglUseFontBitmaps(hdc, 0, 256, 1000);

	// move bottom left, southwest of the red triangle  
	glRasterPos2f(30.0F, 300.0F);

	// set up for a string-drawing display list call  
	glListBase(1000);

	// draw a string using font display lists  
	glCallLists(12, GL_UNSIGNED_BYTE, "Red Triangle");

	// get all those commands to execute  
	glFlush();

	// delete our 256 glyph display lists  
	glDeleteLists(1000, 256);

	// make the rendering context not current  
	wglMakeCurrent(NULL, NULL);

	// release the device context  
	//ReleaseDC(hdc);

	// delete the rendering context  
	wglDeleteContext(hglrc);
}

void displayFunc()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int L = -400;
	int R = 400;
	int B = -300;
	int T = 300;
	gluOrtho2D(L, R, B, T);

	//glShadeModel(GL_FLAT);
	//draw();

	/*glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	glPointSize(5);
	glColor3ub(255, 255, 255);
	glVertex2f(0, 0);
	glVertex2f(100, 0);
	glVertex2f(100, 100);
	glEnd();

	glPushMatrix();
	glTranslatef(100, 100, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-100, -100, 0);
	glPopMatrix();

	glPopMatrix();*/

	wglTextTest();

	glFlush();
}
