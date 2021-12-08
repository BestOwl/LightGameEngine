/*
* Function: mapping an image by pixel
*/

#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>

static GLint imagewidth;
static GLint imageheight;
static GLint pixellength;
static GLubyte* pixeldata;

void myinit(void) {
	// Read in and open an image file
	FILE* pfile = NULL; // The image file should be placed in the same folder with the source code.
	fopen_s(&pfile, "Week11Logo.bmp", "rb"); // read in binary mode

	if (pfile == 0) exit(0);

	// get the width and height of image
	// reposition stream position indicator
	// SEEK_SET: Beginning of file
	fseek(pfile, 0x0012, SEEK_SET); // skip 16 bits from beginning for bmp files

	// get the width of image
	fread(&imagewidth, sizeof(imagewidth), 1, pfile);
	// get the height of image
	fread(&imageheight, sizeof(imageheight), 1, pfile);

	// count the length of in the image by pixel
	// pixel data consists of three colors red, green and blue (Windows implement BGR)
	pixellength = imagewidth * 3;
	// pixel data width should be an integral multiple of 4, which is required by the .bmp file
	while (pixellength % 4 != 0)
		pixellength++;
	// pixel data length = width * height
	pixellength *= imageheight;

	// malloc for the image by pixel
	pixeldata = (GLubyte*)malloc(pixellength); // memory allocation
	if (pixeldata == 0)
		exit(0);

	// read the data of image as pixel
	fseek(pfile, 54, SEEK_SET);
	fread(pixeldata, pixellength, 1, pfile);

	// close file
	fclose(pfile);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the colour and depth buffers
	// write a block of pixels to the frame buffer
	glDrawPixels(imagewidth, imageheight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixeldata);
	glFlush();
}

void myReshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0 * (GLfloat)w / (GLfloat)h, 1.0, 30000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	myinit();
	glutInitWindowSize(imagewidth, imageheight);
	glutCreateWindow("Loading Image by Pixel");
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutMainLoop();
}