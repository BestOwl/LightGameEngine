#include "Cube.h"

using namespace LightGameEngine::GeometricPrimitives;

Cube::Cube(Vector3 initPos, GLfloat sideLength, const std::wstring& texturePath) : GameObject(initPos)
{
	this->texture = new CubeTexture(texturePath);
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
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

#pragma region Front
	this->texture->Front->BindTexture();
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
	this->texture->Back->BindTexture();
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
	this->texture->Left->BindTexture();
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
	this->texture->Right->BindTexture();
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
	this->texture->Top->BindTexture();
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
	this->texture->Bottom->BindTexture();
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

	glDisable(GL_TEXTURE_2D);
}
