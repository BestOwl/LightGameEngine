/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "Cylinder.h"
#include "EngineUtil.h"

#include <vector>

using namespace LightGameEngine;
using namespace LightGameEngine::GeometricPrimitives;

Cylinder::Cylinder(Vector3 initPos, GLfloat radius, GLfloat height, Vector3 axisVector, Texture* texture) : GameObject(initPos)
{
	this->radius = radius;
	this->height = height;
	this->axisVector = axisVector;

	GLfloat norm = height / 2;
	this->offset = axisVector.Scale(norm);

	this->texture = texture;
}

void Cylinder::Draw()
{
	std::vector<Vector2> texCoords;
	std::vector<Vector3> topVertices = EngineUtil::GenCircleVertices3D(this->GetPos() + this->offset, radius, axisVector, NULL, &texCoords);
	std::vector<Vector3> bottomVertices = EngineUtil::GenCircleVertices3D(this->GetPos() - this->offset, radius, axisVector);

	if (this->texture != NULL)
	{
		this->texture->BindTexture();
	}

	glBegin(GL_POLYGON);
	for (int i = 0; i < topVertices.size(); i++)
	{
		glTexCoord2fv((GLfloat*)&texCoords[i]);
		glVertex3fv((GLfloat*) &topVertices[i]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < bottomVertices.size(); i++)
	{
		glTexCoord2fv((GLfloat*)&texCoords[i]);
		glVertex3fv((GLfloat*) &bottomVertices[i]);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < topVertices.size(); i++)
	{
		glTexCoord2f((GLfloat)i / (GLfloat)topVertices.size(), 0);
		glVertex3fv((GLfloat*) &topVertices[i]);
		
		glTexCoord2f((GLfloat)i / (GLfloat)topVertices.size(), 1);
		glVertex3fv((GLfloat*) &bottomVertices[i]);
	}
	glEnd();

	Texture::Unbind();
}
