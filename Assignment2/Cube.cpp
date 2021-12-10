#include "Cube.h"

using namespace LightGameEngine::GeometricPrimitives;

Cube::Cube(Vector3 initPos, GLfloat sideLength, CubeTexture* texture) : GameObject(initPos)
{
	this->texture = texture;
	this->sideLength = sideLength;
	this->offset = sideLength / 2.f;
}

Cube::~Cube()
{
	if (this->texture)
	{
		delete this->texture;
	}
}

void Cube::Draw()
{
	if (this->texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
	}

#pragma region Front
	if (this->texture != NULL)
	{
		this->texture->Front->BindTexture();
	}
	glBegin(GL_QUADS);

	glTexCoord2f(1, 1);
	glVertex3f(offset, -offset, -offset);

	glTexCoord2f(0, 1);
	glVertex3f(offset, -offset, offset);

	glTexCoord2f(0, 0);
	glVertex3f(offset, offset, offset);

	glTexCoord2f(1, 0);
	glVertex3f(offset, offset, -offset);

	glEnd();
#pragma endregion

#pragma region Back
	if (this->texture != NULL)
	{
		this->texture->Back->BindTexture();
	}
	glBegin(GL_QUADS);

	glTexCoord2f(1, 1);
	glVertex3f(-offset, -offset, offset);

	glTexCoord2f(0, 1);
	glVertex3f(-offset, -offset, -offset);

	glTexCoord2f(0, 0);
	glVertex3f(-offset, offset, -offset);

	glTexCoord2f(1, 0);
	glVertex3f(-offset, offset, offset);

	glEnd();
#pragma endregion

#pragma region Left
	if (this->texture != NULL)
	{
		this->texture->Left->BindTexture();
	}
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex3f(-offset, -offset, offset);

	glTexCoord2f(1, 1);
	glVertex3f(offset, -offset, offset);

	glTexCoord2f(1, 0);
	glVertex3f(offset, offset, offset);

	glTexCoord2f(0, 0);
	glVertex3f(-offset, offset, offset);

	glEnd();
#pragma endregion


#pragma region Right
	if (this->texture != NULL)
	{
		this->texture->Right->BindTexture();
	}
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glVertex3f(offset, -offset, -offset);

	glTexCoord2f(1, 1);
	glVertex3f(-offset, -offset, -offset);

	glTexCoord2f(1, 0);
	glVertex3f(-offset, offset, -offset);

	glTexCoord2f(0, 0);
	glVertex3f(offset, offset, -offset);

	glEnd();
#pragma endregion

#pragma region Top
	if (this->texture != NULL)
	{
		this->texture->Top->BindTexture();
	}
	glBegin(GL_QUADS);

	glTexCoord2f(1, 0);
	glVertex3f(-offset, offset, -offset);

	glTexCoord2f(0, 0);
	glVertex3f(-offset, offset, offset);

	glTexCoord2f(0, 1);
	glVertex3f(offset, offset, offset);

	glTexCoord2f(1, 1);
	glVertex3f(offset, offset, -offset);

	glEnd();
#pragma endregion

#pragma region Bottom
	if (this->texture != NULL)
	{
		this->texture->Bottom->BindTexture();
	}
	glBegin(GL_QUADS);

	glTexCoord2f(1, 1);
	glVertex3f(-offset, -offset, -offset);

	glTexCoord2f(0, 1);
	glVertex3f(-offset, -offset, offset);

	glTexCoord2f(0, 0);
	glVertex3f(offset, -offset, offset);

	glTexCoord2f(1, 0);
	glVertex3f(offset, -offset, -offset);

	glEnd();
#pragma endregion

	if (this->texture != NULL)
	{
		glDisable(GL_TEXTURE_2D);
	}
}
