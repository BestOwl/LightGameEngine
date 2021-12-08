/*Function: Texture with mipmapping
*/

#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>

GLbyte mipmapImage32[32][32][3];
GLbyte mipmapImage16[16][16][3];
GLbyte mipmapImage8[8][8][3];
GLbyte mipmapImage4[4][4][3];
GLbyte mipmapImage2[2][2][3];
GLbyte mipmapImage1[1][1][3];

// create the texture image
void loadImages(void) {
	int i, j;

	// yellow
	for (i = 0; i < 32; i++) {
		for (j = 0; j < 32; j++) {
			mipmapImage32[i][j][0] = 255.0;
			mipmapImage32[i][j][1] = 255.0;
			mipmapImage32[i][j][2] = 0.0;
		}
	}

	// pink
	for (i = 0; i < 16; i++) {
		for (j = 0; j < 16; j++) {
			mipmapImage16[i][j][0] = 255;
			mipmapImage16[i][j][1] = 0;
			mipmapImage16[i][j][2] = 255;
		}
	}

	// red
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			mipmapImage8[i][j][0] = 255;
			mipmapImage8[i][j][1] = 0;
			mipmapImage8[i][j][2] = 0;
		}
	}

	// green
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			mipmapImage4[i][j][0] = 0;
			mipmapImage4[i][j][1] = 255;
			mipmapImage4[i][j][2] = 0;
		}
	}

	// blue
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			mipmapImage2[i][j][0] = 0;
			mipmapImage2[i][j][1] = 0;
			mipmapImage2[i][j][2] = 255;
		}
	}

	// white
	mipmapImage1[0][0][0] = 255;
	mipmapImage1[0][0][1] = 255;
	mipmapImage1[0][0][2] = 255;
}

// all the texture mipmapping initialisation occurs here
void myinit(void) {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_FLAT);
	//set the texture and create the texture image
	loadImages();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 32, 32, 0, GL_RGB, GL_UNSIGNED_BYTE, &mipmapImage32[0][0][0]);
	glTexImage2D(GL_TEXTURE_2D, 1, 3, 16, 16, 0, GL_RGB, GL_UNSIGNED_BYTE, &mipmapImage16[0][0][0]);
	glTexImage2D(GL_TEXTURE_2D, 2, 3, 8, 8, 0, GL_RGB, GL_UNSIGNED_BYTE, &mipmapImage8[0][0][0]);
	glTexImage2D(GL_TEXTURE_2D, 3, 3, 4, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, &mipmapImage4[0][0][0]);
	glTexImage2D(GL_TEXTURE_2D, 4, 3, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, &mipmapImage2[0][0][0]);
	glTexImage2D(GL_TEXTURE_2D, 5, 3, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, &mipmapImage1[0][0][0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);
}

void display(void) {
	// Clear the colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// set the Texture and vertex coordinates
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
	glTexCoord2f(0.0, 8.0); glVertex3f(-2.0, 1.0, 0.0);
	glTexCoord2f(8.0, 8.0); glVertex3f(2000.0, 1.0, -6000.0);
	glTexCoord2f(8.0, 0.0); glVertex3f(2000.0, -1.0, -6000.0);
	glEnd();
	glFlush();
}

void myReshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0 * (GLfloat)w / (GLfloat)h, 1.0, 30000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// glTranslate moves the coordinate system origin to the point specified by (x, y, z)
	glTranslatef(0.0, 0.0, -3.6);
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Texture Mapping");
	myinit();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMainLoop();
}
