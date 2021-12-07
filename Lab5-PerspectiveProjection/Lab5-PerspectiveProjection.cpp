// Perspective projection

#define FREEGLUT_STATIC
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>

// Angles of rotation
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

// Change the view volume and viewport. This is called when the window is resized.
void ChangeSize(int w, int h) {
	GLfloat fAspect;
	if (h == 0) // Avoid division by zero
		h = 1;
	glViewport(0, 0, w, h); // Set viewport to window dimensions
	fAspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION); // Reset coordinate system
	glLoadIdentity();
	gluPerspective(60.0f, fAspect, 1.0, 600.0); // Set viewing volume
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Setting up lighting and material parameters for enhanced rendering effect.
// This topic will be covered later on in the module so please skip this for now.
void SetupRC() {
	// Light parameters and coordinates
	GLfloat whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
	GLfloat sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
	GLfloat lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };
	glEnable(GL_DEPTH_TEST); // Hidden surface removal
	glEnable(GL_LIGHTING); // Enable lighting
	// Setup and enable light0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sourceLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL); // Enable colour tracking
	// Set material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
}

// Respond to arrow keys
void SpecialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	xRot = (GLfloat)((const int)xRot % 360);
	yRot = (GLfloat)((const int)yRot % 360);
	glutPostRedisplay(); // Refresh the window
}

// Draw scene
void RenderScene(void) {
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Perform the depth test to render multiple objects in the correct order of Z-axis value
	glEnable(GL_DEPTH_TEST); // Hidden surface removal
	glPushMatrix(); // Save the matrix state and perform rotations
	glTranslatef(0.0f, 0.0f, -300.0f);
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidTeapot(25);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -100.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidTeapot(25);
	glPopMatrix();
	glPopMatrix(); // Restore the matrix state
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Perspective Projection");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
	return 0;
}