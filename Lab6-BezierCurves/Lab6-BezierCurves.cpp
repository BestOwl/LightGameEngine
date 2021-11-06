// Bezier Curves

#define FREEGLUT_STATIC
#include <GL/freeglut.h>

GLfloat step = 2;

GLfloat ctrlpoints[4][3] = { // 4 points to define a cubic Bezier curve
{ -2.0, -2.0, 0.0 }, // Point 0
{ -2.0, 2.0, 0.0 }, // Point 1
{ 2.0, -2.0, 0.0 }, // Point 2
{ 2.0, 2.0, 0.0 } }; // Point 3

void when_in_mainloop() { // idle callback function
	glutPostRedisplay(); // force OpenGL to redraw the current window
}

void keyboard_input(unsigned char key, int x, int y) {
	if (key == 'q' || key == 'Q')
		exit(0);
	else if (key == 'i' || key == 'I') {
		step++;
		if (step > 4)
			step = 4;
	}
	else if (key == 'd' || key == 'D') {
		step--;
		if (step < 2)
			step = 2;
	}
}

void myinit(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	/* glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points)
	glMap1f defines a one-dimensional evaluator.
	target specifies what the control points represent. It also specifies the type of points, e.g.
	GL_MAP1_VERTEX_3: Each control point has three floating-point values representing x, y, and z.
	GL_MAP1_VERTEX_4: Each control point has four floating-point values representing x, y, z and w.
	GL_MAP1_TEXTURE_COORD_3: Each control point has three floating-point values representing the s, t, and
	r texture coordinates.
	GL_MAP1_TEXTURE_COORD_4: Each control point is four floating-point values representing the s, t, r and
	q texture coordinates.
	u1 and u2 specify a linear mapping of u.
	stride specifies the number of floats or doubles between the beginning of a control point and the
	beginning of the next in the data structure referenced in points.
	order specifies the number of control points. It must be positive.
	points specifies a pointer to the array of control points */
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, step, &ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3); // Enable the evaluator.
}

void myDisplay(void) {
	myinit();
	glClear(GL_COLOR_BUFFER_BIT);
	//Plot Bezier Curve between Point 1 and Point 4
	glColor3f(1.0, 1.0, 1.0);
	int number = 50;
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= number; i++) {
		/* glEvalCoord1f evaluates the one-dimensional maps that are enabled.
		void glEvalCoord1f(GLfloat u);
		u specifies a value that is the domain coordinate u to the basis function defined in a previous
		glMap1 function. */
		glEvalCoord1f((GLfloat)i / number);
	}
	glEnd();
	//Plot 4 Points
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++) {
		glVertex3fv(&ctrlpoints[i][0]); // Draw each control point
	}
	glEnd();
	glFlush();
}

void myReshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h); // define the viewport
	glMatrixMode(GL_PROJECTION); // the projection transformation
	glLoadIdentity(); // clear the matrix
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW); // back to modelview matrix
	glLoadIdentity(); // clear the matrix 
	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Bezier");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(when_in_mainloop);
	glutKeyboardFunc(keyboard_input);
	glutMainLoop();
}