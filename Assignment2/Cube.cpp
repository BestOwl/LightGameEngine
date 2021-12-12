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
#pragma region Front
	if (this->texture != NULL && this->texture->Front != NULL)
	{
		this->texture->Front->BindTexture();
	}
	Vector3 normal = { 1, 0, 0 };
	glBegin(GL_QUADS);

	glTexCoord2f(1, 1);
	glNormal3fv((GLfloat*) & normal);
	glVertex3f(offset, -offset, -offset);

	glTexCoord2f(0, 1);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(offset, -offset, offset);

	glTexCoord2f(0, 0);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(offset, offset, offset);

	glTexCoord2f(1, 0);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(offset, offset, -offset);

	glEnd();
	Texture::Unbind();
#pragma endregion

#pragma region Back
	if (this->texture != NULL && this->texture->Back != NULL)
	{
		this->texture->Back->BindTexture();
	}
	normal = { -1, 0, 0 };
	glBegin(GL_QUADS);

	glTexCoord2f(1, 1);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(-offset, -offset, offset);

	glTexCoord2f(0, 1);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(-offset, -offset, -offset);

	glTexCoord2f(0, 0);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(-offset, offset, -offset);

	glTexCoord2f(1, 0);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(-offset, offset, offset);

	glEnd();
	Texture::Unbind();
#pragma endregion

#pragma region Left
	if (this->texture != NULL && this->texture->Left != NULL)
	{
		this->texture->Left->BindTexture();
	}
	normal = { 0, 0, 1 };
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(-offset, -offset, offset);

	glTexCoord2f(1, 1);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(offset, -offset, offset);

	glTexCoord2f(1, 0);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(offset, offset, offset);

	glTexCoord2f(0, 0);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(-offset, offset, offset);

	glEnd();
	Texture::Unbind();
#pragma endregion


#pragma region Right
	if (this->texture != NULL && this->texture->Right != NULL)
	{
		this->texture->Right->BindTexture();
	}
	normal = { 0, 0, -1 };
	glBegin(GL_QUADS);

	glTexCoord2f(0, 1);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(offset, -offset, -offset);

	glTexCoord2f(1, 1);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(-offset, -offset, -offset);

	glTexCoord2f(1, 0);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(-offset, offset, -offset);

	glTexCoord2f(0, 0);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(offset, offset, -offset);

	glEnd();
	Texture::Unbind();
#pragma endregion

#pragma region Top
	if (this->texture != NULL && this->texture->Top != NULL)
	{
		this->texture->Top->BindTexture();
	}
	normal = { 0, 1, 0 };
	glBegin(GL_QUADS);

	glTexCoord2f(1, 0);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(-offset, offset, -offset);

	glTexCoord2f(0, 0);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(-offset, offset, offset);

	glTexCoord2f(0, 1);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(offset, offset, offset);

	glTexCoord2f(1, 1);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(offset, offset, -offset);

	glEnd();
	Texture::Unbind();
#pragma endregion

#pragma region Bottom
	if (this->texture != NULL && this->texture->Bottom != NULL)
	{
		this->texture->Bottom->BindTexture();
	}
	normal = { 0, -1, 0 };
	glBegin(GL_QUADS);

	glTexCoord2f(1, 1);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(-offset, -offset, -offset);

	glTexCoord2f(0, 1);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(-offset, -offset, offset);

	glTexCoord2f(0, 0);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(offset, -offset, offset);

	glTexCoord2f(1, 0);
	glNormal3fv((GLfloat*)&normal);
	glVertex3f(offset, -offset, -offset);

	glEnd();
	Texture::Unbind();
#pragma endregion

}
