/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#include "EngineUtil.h"
#include "Texture.h"

#include <iostream>
#include <comdef.h>

using namespace LightGameEngine;

#define MAX_CHAR 128

void EngineUtil::DrawCircle2D(GLfloat cx, GLfloat cy, GLfloat r, DrawCircleArgs* extraArgs)
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

std::vector<Vector3> EngineUtil::GenCircleVertices3D(Vector3 center, GLfloat r, Vector3 normalVector, 
	DrawCircleArgs* extraArgs, std::vector<Vector2>* out_TexCoord)
{
	std::vector<Vector3> vertices;

	// Calculate the axis vectors (three vectors are perpendicular to each other)
	Vector3 vec = Vector3{ 0, 0, 1 };
	if (vec == normalVector)
	{
		vec += Vector3{ 0, 1, 0 };
	}
	Vector3 a = normalVector.CrossProduct(vec);
	a.ScaleTo(1); // to unit vector

	vec = Vector3{ 1, 0, 0 };
	if (vec == normalVector)
	{
		vec += Vector3{ 0, 1, 0 };
	}
	Vector3 b = normalVector.CrossProduct(vec);
	b.ScaleTo(1);

	DrawCircleArgs arg;
	if (extraArgs == NULL)
	{
		arg = GetDefaultDrawCircleArgs();
	}
	else
	{
		arg = *extraArgs;
	}

	for (GLfloat angle = arg.startAngle; angle <= arg.endAngle; angle += 0.01f)
	{
		GLfloat plane_a = arg.xFactor * cos(angle);
		GLfloat plane_b = arg.yFactor * sin(angle);

		if (out_TexCoord != NULL)
		{
			out_TexCoord->push_back(Vector2{ plane_a / 2.f + 0.5f, 0.5f - plane_b / 2.f });
		}

		Vector3 v1 = r * plane_a * a;
		Vector3 v2 = r * plane_b * b;

		Vector3 cp = center + v1 + v2;
		vertices.push_back(cp);
	}
	if (arg.endAngle - arg.startAngle == 2 * M_PI)
	{
		vertices.push_back(vertices.front());
		if (out_TexCoord != NULL)
		{
			out_TexCoord->push_back(out_TexCoord->front());
		}
	}

	return vertices;
}

BitmapFont* EngineUtil::RasterStringSelectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);

	GLuint bitmapFontLists = glGenLists(MAX_CHAR);
	HDC hdc = wglGetCurrentDC();
	wglUseFontBitmaps(hdc, 0, MAX_CHAR, bitmapFontLists);
	return new BitmapFont(bitmapFontLists);
}

void EngineUtil::DrawRasterString(BitmapFont* font, GLfloat x, GLfloat y, const std::string& str)
{
	glRasterPos2f(x, y);
	font->DrawString(str);
}

DrawCircleArgs EngineUtil::GetDefaultDrawCircleArgs()
{
	return DrawCircleArgs {0, 2 * M_PI, 1, 1, GL_POLYGON};
}

void EngineUtil::ThrowIfFail(HRESULT hr)
{
	if (FAILED(hr))
	{
		throw _com_error(hr);
	}
}

GLubyte* LightGameEngine::EngineUtil::LoadImageFromFile(const std::wstring& imagePath, int bytePerPixel, REFWICPixelFormatGUID dstFormat, GLuint* out_imageWidth, GLuint* out_imageHeight)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pFrame = NULL;
	IWICFormatConverter* pConverter = NULL;
	GLubyte* buffer = NULL;
	try
	{
		IWICImagingFactory* pWICFactory = Texture::GetWICFactory();

		EngineUtil::ThrowIfFail(pWICFactory->CreateDecoderFromFilename(
			imagePath.c_str(),
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnDemand,
			&pDecoder
		));

		EngineUtil::ThrowIfFail(pDecoder->GetFrame(0, &pFrame));

		pWICFactory->CreateFormatConverter(&pConverter);
		EngineUtil::ThrowIfFail(pConverter->Initialize(
			pFrame,							// Input bitmap source
			dstFormat,	// Destination pixel format
			WICBitmapDitherTypeNone,		// dither pattern
			NULL,							// Specify a particular palette 
			0.0f,							// Aplha threshold
			WICBitmapPaletteTypeCustom		// Palette translation type
		));

		pConverter->GetSize(out_imageWidth, out_imageHeight);

		UINT bufferSz = *out_imageWidth * *out_imageHeight * bytePerPixel;
		buffer = new GLubyte[bufferSz];

		pConverter->CopyPixels(
			NULL, // rect to copy. NULL specifies the entire bitmap
			*out_imageWidth * bytePerPixel,
			bufferSz,
			buffer
		);
	}
	catch (_com_error err)
	{
		std::wcout << err.Description() << std::endl;
	}
	EngineUtil::SafeRelease(pConverter);
	EngineUtil::SafeRelease(pFrame);
	EngineUtil::SafeRelease(pDecoder);
	return buffer;
}

LightGameEngine::BitmapFont::BitmapFont(GLuint bitmapFontLists)
{
	this->bitmapFontLists = bitmapFontLists;
}

LightGameEngine::BitmapFont::~BitmapFont()
{
	glDeleteLists(this->bitmapFontLists, MAX_CHAR);
}

void LightGameEngine::BitmapFont::DrawString(const std::string& str)
{
	glListBase(this->bitmapFontLists);
	glCallLists(str.size(), GL_UNSIGNED_BYTE, str.c_str());
}
