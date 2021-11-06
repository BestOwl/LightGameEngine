#pragma once

#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <type_traits>
#include <string>

namespace NaiveEngine
{

	typedef struct DrawCircleArgs
	{
		GLfloat startAngle;
		GLfloat endAngle;
		GLfloat xFactor;
		GLfloat yFactor;
		GLenum drawMode;
	};


	class NaiveEngineUtil
	{
	public:
		static DrawCircleArgs GetDefaultDrawCircleArgs();
		static void DrawCircle(GLfloat cx, GLfloat cy, GLfloat r, DrawCircleArgs* extraArgs);
		static void Draw2dString(GLfloat x, GLfloat y, const char* str);
		static void Select2dStringFont(int size, int charset, const char* face);
	};

}



