#include "GameObject.h"

using namespace NaiveEngine;

GLfloat GameObject::getX()
{
	return this->x;
}

GLfloat GameObject::getY()
{
	return this->y;
}

bool NaiveEngine::GameObject::Tick()
{
	return false;
}

GameObject::GameObject(GLfloat x, GLfloat y)
{
	this->x = x;
	this->y = y;
}
