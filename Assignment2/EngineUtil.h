/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <type_traits>
#include <string>
#include <vector>

#ifdef _WIN32
#include <wincodec.h>
#endif // _WIN32

#include "EngineBasis.h"


namespace LightGameEngine
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

	class EngineUtil
	{
	public:
		static void Init();

		static void SelectFont(int size, const char* face);
		static void DrawString(std::wstring str);

		static DrawCircleArgs GetDefaultDrawCircleArgs();
		static void DrawCircle2D(GLfloat cx, GLfloat cy, GLfloat r, DrawCircleArgs* extraArgs);

		static std::vector<Vector3> GenCircleVertices3D(Vector3 center, GLfloat r, Vector3 normalVector, 
			DrawCircleArgs* extraArgs = NULL, std::vector<Vector2>* out_TexCoord = NULL);

		static void DrawRasterString(GLfloat x, GLfloat y, const char* str);
		static void RasterStringSelectFont(int size, int charset, const char* face);

		static void ThrowIfFail(HRESULT hr);
		static GLubyte* LoadImageFromFile(const std::wstring& imagePath, int bytePerPixel, REFWICPixelFormatGUID dstFormat, GLuint* out_imageWidth, GLuint* out_imageHeight);

		template <typename T>
		inline static void SafeRelease(T*& p)
		{
			if (NULL != p)
			{
				p->Release();
				p = NULL;
			}
		}

	};

}



