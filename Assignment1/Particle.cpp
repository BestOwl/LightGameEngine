#include "Particle.h"

NaiveEngine::Particle::Particle(GLfloat x, GLfloat y, GLint dissolveTime) : GameObject(x, y)
{
	this->dissolveTime = dissolveTime;
}

void NaiveEngine::Particle::Draw()
{
	glBegin(GL_POINTS);

	glVertex2f(0, 0);

	glEnd();
}

bool NaiveEngine::Particle::Tick()
{
	this->dissolveTime--;
	if (this->dissolveTime < 0)
	{
		this->IsDestroyed = true;
	}

	return GameObject::Tick();
}
