/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "Sphere.h"

using namespace LightGameEngine;
using namespace LightGameEngine::GeometricPrimitives;

Sphere::Sphere(Vector3 initPos, GLfloat radius, Texture* texture) : GameObject(initPos)
{
	this->radius = radius;
	this->texture = texture;
}

void Sphere::Draw()
{
	GLUquadric* quadric = gluNewQuadric();
	if (this->texture != NULL)
	{
		this->texture->BindTexture();
	}
	
	gluQuadricTexture(quadric, GL_TRUE);
	//gluQuadricNormals()
	gluSphere(quadric, this->radius, 100, 100);
	
	gluDeleteQuadric(quadric);
	Texture::Unbind();
}
