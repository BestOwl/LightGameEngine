/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "Sphere.h"

using namespace LightGameEngine;
using namespace LightGameEngine::GeometricPrimitives;

Sphere::Sphere(Vector3 initPos, GLfloat radius) : GameObject(initPos)
{
	this->radius = radius;
}

void Sphere::Draw()
{
	GLUquadric* quadric = gluNewQuadric();
	gluSphere(quadric, this->radius, 100, 100);
	gluDeleteQuadric(quadric);
}
