#include "HandHeldWindmill.h"

void drawWindmillBody()
{
	glBegin(GL_POLYGON);
	
	glColor3ub(3, 6, 69);
	glVertex2f(0, 0);
	glVertex2f(0, 20);

	glColor3ub(84, 39, 121);
	glVertex2f(30, 20);

	glColor3ub(207, 90, 200);
	glVertex2f(60, 0);

	glEnd();
}

void HandHeldWindmill::Draw()
{
	// draw hand held
	glColor3ub(230, 200, 170);
	glRectf(-3, -3, 3, -100);

	// rotate the entire windmill body
	glRotatef(this->rotate, 0, 0, 1);

#pragma region windmill body
	drawWindmillBody();

	glRotatef(90, 0, 0, 1);
	drawWindmillBody();

	glRotatef(90, 0, 0, 1);
	drawWindmillBody();

	glRotatef(90, 0, 0, 1);
	drawWindmillBody();
#pragma endregion

	
}

bool HandHeldWindmill::Tick()
{
	this->rotate++;
	if (this->rotate == 360)
	{
		this->rotate = 0;
	}

	return true;
}
