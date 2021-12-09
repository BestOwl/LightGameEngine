/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#include "Skybox.h"

using namespace LightGameEngine;

const GLuint boxLength = 5000; 

Skybox::Skybox(Vector3 initPos) : GameObject(initPos)
{
	this->front = Texture::LoadTexture(L"skybox_front.jpg");
	this->back = Texture::LoadTexture(L"skybox_back.jpg");
	this->left = Texture::LoadTexture(L"skybox_left.jpg");
	this->right = Texture::LoadTexture(L"skybox_right.jpg");
	this->top = Texture::LoadTexture(L"skybox_top.jpg");
	this->bottom = Texture::LoadTexture(L"skybox_bottom.jpg");
}

Skybox::~Skybox()
{
	delete this->front;
	delete this->back;
	delete this->left;
	delete this->right;
	delete this->top;
	delete this->bottom;
}

void Skybox::Draw()
{
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLfloat offset = static_cast<GLfloat>(boxLength) / 2;

#pragma region Front
	glTexImage2D(GL_TEXTURE_2D, 0, 4, this->front->Width, this->front->Height, 0, this->front->Format, GL_UNSIGNED_BYTE, this->front->Buffer);
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
	glTexImage2D(GL_TEXTURE_2D, 0, 4, this->back->Width, this->back->Height, 0, this->back->Format, GL_UNSIGNED_BYTE, this->back->Buffer);
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
	glTexImage2D(GL_TEXTURE_2D, 0, 4, this->left->Width, this->left->Height, 0, this->left->Format, GL_UNSIGNED_BYTE, this->left->Buffer);
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
	glTexImage2D(GL_TEXTURE_2D, 0, 4, this->right->Width, this->right->Height, 0, this->right->Format, GL_UNSIGNED_BYTE, this->right->Buffer);
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
	glTexImage2D(GL_TEXTURE_2D, 0, 4, this->top->Width, this->top->Height, 0, this->top->Format, GL_UNSIGNED_BYTE, this->top->Buffer);
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
	glTexImage2D(GL_TEXTURE_2D, 0, 4, this->bottom->Width, this->bottom->Height, 0, this->bottom->Format, GL_UNSIGNED_BYTE, this->bottom->Buffer);
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
