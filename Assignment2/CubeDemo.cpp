/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#include "CubeDemo.h"

#include <cassert>

GLubyte* CubeDemo::textureImage = nullptr;
GLint CubeDemo::textureImageWidth = 0;
GLint CubeDemo::textureImageHeight = 0;

CubeDemo::CubeDemo(Vector3 initPos) : GameObject(initPos)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, "cube_demo.bmp", "rb");

	_ASSERT(pFile != NULL);

	// get the width and height of image
	// reposition stream position indicator
	// SEEK_SET: Beginning of file
	fseek(pFile, 0x0012, SEEK_SET); // skip 16 bits from beginning for bmp files
	// get the width of image
	fread(&this->textureImageWidth, sizeof(this->textureImageWidth), 1, pFile);
	// get the height of image
	fread(&this->textureImageHeight, sizeof(this->textureImageHeight), 1, pFile);

	// count the length of in the image by pixel
	// pixel data consists of three colors red, green and blue (Windows implement BGR)
	GLint pixelLength = this->textureImageWidth * 3;
	// pixel data width should be an integral multiple of 4, which is required by the .bmp file
	while (pixelLength % 4 != 0)
		pixelLength++;
	// pixel data length = width * height
	pixelLength *= this->textureImageHeight;

	this->textureImage = new GLubyte[pixelLength];

	// read the data of image as pixel
	fseek(pFile, 54, SEEK_SET);
	fread(this->textureImage, pixelLength, 1, pFile);
	fclose(pFile);
}

void CubeDemo::Draw()
{
	glEnable(GL_TEXTURE_2D);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, 3, this->textureImageWidth, this->textureImageHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, this->textureImage);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);

	glTexCoord2f(1, 0);
	glVertex3f(-25, 0, 0);

	glTexCoord2f(0, 0);
	glVertex3f(25, 0, 0);

	glTexCoord2f(0, 1);
	glVertex3f(25, 50, 0);

	glTexCoord2f(1, 1);
	glVertex3f(-25, 50, 0);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}
