#include "Firework.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <ctime>

constexpr int particleAmount = 1;

Firework::Firework(GLfloat x, GLfloat y) : GameObject(x, y)
{
	this->initalX = x;
	this->initalY = y;
}

void Firework::Explode()
{
	// use current system and current pos as random seed
	/*srand(time(NULL) + this->x * 100 + this->y * 100);
	for (int i = 0; i < particleAmount; i++)
	{
		GLint randX = rand() % 100 - 50;
		GLint randY = rand() % 100 - 50;
		Particle* particle = new Particle(randX, randY);
		particle->IsPhysicsEnabled = true;
		particle->VelocityX = 10;
		this->ChildrenObjects.push_back(particle);
	}*/

	// use current system and current pos as random seed
	srand(time(NULL) + this->x * 100 + this->y * 100);

	//GLfloat initV = 10;
	for (int i = 0; i < 90; i++)
	{
		GLint initV = rand() % 10;
		int degree = i * 4;
		Particle* particle = new Particle(0, 0, 100);
		particle->IsPhysicsEnabled = true;
		particle->VelocityX = cos(degree * M_PI / 180) * initV;
		particle->VelocityY = sin(degree * M_PI / 180) * initV;
		this->ChildrenObjects.push_back(particle);
	}
}

void Firework::Draw()
{
	switch (this->state)
	{
	case 0:
		glColor3ub(148, 40, 40);
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 15);
		glVertex2f(-5, 0);
		glVertex2f(5, 0);
		glEnd();

		glColor3ub(53, 53, 53);
		glRectf(-3, 0, 3, -30);

		// use current system and current pos as random seed
		srand(time(NULL) + this->x * 50 + this->y * 50);
		
		glPointSize(2);
		glBegin(GL_POINTS);

		for (int i = 0; i < 10; i++)
		{
			GLint randX = rand() % 6 - 3;
			GLint randY = rand() % 30 - 60;
			glVertex2i(randX, randY);
		}

		glEnd();

		break;
	case 2:
		glPointSize(2);
		break;
	default:
		break;
	}
}

bool Firework::Tick()
{
	switch (this->state)
	{
	case FireworkState::Flying:
		if (this->y < this->initalY + this->flyHeight)
		{
			this->y++;
		}
		else {
			this->state = FireworkState::Explode;
		}
		return true;

	case FireworkState::Explode:
		Explode();
		this->state = FireworkState::Drop;
		break;
	case FireworkState::Drop:
		if (this->ChildrenObjects.size() == 0)
		{
			this->IsDestroyed = true;
		}
	default:
		break;
	}

	return false;
}
