#include "Firework.h"

#include <ctime>

Firework::Firework(GLfloat x, GLfloat y) : GameObject(x, y)
{
	this->initalX = x;
	this->initalY = y;
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

		// use current system as random seed
		srand(time(NULL));
		
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
	default:
		break;
	}
}

bool Firework::Tick()
{
	switch (this->state)
	{
	case 0:
		if (this->y < this->initalY + this->flyHeight)
		{
			this->y++;
		}
		else {
			this->state = 1;
		}
		return true;
	default:
		break;
	}

	return false;
}
