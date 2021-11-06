// File ID: Lab03
// Title: 
// Author: 

#define FREEGLUT_STATIC
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/freeglut.h>

typedef struct { GLfloat x, y; } point; // define a 2D point
point p0 = { 0,50 }; // set initial co-ordinate values of the point
GLfloat finishx = 300; // declare position of vertical axis

//Task 2
GLfloat step = 10; // declare incremental step
int time_interval = 16; // declare refresh interval in ms

void when_in_mainloop()
{ // idle callback function
	glutPostRedisplay(); // force OpenGL to redraw the current window
}

void OnTimer(int value)
{
	p0.x += step;
	if (p0.x >= 600)
		p0.x = 0;
	else if (p0.x <= 0)
		p0.x = 599;
	//when_in_mainloop();
	glutTimerFunc(time_interval, OnTimer, 1);
}

//Task 3
void keyboard_input(unsigned char key, int x, int y) // keyboard interactions
{
	if (key == 'q' || key == 'Q')
		exit(0);
	else if (key == 'f' || key == 'F') // change direction of movement
		step = -step;
	else if (key == 's' || key == 'S') // stop movement
		step = 0;
	else if (key == 'r' || key == 'R') // reset step (resume movement)
		step = 10;
}

//Task 4
void mouse_input(int button, int state, int x, int y) // mouse interactions
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && step >= -15)
		step -= 1; // decrement step
	else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON && step <= 15)
		step += 1; // increment step
}

void display(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 400);
	glClearColor(0, 0, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex2f(finishx, 50);
	glVertex2f(finishx, 350);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, 50);
	glVertex2f(600, 50);
	glVertex2f(600, 0);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(p0.x, p0.y);
	glVertex2f(p0.x, p0.y + 20);
	glVertex2f(p0.x + 30, p0.y + 20);
	glVertex2f(p0.x + 30, p0.y);
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 400);
	glutCreateWindow("My Interactive Window");
		
	glutDisplayFunc(display);

	//Task 2
	glutIdleFunc(when_in_mainloop);
	/* glutIdleFunc sets the global idle callback to be func so a GLUT program can perform background
	processing tasks or continuous animation when window system events are not being received.
	If enabled, the idle callback is continuously called when events are not being received. The callback
	routine has no parameters. The current window and current menu will not be changed before the idle
	callback. Programs with multiple windows and/or menus should explicitly set the current window and/or
	current menu and not rely on its current setting. The amount of computation and rendering done in an idle
	callback should be minimized to avoid affecting the program's interactive response. In general, not more
	than a single frame of rendering should be done in an idle callback.
	Assigning NULL to glutIdleFunc disables the generation of the idle callback.*/
	glutTimerFunc(time_interval, OnTimer, 1);
	
	//Task 3
	glutKeyboardFunc(keyboard_input); // keyboard callback function 
	
	//Task 4
	glutMouseFunc(mouse_input); // mouse callback function

	glutMainLoop();
}