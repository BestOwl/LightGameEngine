// File ID: prog2.cpp
// Title: Working with Graphics Primitives

#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <math.h>

void define_to_OpenGL();
void draw_axes();
void draw_origin();
void plot_sine_wave();
void draw_triangle();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	// Task 2
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(50, 50);

	

	glutCreateWindow("Graphics Primitives");
	glutDisplayFunc(define_to_OpenGL);
	glutMainLoop();
}


void define_to_OpenGL()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	// The stuff to appear on screen goes here
	
	// Task 2
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int L = -100;
	int R = 500;
	int B = -200;
	int T = 200;
	gluOrtho2D(L, R, B, T);
	
	// Task 3
	draw_axes();

	// Task 4
	draw_origin();

	// Task 5
	plot_sine_wave();

	// Tasks 6, 7 and 8
	draw_triangle();

	glFlush();
}

void draw_axes() 
{
	glLineWidth(1.0);
	glColor3f(0 , 0 , 0 );
	glBegin(GL_LINES);

	glVertex2f(0, 0); // start location
	glVertex2f(450, 0); // end location

	glVertex2f(0, -150);
	glVertex2f(0, 150);

	glEnd();
}

void draw_origin()
{
	glPointSize(10);
	glColor3f(255 , 0 , 0 );
	glBegin(GL_POINTS);
	glVertex2f(0 , 0 );
	glEnd();
}

void plot_sine_wave()
{
	// draw a sine wave
	int i;
	float x, y;
	glColor3f(0.0, 0.0, 1.0);
	glPointSize(1);
	glBegin(GL_LINE_STRIP);
	for (i = 0; i < 361; i = i + 5)
	{
		x = (float)i;
		y = 100.0 * sin(i * (6.284 / 360.0));
		glVertex2f(x, y);
	}
	glEnd();
}

void draw_triangle() {
	//glShadeModel(GL_FLAT);
	glBegin(GL_TRIANGLES);

	glColor3f(255, 0, 0);
	glVertex2f(-50, 50);

	glColor3f(0, 255, 0);
	glVertex2f(-50, 0);

	glColor3f(0, 0, 255);
	glVertex2f(0, 0);

	glEnd();
}