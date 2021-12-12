/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#include "EngineUtil.h"
#include "Texture.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

#ifdef _WIN32
#include <Knownfolders.h>
#include <shlobj_core.h>
#include <comdef.h>
#include <codecvt>
#include <locale>
#endif // _WIN32


using namespace LightGameEngine;

#define MAX_CHAR 128

static FT_Library ft_lib;
static FT_Face ft_face;

void EngineUtil::Init()
{
	FT_Error error = FT_Init_FreeType(&ft_lib);
	if (error)
	{
		MessageBox(NULL, L"Failed to init FreeType library", L"FATAL ERROR", MB_ICONERROR);
		throw;
	}
}

//void EngineUtil::SelectFont(int size, const char* face)
//{
//	std::string facePath;
//#ifdef _WIN32
//	IKnownFolderManager* pManager;
//	HRESULT hr = CoCreateInstance(CLSID_KnownFolderManager, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pManager));
//	if (SUCCEEDED(hr)) {
//	}
//	else {
//		_com_error err(hr);
//		throw err;
//	}
//
//	IKnownFolder* pFolder;
//	pManager->GetFolder(FOLDERID_Fonts, &pFolder);
//
//	LPWSTR wFolderPath = NULL;
//	pFolder->GetPath(KF_FLAG_DEFAULT, &wFolderPath);
//
//	std::wstring wsFolderPath(wFolderPath);
//
//	facePath = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wsFolderPath);
//	facePath = facePath + "\\" + face;
//#elif __linux__
//	facePath = "/usr/share/fonts/truetype/" + face;
//#endif // _WIN32
//
//	FT_Error error = FT_New_Face(ft_lib,
//		facePath.c_str(),
//		0,
//		&ft_face);
//
//	FT_Set_Char_Size(
//		ft_face,    /* handle to face object           */
//		0,       /* char_width in 1/64th of points  */
//		size * 64,   /* char_height in 1/64th of points */
//		300,     /* horizontal device resolution    */
//		300);
//}

void DrawGlyphBitmap(int pen_x, int pen_y, wchar_t c)
{
	FT_Load_Char(ft_face, c, FT_LOAD_RENDER);

	if (ft_face->glyph->format != FT_Glyph_Format::FT_GLYPH_FORMAT_BITMAP)
	{
		FT_Render_Glyph(ft_face->glyph, FT_RENDER_MODE_NORMAL);
	}

	//assert(ft_face->glyph->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY);

	pen_x += ft_face->glyph->bitmap_left;
	pen_y += ft_face->glyph->bitmap_top;

	for (int j = 0; j < ft_face->glyph->bitmap.rows; j++)
	{
		for (int i = 0; i < ft_face->glyph->bitmap.width; i++)
		{
			glColor4ub(0, 0, 0, ((uint8_t*)ft_face->glyph->bitmap.buffer)[j * ft_face->glyph->bitmap.width + i]);
			glBegin(GL_POINTS);
			glVertex2f(pen_x + i, pen_y - j);
			glEnd();
		}
	}
}

void EngineUtil::DrawString(std::wstring str)
{
	glColor4ub(0, 0, 0, 0);

	GLint x = 0;
	GLint y = 0;

	for (wchar_t c : str)
	{
		DrawGlyphBitmap(x, y, c);

		x += ft_face->glyph->advance.x / 64;
	}
}

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

void EngineUtil::RasterStringSelectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

void EngineUtil::DrawRasterString(GLfloat x, GLfloat y, const char* str)
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
