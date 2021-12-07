// Solar System
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>

void set_initial_state(void);
void myDisplay(void);
void myIdleFunc(void);
void myKeyboardFunc(void);

float mercury = 360;
float venus = 360;
float earth = 360;
float mars = 360;
float jupiter = 360;
float saturn = 360;
float uranus = 360;
float neptune = 360;
float pluto = 360;

GLint winWidth = 700, winHeight = 500; // initial display window size

GLfloat x0 = 0.0, y0 = 1000.0, z0 = 1500.0; // viewing co-ordinate origin
GLfloat xref = 0.0, yref = 50.0, zref = 0.0; // look-at point
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // view-up vector

// co-ordinate limits for clipping window
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;

// positions for near and far clipping planes
GLfloat dnear = 150.0, dfar = 2500.0;

void myReshapeFunc(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}

void myKeyboardFunc(unsigned char key, int x, int y)
{
	//Original viewing co-ordinate origin
	if (key == 'o' || key == 'O')
		x0 = 0.0, y0 = 1000.0, z0 = 1500.0;
	//Sun origin viewing point
	if (key == 's' || key == 'S')
		x0 = 0.0, y0 = 1000.0, z0 = 1.0;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Solar System");
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdleFunc);
	glutReshapeFunc(myReshapeFunc);
	glutKeyboardFunc(myKeyboardFunc);
	set_initial_state();
	glutMainLoop();
}

void set_initial_state(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void myIdleFunc(void)
{
	mercury += 1.4; // incremental angle per frame while 60 frames/second (so very fast)
	venus += 1.2;
	earth += 1.0;
	mars += 0.9;
	jupiter += 0.8;
	saturn += 0.5;
	uranus += 0.6;
	neptune += 0.4;
	pluto += 0.2;

	glutPostRedisplay();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);

	//Solar System
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(90, 1, 0, 0); // from x-y plane to x-z plane
	glutSolidTorus(1, 420, 5, 30); // minor radius, major radius,
	glutSolidTorus(1, 380, 5, 30); // number of sides of section circle and number of sections
	glutSolidTorus(1, 340, 5, 30);
	glutSolidTorus(1, 280, 5, 30);
	glutSolidTorus(1, 220, 5, 30);
	glutSolidTorus(1, 175, 5, 30);
	glutSolidTorus(1, 145, 5, 30);
	glutSolidTorus(1, 120, 5, 30);
	glutSolidTorus(1, 85, 5, 30);
	glTranslatef(0, 0, 0);
	glPopMatrix();

	//Sun
	glPushMatrix();
	glColor3f(1.0, 0.5, 0.2);
	glTranslatef(0, 0, 0);
	glPushMatrix();
	glutSolidSphere(40, 40, 40);
	glPopMatrix();
	glPopMatrix();

	//Mercury
	glPushMatrix();
	glColor3f(0.8, 0.5, 0.2);
	glTranslatef(0, 0, 0);
	glRotatef(mercury, 0, 1, 0);
	glPushMatrix();
	glTranslatef(85, 0, 0); // send Mercury to its obit
	glutSolidSphere(8, 8, 8);
	glPopMatrix();
	glPopMatrix();

	//Venus
	glPushMatrix();
	glColor3f(0.8, 0.8, 1.0);
	glTranslatef(0, 0, 0);
	glRotatef(venus, 0, 1, 0);
	glPushMatrix();
	glTranslatef(120, 0, 0);
	glutSolidSphere(10, 10, 10);
	glPopMatrix();
	glPopMatrix();

	//Earth
	glPushMatrix();
	glColor3f(0.1, 0.3, 1.0);
	glTranslatef(0, 0, 0);
	glRotatef(earth, 0, 1, 0);
	glPushMatrix();
	glTranslatef(145, 0, 0);
	glutSolidSphere(10, 10, 10);
	glPopMatrix();
	glPopMatrix();

	//Mars
	glPushMatrix();
	glColor3f(1.0, 0.2, 0.2);
	glTranslatef(0, 0, 0);
	glRotatef(mars, 0, 1, 0);
	glPushMatrix();
	glTranslatef(175, 0, 0);
	glutSolidSphere(8, 8, 8);
	glPopMatrix();
	glPopMatrix();

	//Jupiter
	glPushMatrix();
	glColor3f(0.8, 0.5, 0.5);
	glTranslatef(0, 0, 0);
	glRotatef(jupiter, 0, 1, 0);
	glPushMatrix();
	glTranslatef(220, 0, 0);
	glutSolidSphere(20, 20, 20);
	glPopMatrix();
	glPopMatrix();

	//Saturn
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.7);
	glRotatef(saturn, 0, 1, 0);
	glTranslatef(280, 0, 0);
	glutSolidSphere(20, 20, 20);

	//Rings Of Saturn
	glPushMatrix();
	glColor3f(0.8, 0.4, 0.2);
	glRotatef(83, 1, 0, 0);
	glutSolidTorus(1, 23, 5, 30);
	glTranslatef(200, 0, 0);
	glPopMatrix();
	glPopMatrix();

	//Uranus
	glPushMatrix();
	glColor3f(0.6, 0.7, 0.6);
	glTranslatef(0, 0, 0);
	glRotatef(uranus, 0, 1, 0);
	glPushMatrix();
	glTranslatef(340, 0, 0);
	glutSolidSphere(16, 16, 16);
	glPopMatrix();
	glPopMatrix();

	//Neptune
	glPushMatrix();
	glColor3f(0.2, 0.5, 1.0);
	glTranslatef(0, 0, 0);
	glRotatef(neptune, 0, 1, 0);
	glPushMatrix();
	glTranslatef(380, 0, 0);
	glutSolidSphere(16, 16, 16);
	glPopMatrix();
	glPopMatrix();

	//Pluto
	glPushMatrix();
	glColor3f(0.5, 0.1, 1.0);
	glTranslatef(0, 0, 0);
	glRotatef(pluto, 0, 1, 0);
	glPushMatrix();
	glTranslatef(420, 0, 0);
	glutSolidSphere(4, 4, 4);
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();
}
