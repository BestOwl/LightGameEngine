/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "Texture.h"
#include "EngineUtil.h"

#include <comdef.h>
#include <iostream>

using namespace LightGameEngine;

IWICImagingFactory* Texture::_pWICFactory = nullptr;

Texture::Texture(GLubyte* buffer, GLuint width, GLuint height, GLenum format)
{
	glGenTextures(1, &this->Name);
	glBindTexture(GL_TEXTURE_2D, this->Name);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, format, GL_UNSIGNED_BYTE, buffer);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	if (this->Name)
	{
		glDeleteTextures(1, &this->Name);
	}
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, this->Name);
}

void LightGameEngine::Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture* Texture::LoadTexture(const std::wstring& texturePath)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pFrame = NULL;
	IWICFormatConverter* pConverter = NULL;
	Texture* pTexture = NULL;

	try
	{
		IWICImagingFactory* pWICFactory = Texture::GetWICFactory();

		EngineUtil::ThrowIfFail(pWICFactory->CreateDecoderFromFilename(
			texturePath.c_str(),
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnDemand,
			&pDecoder
		));

		EngineUtil::ThrowIfFail(pDecoder->GetFrame(0, &pFrame));

		// Convert to BGRA format
		pWICFactory->CreateFormatConverter(&pConverter);
		EngineUtil::ThrowIfFail(pConverter->Initialize(
			pFrame,							// Input bitmap source
			GUID_WICPixelFormat32bppRGBA,	// Destination pixel format
			WICBitmapDitherTypeNone,		// dither pattern
			NULL,							// Specify a particular palette 
			0.0f,							// Aplha threshold
			WICBitmapPaletteTypeCustom		// Palette translation type
		));

		UINT width;
		UINT height;
		pConverter->GetSize(&width, &height);

		UINT bufferSz = width * height * 4;
		GLubyte* buffer = new GLubyte[bufferSz];

		pConverter->CopyPixels(
			NULL, // rect to copy. NULL specifies the entire bitmap
			width * 4,
			bufferSz,
			buffer
		);

		pTexture = new Texture(buffer, width, height, GL_RGBA);
		delete[] buffer;
	}
	catch (_com_error err)
	{
		std::wcout << err.Description() << std::endl;
	}
	EngineUtil::SafeRelease(pConverter);
	EngineUtil::SafeRelease(pFrame);
	EngineUtil::SafeRelease(pDecoder);

	if (pTexture == NULL)
	{
		pTexture = MakeErrorTexture();
	}
	return pTexture;
}

Texture* Texture::MakeErrorTexture()
{
	GLuint width = 64;
	GLuint height = 64;
	GLubyte* buffer = new GLubyte[width * height * 4];

	int i, j, c;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8) == 0))) * 255; // bitwise AND and OR operations,
			buffer[i + j * height + 0] = (GLubyte)c; // which are faster than normal calculations
			buffer[i + j * height + 1] = (GLubyte)c;
			buffer[i + j * height + 2] = (GLubyte)c;
			buffer[i + j * height + 3] = 1;
		}
	}
	return new Texture(buffer, width, height, GL_RGBA);
}

IWICImagingFactory* Texture::GetWICFactory()
{
	if (_pWICFactory == nullptr)
	{
		EngineUtil::ThrowIfFail(CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_pWICFactory)));
	}
	return _pWICFactory;
}

CubeTexture::CubeTexture(const std::wstring& texturePath)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pFrame = NULL;
	IWICFormatConverter* pConverter = NULL;

	Texture** textures[] =
	{
		&this->Left,
		&this->Front,
		&this->Right,
		&this->Back,
		&this->Top,
		&this->Bottom
	};

	try
	{
		IWICImagingFactory* pWICFactory = Texture::GetWICFactory();

		EngineUtil::ThrowIfFail(pWICFactory->CreateDecoderFromFilename(
			texturePath.c_str(),
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnDemand,
			&pDecoder
		));

		EngineUtil::ThrowIfFail(pDecoder->GetFrame(0, &pFrame));

		// Convert to BGRA format
		pWICFactory->CreateFormatConverter(&pConverter);
		EngineUtil::ThrowIfFail(pConverter->Initialize(
			pFrame,							// Input bitmap source
			GUID_WICPixelFormat32bppRGBA,	// Destination pixel format
			WICBitmapDitherTypeNone,		// dither pattern
			NULL,							// Specify a particular palette 
			0.0f,							// Aplha threshold
			WICBitmapPaletteTypeCustom		// Palette translation type
		));

		UINT width;
		UINT height;
		pConverter->GetSize(&width, &height);
		if (width % 6 != 0)
		{
			goto end;
		}

		UINT widthPerFace = width / 6;

		for (int i = 0; i < 6; i++)
		{
			UINT bufferSz = widthPerFace * height * 4;
			GLubyte* buffer = new GLubyte[bufferSz];

			WICRect rect =
			{
				widthPerFace * i, //x
				0,
				widthPerFace,
				height
			};

			pConverter->CopyPixels(
				&rect, // rect to copy. NULL specifies the entire bitmap
				widthPerFace * 4,
				bufferSz,
				buffer
			);
			*textures[i] = new Texture(buffer, widthPerFace, height, GL_RGBA);
		}
	}
	catch (_com_error err)
	{
		std::wcout << L"Failed to load texture file: " << texturePath << std::endl;
	}

end:
	EngineUtil::SafeRelease(pConverter);
	EngineUtil::SafeRelease(pFrame);
	EngineUtil::SafeRelease(pDecoder);

	Texture* errorTexture = NULL;
	for (int i = 0; i < 6; i++)
	{
		if (*textures[i] == NULL)
		{
			if (errorTexture == NULL)
			{
				errorTexture = Texture::MakeErrorTexture();
			}
			*textures[i] = errorTexture;
		}
	}
}

LightGameEngine::CubeTexture::CubeTexture(Texture* front, Texture* back, Texture* left, Texture* right, Texture* top, Texture* bottom)
{
	this->Front = front;
	this->Back = back;
	this->Left = left;
	this->Right = right;
	this->Top = top;
	this->Bottom = bottom;
}

CubeTexture::~CubeTexture()
{
	if (this->Front)
	{
		delete this->Front;
	}
	if (this->Back)
	{
		delete this->Back;
	}
	if (this->Left)
	{
		delete this->Left;
	}
	if (this->Right)
	{
		delete this->Right;
	}
	if (this->Top)
	{
		delete this->Top;
	}
	if (this->Bottom)
	{
		delete this->Bottom;
	}
}
