/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#include "EngineUtil.h"

#include <ft2build.h>
#include FT_FREETYPE_H

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

void EngineUtil::SelectFont(int size, const char* face)
{
	std::string facePath;
#ifdef _WIN32
	IKnownFolderManager* pManager;
	HRESULT hr = CoCreateInstance(CLSID_KnownFolderManager, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pManager));
	if (SUCCEEDED(hr)) {
	}
	else {
		_com_error err(hr);
		throw err;
	}

	IKnownFolder* pFolder;
	pManager->GetFolder(FOLDERID_Fonts, &pFolder);

	LPWSTR wFolderPath = NULL;
	pFolder->GetPath(KF_FLAG_DEFAULT, &wFolderPath);

	std::wstring wsFolderPath(wFolderPath);

	facePath = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(wsFolderPath);
	facePath = facePath + "\\" + face;
#elif __linux__
	facePath = "/usr/share/fonts/truetype/" + face;
#endif // _WIN32

	FT_Error error = FT_New_Face(ft_lib,
		facePath.c_str(),
		0,
		&ft_face);

	FT_Set_Char_Size(
		ft_face,    /* handle to face object           */
		0,       /* char_width in 1/64th of points  */
		size * 64,   /* char_height in 1/64th of points */
		300,     /* horizontal device resolution    */
		300);
}

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

void EngineUtil::DrawCircle(GLfloat cx, GLfloat cy, GLfloat r, DrawCircleArgs* extraArgs)
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
