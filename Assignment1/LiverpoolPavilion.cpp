#include "LiverpoolPavilion.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/freeglut.h>

using namespace NaiveEngine;

void drawCircle(GLfloat cx, GLfloat cy, GLfloat r, GLfloat startAngle = 0, GLfloat endAngle = 2.0f * M_PI) {
	GLfloat x, y, angle;

	glBegin(GL_POLYGON);
	for (angle = startAngle; angle <= endAngle; angle += 0.01f)
	{
		x = cx + r * sin(angle);
		y = cy + r * cos(angle);
		glVertex3f(x, y, 0.0f);
	}
	glEnd();
}

void LiverpoolPavilion::Draw()
{
	int x = 0;
	int x_step = 10;
	int pillar_width = 8;
	int pillar_amount = 6;

	glColor3ub(250, 250, 250);

	for (int i = 0; i < pillar_amount; i++)
	{
		glRectf(x, 0, x + pillar_width, 50);
		x += x_step + pillar_width;
	}

	int boarder_width = pillar_amount * (pillar_width + x_step) + 10;
	glRectf(-10, 52.5, -10 + boarder_width, 55);
	glRectf(-10, -2.5, -10 + boarder_width, -5);

	GLfloat r = boarder_width / 2 / cos(0.2 * M_PI);
	drawCircle(49, 15, r, -0.3 * M_PI, 0.3 * M_PI);
	drawCircle(49, 72.5, 30, -0.4 * M_PI, 0.4 * M_PI);
}