// Train System
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>
#include<math.h>

int intWinWidth = 600; //Default window size
int intWinHeight = 400;

float fltAnimationOffset = 0.0; //Animation offsets for various objects
float fltTreeOffset = 0.0;
float fltBuildingOffset = -2500.0;
float fltPoleOffset = 750.0;
float fltAcceleration = 1.0; //Speed of animation

float fltColourVal1 = 0.5; //First colour value
float fltColourVal2 = 0.7; //Second colour value
float fltColourVal3 = 0.4; //Third colour value

float fltFOV = 70; //Field Of View
float fltZoom = 1.0; //Zoom amount
float fltX0 = 0.0; //Camera position
float fltY0 = 150.0;
float fltZ0 = -500.0;
float fltXRef = 0.0; //Look At reference point
float fltYRef = 0.0;
float fltZRef = 0.0;
float fltXUp = 0.0; //Up vector
float fltYUp = 1.0;
float fltZUp = 0.0;
float fltViewingAngle = 0; //Used for rotating camera

void animateTracks()
{
	//Increments/decrements animation variables
	fltAnimationOffset -= fltAcceleration;
	if (fltAnimationOffset <= -20.0)
		fltAnimationOffset = 0.0;
	else if (fltAnimationOffset >= 0.0)
		fltAnimationOffset = -20.0;

	fltPoleOffset -= fltAcceleration;
	if (fltPoleOffset <= -400.0)
		fltPoleOffset = 0.0;
	else if (fltPoleOffset >= 0.0)
		fltPoleOffset = -400.0;

	fltTreeOffset -= fltAcceleration;
	if (fltTreeOffset <= -2500.0)
		fltTreeOffset = 2500.0;
	else if (fltTreeOffset >= 2500.0)
		fltTreeOffset = -2500.0;

	fltBuildingOffset -= fltAcceleration;
	if (fltBuildingOffset <= -2500.0)
		fltBuildingOffset = 2500.0;
	else if (fltBuildingOffset >= 2500.0)
		fltBuildingOffset = -2500.0;

	glutPostRedisplay();
}

void groundAndTracks()
{
	//========TELEGRAPH POLES========
	for (int fltPoleNumber = -25; fltPoleNumber < 25; fltPoleNumber += 4.0)
	{
		glPushMatrix();
		glTranslatef(-200.0, 0.0, ((fltPoleNumber * 100) + fltPoleOffset));
		glPushMatrix();
		glTranslatef(0.0, 200.0, 0.0);
		glScalef(80.0, 10.0, 10.0);
		glColor3f(0.7, 0.3, 0.0);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(0.0, 100.0, 0.0);
		glScalef(7.0, 200.0, 7.0);
		glColor3f(0.7, 0.3, 0.0);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1);
		glPopMatrix();
		glPopMatrix();
	}

	//========BUILDINGS========
	glPushMatrix();
	glTranslatef(-400.0, 0.0, fltBuildingOffset);
	glPushMatrix();
	glTranslatef(0.0, 75, 0.0);
	glScalef(200.0, 150.0, 1000.0);
	glColor3f(fltColourVal1, fltColourVal2, fltColourVal3);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(400.0, 0.0, fltBuildingOffset);
	glPushMatrix();
	glTranslatef(0.0, 75, 0.0);
	glScalef(400.0, 200.0, 600.0);
	glColor3f(fltColourVal3, fltColourVal1, fltColourVal2);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	//========TREE========
	glPushMatrix();
	glTranslatef(150.0, 0.0, fltTreeOffset);
	glPushMatrix();
	glTranslatef(0.0, 100.0, 0.0);
	glScalef(60.0, 65.0, 60.0);
	glColor3f(0.0, 0.7, 0.1);
	glutSolidIcosahedron();
	glColor3f(0.0, 0.0, 0.0);
	glutWireIcosahedron();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.0, 25.0, 0.0);
	glScalef(15.0, 50.0, 15.0);
	glColor3f(0.7, 0.3, 0.0);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	//========TRACKS========
	glPushMatrix();
	glTranslatef(-75.0, 5.0, 0.0);
	glScalef(5.0, 5.0, 5000.0);
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(75.0, 5.0, 0.0);
	glScalef(5.0, 5.0, 5000.0);
	glPushMatrix();
	glColor3f(0.3, 0.3, 0.3);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();

	//========TRACK SLEEPERS========
	for (int intSleeper = -249; intSleeper < 250; intSleeper += 2)
	{
		float fltZOffset = intSleeper * 10;
		glPushMatrix();
		glTranslatef(0.0, 0.0, fltZOffset + fltAnimationOffset);
		glScalef(200.0, 5.0, 10.0);
		glPushMatrix();
		glColor3f(0.5, 0.25, 0.0);
		glutSolidCube(1);
		glColor3f(0.0, 0.0, 0.0);
		glutWireCube(1);
		glPopMatrix();
		glPopMatrix();
	}

	//========GROUND========
	glPushMatrix();
	glTranslatef(0.0, -10.0, 0.0);
	glScalef(5000.0, 10.0, 5000.0);
	glPushMatrix();
	glColor3f(0.3, 1.0, 0.2);
	glutSolidCube(1);
	glColor3f(0.0, 0.0, 0.0);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
}

void displayObject()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fltFOV, 1, 0.1, 5000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(fltX0 * fltZoom, fltY0 * fltZoom, fltZ0 * fltZoom, fltXRef, fltYRef, fltZRef, fltXUp,
		fltYUp, fltZUp);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2, 0.2, 0.8, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	groundAndTracks();
	glutSwapBuffers();
}

void reshapeWindow(GLint intNewWidth, GLint intNewHeight)
{
	glViewport(0, 0, intNewWidth, intNewHeight);
}

void adjustDisplay(unsigned char key, int x, int y)
{
	if (key == '-' || key == '_')
		fltAcceleration -= 0.5; //Speed down
	if (key == '=' || key == '+')
		fltAcceleration += 0.5; //Speed up
	if (key == 'd' || key == 'D')
		if (fltY0 > 35)
			fltY0 -= 5; //Camera down
	if (key == 'u' || key == 'U')
		if (fltY0 < 500)
			fltY0 += 5; //Camera up
	if (key == 'i' || key == 'I')
		if (fltZoom > 0.2)
			fltZoom -= 0.1; //Zoom in
	if (key == 'o' || key == 'O')
		if (fltZoom < 5.0)
			fltZoom += 0.1; //Zoom out
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(intWinWidth, intWinHeight);
	glutCreateWindow("Train System");
	glutDisplayFunc(displayObject);
	glutReshapeFunc(reshapeWindow);
	glutKeyboardFunc(adjustDisplay);
	glutIdleFunc(animateTracks); // try to understand static scene by turning this off
	glutMainLoop();
}
