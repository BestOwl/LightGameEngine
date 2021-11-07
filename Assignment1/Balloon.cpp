#include "Balloon.h"
#include "NaiveEngineUtil.h"

using namespace NaiveEngine;

const GLfloat ctrlpoints[4][3] = { // 4 points to define a cubic Bezier curve
{ -20.0, -110, 0.0 }, // Point 0
{ -20.0, -45, 0.0 }, // Point 1
{ 0, -110, 0.0 }, // Point 2
{ 0, -45, 0.0 } };

Balloon::Balloon(GLfloat x, GLfloat y, BalloonColor color) : GameObject(x, y)
{
	this->Scale = 0.5f;
	this->color = color;
}

void Balloon::Draw()
{
	//glColor3ub(59, 204, 176);
	glColor3ub(this->color.r, this->color.g, this->color.b);
	DrawCircleArgs circleArgs = NaiveEngineUtil::GetDefaultDrawCircleArgs();
	circleArgs.yFactor = 1.5;
	NaiveEngineUtil::DrawCircle(0, 0, 30, &circleArgs);

	circleArgs.drawMode = GL_LINE_STRIP;
	circleArgs.startAngle = M_PI / 8;
	circleArgs.endAngle = circleArgs.startAngle * 3;
	glLineWidth(5);
	glColor3ub(255, 255, 255);
	NaiveEngineUtil::DrawCircle(0, 0, 25, &circleArgs);

#ifdef _DEBUG_CTRL_POINTS // Debug control points
	glPointSize(5.0);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	for (int i = 0; i < 4; i++) {
		glVertex3fv(&ctrlpoints[i][0]); // Draw each control point
	}
	glEnd();
#endif

	// Bezier Curves
	glLineWidth(1);
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3); // Enable the evaluator.
	glColor3ub(1, 1, 1);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 50; i++) {
		/* glEvalCoord1f evaluates the one-dimensional maps that are enabled.
		void glEvalCoord1f(GLfloat u);
		u specifies a value that is the domain coordinate u to the basis function defined in a previous
		glMap1 function. */
		glEvalCoord1f((GLfloat)i / 50);
	}
	glEnd();
}

bool Balloon::Tick()
{
	if (this->y <= 300)
	{
		this->y++;
		return true;
	}
	else
	{
		this->IsDestroyed = true;
		return false;

	}
}
