#include "Particle.h"

NaiveEngine::Particle::Particle(GLfloat x, GLfloat y, GLint dissolveTime, ParticleColor color) : GameObject(x, y)
{
	this->dissolveTime = dissolveTime;
	this->color = color;
}

void NaiveEngine::Particle::Draw()
{
	glBegin(GL_POINTS);
	glColor3ub(this->color.r, this->color.g, this->color.b);

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
