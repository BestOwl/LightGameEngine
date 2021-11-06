#include "CentralBuilding.h"

#include <GL/freeglut.h>

#define CB_THEME_COLOR 200, 155, 160

void CentralBuilding::Draw() 
{

	glColor3ub(100, 100, 100);
	glRectf(0, 0, 200, 200);

#pragma region upper part
	glColor3ub(255, 250, 245);
	glBegin(GL_QUAD_STRIP);

	glVertex2f(-15, 200 + 15);
	glVertex2f(-15, 85);
	glVertex2f(35, 200 + 15);
	glVertex2f(35, 85);

	glVertex2f(60, 200 - 30);
	glVertex2f(60, 85);

	glVertex2f(80, 200 - 30);
	glVertex2f(80, 85);

	glEnd();

	glBegin(GL_POLYGON);

	glVertex2f(80, 200 + 15);
	glVertex2f(80, 85);
	glVertex2f(100, 85);
	glVertex2f(130, 150);
	glVertex2f(160, 150);
	glVertex2f(160, 200 + 15);

	glEnd();

	glRectf(160, 200 + 15, 200 + 15, 85);



	glLineWidth(10);

	glBegin(GL_LINE_STRIP);

	glColor3ub(CB_THEME_COLOR);
	glVertex2f(35, 200 + 15);
	glVertex2f(60, 200 - 30);
	glVertex2f(80, 200 - 30);
	glVertex2f(80, 200 + 15);

	glEnd();

	glBegin(GL_LINE_STRIP);

	glVertex2f(-15, 85);
	glVertex2f(100, 85);
	glVertex2f(130, 150);
	glVertex2f(160, 150);
	glVertex2f(160, 85);
	glVertex2f(200 + 15, 85);

	glEnd();
#pragma endregion

	
#pragma region lowwer part
	glColor3ub(255, 250, 245);
	glBegin(GL_POLYGON);

	glVertex2f(-15, 10);
	glVertex2f(-15, 25);
	glVertex2f(125, 55);
	glVertex2f(200 + 15, 55);
	glVertex2f(200 + 15, 10);

	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(CB_THEME_COLOR);

	glVertex2f(-15, 25);
	glVertex2f(125, 55);
	glVertex2f(200 + 15, 55);


	glEnd();
#pragma endregion

#pragma region basement
	glColor3ub(100, 100, 100);
	glRectf(-40, 0, 200 + 40, -60);

	glColor3ub(250, 233, 215);
	glRectf(-40, 0, 200 + 40, -10);
	glRectf(-40, -20, 200 + 40, -30);
	glRectf(-40, -40, 200 + 40, -50);

	glColor3ub(184, 204, 166);
	glRectd(-10, -10, 50, -20);
	glRectd(-10, -30, 45, -40);
	glRectd(200 + 10, -10, 200 - 50, -20);
	glRectd(200 + 10, -30, 200 - 45, -40);

	// draw main entrance stair
	glColor3ub(100, 100, 100);
	glBegin(GL_POLYGON);
	glVertex2f(40, -60);
	glVertex2f(55, -5);
	glVertex2f(145, -5);
	glVertex2f(160, -60);
	glEnd();
	glColor3ub(166, 164, 161);
	glBegin(GL_POLYGON);
	glVertex2f(80 - 12, -60);
	glVertex2f(80, -20);
	glVertex2f(120, -20);
	glVertex2f(120 + 12, -60);
	glEnd();

	glColor3ub(CB_THEME_COLOR);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-40, -55);
	glVertex2f(40, -55);
	glVertex2f(55, -5);
	glVertex2f(145, -5);
	glVertex2f(160, -55);
	glVertex2f(200 + 40, -55);
	glEnd();
#pragma endregion


}