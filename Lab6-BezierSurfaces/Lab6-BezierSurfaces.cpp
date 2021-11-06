// Bezier Surfaces

#define FREEGLUT_STATIC
#include <GL/freeglut.h>

GLfloat r = 0; // incremental step for angle of rotation
//Control points

GLfloat ctrlpoints[3][3][3] = {
{{0.0, 2.0, 2.0}, {2.0, 2.0, 2.0}, {2.0, 0.0, 2.0}},
{{0.0, 2.0, 0.0}, {2.0, 2.0, 0.0}, {2.0, 0.0, 0.0}},
{{0.0, 2.0, -2.0}, {2.0, 2.0, -2.0}, {2.0, 0.0, -2.0}},
};

void keyboard_input(unsigned char key, int x, int y) {
	if (key == 'q' || key == 'Q')
		exit(0);
	else if (key == 'i' || key == 'I') {
		r += 1;
		if (r >= 360)
			r = 0;
	}
	else if (key == 'd' || key == 'D') {
		r -= 1;
		if (r <= 0)
			r = 360;
	}
}

void when_in_mainloop() { // idle callback function
	glutPostRedisplay(); // force OpenGL to redraw the current window
}

void myinit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	/* glMap2f defines a two-dimensional evaluator.
	void glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2,
	GLint vstride, GLint vorder, const GLfloat * points);
	Compared with glMap1f, glMap2f adds v1 and v2 to specify a linear mapping of v. The definitions of
	vstride and vorder are the same as ustride and uorder. */
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 3, 0, 1, 9, 3, &ctrlpoints[0][0][0]);
	glEnable(GL_MAP2_VERTEX_3);
	/* glMapGrid2f defines a two-dimensional mesh.
	void glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
	un specifies the number of partitions in the grid range interval [u1, u2]. Must be positive.
	u1 and u2 specify the mappings for integer grid domain values i = 0 and i = un.
	vn specifies the number of partitions in the grid range interval [v1, v2].
	v1 and v2 specify the mappings for integer grid domain values j = 0 and j = vn. */
	glMapGrid2f(20, 0.0f, 1.0f, 20, 0.0f, 1.0f);
	//Do depth comparisons and update the depth buffer.
	glEnable(GL_DEPTH_TEST);
}

void myDisplay(void) {
	myinit();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Plot Bezier surface
	int num1 = 10;
	int num2 = 30;
	glPushMatrix();
	glRotatef(r, 1, 0, 0);
	glPushMatrix();
	for (int m = 0; m <= 3; m++) {
		glRotatef(90, 0.0f, 0.0f, 1.0f);
		glColor3f(1.0, 0.0, 0.0);
		for (int j = 0; j <= num1; j++) {
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i <= num2; i++) {
				/* glEvalCoord2f evaluates the one-dimensional maps that are enabled.
				void glEvalCoord2f(GLfloat u, GLfloat v);
				u specifies a value that is the domain coordinate u to the basis function defined in a
				previous glMap2 function.
				v specifies a value that is the domain coordinate v to the basis function defined in a
				previous glMap2 function. */
				glEvalCoord2f((GLfloat)i / num2, (GLfloat)j / num1);
			}
			glEnd();
			glBegin(GL_LINE_STRIP);
			for (int i = 0; i <= num2; i++) {
				glEvalCoord2f((GLfloat)j / num1, (GLfloat)i / num2);
			}
			glEnd();
		}
	}

	//Plot 9 points
	int m = 0;
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 3; i++) {
			glVertex3fv(&ctrlpoints[j][i][m]);
		}
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();
	glFlush();
}

void myReshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h); // define the viewport
	glMatrixMode(GL_PROJECTION); // projection transformation
	glLoadIdentity(); // clear the matrix
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	gluLookAt(0, 0, 6, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW); // back to modelview matrix
	glLoadIdentity(); // clear the matrix 
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Bezier Surface");
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(keyboard_input);
	glutReshapeFunc(myReshape);
	glutIdleFunc(when_in_mainloop);
	glutMainLoop();
}
