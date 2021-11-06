#include "NaiveEngineUtil.h"

using namespace NaiveEngine;

#define MAX_CHAR 128

void NaiveEngineUtil::DrawCircle(GLfloat cx, GLfloat cy, GLfloat r, DrawCircleArgs* extraArgs)
{
	GLfloat x, y, angle;

	DrawCircleArgs arg;
	if (extraArgs == NULL)
	{
		arg = GetDefaultDrawCircleArgs();
	}
	else
	{
		arg = *extraArgs;
	}

	glBegin(arg.drawMode);
	for (angle = arg.startAngle; angle <= arg.endAngle; angle += 0.01f)
	{
		x = cx + arg.xFactor * r * cos(angle);
		y = cy + arg.yFactor * r * sin(angle);
		glVertex3f(x, y, 0.0f);
	}
	glEnd();
}

void NaiveEngineUtil::Select2dStringFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

void NaiveEngineUtil::Draw2dString(GLfloat x, GLfloat y, const char* str)
{
	HDC hdc = wglGetCurrentDC();
	glRasterPos2f(x, y);

	GLuint lists = glGenLists(MAX_CHAR);
	wglUseFontBitmaps(hdc, 0, MAX_CHAR, lists);


	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}

	glDeleteLists(lists, MAX_CHAR);
}

DrawCircleArgs NaiveEngineUtil::GetDefaultDrawCircleArgs()
{
	return DrawCircleArgs {0, 2 * M_PI, 1, 1, GL_POLYGON};
}
