#pragma once

#include <GL/freeglut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <type_traits>
#include <string>

namespace NaiveEngine
{

	typedef struct {
		unsigned char r;
		unsigned char g;
		unsigned char b;
	} Color;

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
		static void Init();

		static void SelectFont(int size, const char* face);
		static void DrawString(std::wstring str);

		static DrawCircleArgs GetDefaultDrawCircleArgs();
		static void DrawCircle(GLfloat cx, GLfloat cy, GLfloat r, DrawCircleArgs* extraArgs);

		static void DrawRasterString(GLfloat x, GLfloat y, const char* str);
		static void RasterStringSelectFont(int size, int charset, const char* face);

	};

}



