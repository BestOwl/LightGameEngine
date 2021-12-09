/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#pragma once

#include <GL/freeglut.h>
#include <string>
#include <wincodec.h>

namespace LightGameEngine
{
	class Texture
	{
	public:
		Texture(GLubyte* buffer, GLuint width, GLuint height, GLenum format);
		~Texture();

		void BindTexture();

		GLubyte* Buffer;
		GLuint Width;
		GLuint Height;
		GLenum Format;

		static Texture* LoadTexture(const std::wstring& texturePath);
		static Texture* MakeErrorTexture();

		static IWICImagingFactory* GetWICFactory();

	private:
		static IWICImagingFactory* _pWICFactory;
	};

	class CubeTexture
	{
	public:
		CubeTexture(const std::wstring& texturePath);
		~CubeTexture();

		Texture* Front;
		Texture* Back;
		Texture* Left;
		Texture* Right;
		Texture* Top;
		Texture* Bottom;
	};
}
