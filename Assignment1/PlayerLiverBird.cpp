#include "PlayerLiverBird.h"

void PlayerLiverBird::Draw()
{
#pragma region Rotate the liver bird
	glRotatef(180 * this->rotateMode, 0, 1, 0);
#pragma endregion

#pragma region Render the liver bird
	glColor3ub(1, 44, 113);

	glBegin(GL_POLYGON);

	glVertex2f(-50, 0);
	glVertex2f(50, 0);
	glVertex2f(25, -30);
	glVertex2f(-25, -30);

	glEnd();



	glBegin(GL_TRIANGLES);
	
	glVertex2f(-20, 0);
	glVertex2f(-60, 30);
	glVertex2f(10, 0);

	glEnd();



	glBegin(GL_POLYGON);

	glVertex2f(25, 0);
	glVertex2f(25, 35);
	glVertex2f(50, 30);
	glVertex2f(80, 0);

	glEnd();



	// draw bird's left feet
	glBegin(GL_POLYGON);

	glVertex2f(-20, -30);
	glVertex2f(-25, -50);
	glVertex2f(-15, -45);
	glVertex2f(-15, -30);

	glEnd();

	glBegin(GL_TRIANGLES);

	glVertex2f(-25, -50);
	glVertex2f(-15, -45);
	glVertex2f(-5, -50);

	glEnd();

	// draw bird's right feet
	glBegin(GL_POLYGON);

	glVertex2f(15, -30);
	glVertex2f(10, -50);
	glVertex2f(20, -45);
	glVertex2f(20, -30);

	glEnd();

	glBegin(GL_TRIANGLES);

	glVertex2f(10, -50);
	glVertex2f(20, -45);
	glVertex2f(30, -50);

	glEnd();

	glPointSize(5);
	glColor3ub(255, 255, 255);
	glBegin(GL_POINTS);
	glVertex2f(50, 15);
	glEnd();
#pragma endregion

}

void PlayerLiverBird::SetX(GLfloat newX)
{
	if (newX > this->x)
	{
		this->rotateMode = 0;
	}
	else if (newX < this->x)
	{
		this->rotateMode = 1;
	}

	Player::SetX(newX);

}

