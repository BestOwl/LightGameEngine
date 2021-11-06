#include "Player.h"

void NaiveEngine::Player::Draw()
{
	glColor3ub(0, 255, 0);
	glRectf(0, 0, 50, 50);
}

void NaiveEngine::Player::SetX(GLfloat newX)
{
	this->x = newX;
}

void NaiveEngine::Player::SetY(GLfloat newY)
{
	this->y = newY;
}
