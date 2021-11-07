#include "Player.h"

void NaiveEngine::Player::Draw()
{
	glColor3ub(0, 255, 0);
	glRectf(0, 0, 50, 50);
}

void NaiveEngine::Player::SetX(GLfloat newX)
{
	if (this->hasMovementLimit)
	{
		if (newX > this->xMax)
		{
			newX = this->xMax;
		}
		if (newX < this->xMin)
		{
			newX = this->xMin;
		}
	}
	this->x = newX;
}

void NaiveEngine::Player::SetY(GLfloat newY)
{
	if (this->hasMovementLimit)
	{
		if (newY > this->yMax)
		{
			newY = this->yMax;
		}
		if (newY < this->yMin)
		{
			newY = this->yMin;
		}
	}
	this->y = newY;
}
