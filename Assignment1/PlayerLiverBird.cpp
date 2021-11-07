#include "PlayerLiverBird.h"

PlayerLiverBird::PlayerLiverBird(GLfloat x, GLfloat y) : Player(x, y)
{
	this->Scale = 0.5;
	this->IsPhysicsEnabled = true;
	this->hasMovementLimit = true;
	this->xMax = 800;
	this->xMin = -400;
	this->yMax = 300;
	this->yMin = -300;
}

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

	// draw wing
	glPushMatrix();
	glColor3ub(180, 180, 180);
	glRotatef(this->windDegree - 7.5, -1, 0, 0);
	glBegin(GL_TRIANGLES);

	glVertex2f(-20, 0);
	glVertex2f(-60, 30);
	glVertex2f(10, 0);

	glEnd();
	glPopMatrix();
#pragma endregion

}

bool PlayerLiverBird::Tick()
{
	this->windDegree += 0.1f;
	if (this->windDegree >= 15)
	{
		this->windDegree = 0;
	}
	return Player::Tick() || true;
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

