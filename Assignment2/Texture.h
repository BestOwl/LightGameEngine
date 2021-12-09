/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#pragma once

#include <GL/freeglut.h>
#include <string>
#include <wincodec.h>

class Texture
{
public:
	Texture(GLubyte* buffer, GLuint width, GLuint height, GLenum format);
	~Texture();

	GLubyte* Buffer;
	GLuint Width;
	GLuint Height;
	GLenum Format;

	static Texture* LoadBmpTexture(const std::wstring& texturePath);
	static Texture* LoadTexture(const std::wstring& texturePath);
	static Texture* MakeErrorTexture();

private:
	static IWICImagingFactory* pWICFactory;
};

