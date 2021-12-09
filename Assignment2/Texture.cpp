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

IWICImagingFactory* Texture::pWICFactory = nullptr;

Texture::Texture(GLubyte* buffer, GLuint width, GLuint height, GLenum format)
{
	this->Buffer = buffer;
	this->Width = width;
	this->Height = height;
	this->Format = format;
}

Texture::~Texture()
{
	delete this->Buffer;
}

Texture* Texture::LoadBmpTexture(const std::wstring& texturePath)
{
	FILE* pFile = NULL;
	_wfopen_s(&pFile, texturePath.c_str(), L"rb");

	_ASSERT(pFile != NULL);

	GLuint width;
	GLuint height;

	// get the width and height of image
	// reposition stream position indicator
	// SEEK_SET: Beginning of file
	fseek(pFile, 0x0012, SEEK_SET); // skip 16 bits from beginning for bmp files
	// get the width of image
	fread(&width, sizeof(width), 1, pFile);
	// get the height of image
	fread(&height, sizeof(height), 1, pFile);

	// count the length of in the image by pixel
	// pixel data consists of three colors red, green and blue (Windows implement BGR)
	GLint pixelLength = width * 3;
	// pixel data width should be an integral multiple of 4, which is required by the .bmp file
	while (pixelLength % 4 != 0)
		pixelLength++;
	// pixel data length = width * height
	pixelLength *= height;

	GLubyte* buffer = new GLubyte[pixelLength];

	// read the data of image as pixel
	fseek(pFile, 54, SEEK_SET);
	fread(buffer, pixelLength, 1, pFile);
	fclose(pFile);

	return new Texture(buffer, width, height, GL_BGR_EXT);
}

Texture* Texture::LoadTexture(const std::wstring& texturePath)
{
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pFrame = NULL;
	IWICFormatConverter* pConverter = NULL;
	Texture* pTexture = NULL;

	try
	{
		if (pWICFactory == nullptr)
		{
			EngineUtil::ThrowIfFail(CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWICFactory)));
		}

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

		WICPixelFormatGUID format;
		EngineUtil::ThrowIfFail(pConverter->GetPixelFormat(&format));

		UINT bufferSz = width * height * 4;
		GLubyte* buffer = new GLubyte[bufferSz];

		pConverter->CopyPixels(
			NULL, // rect to copy. NULL specifies the entire bitmap
			width * 4,
			bufferSz,
			buffer
		);

		pTexture = new Texture(buffer, width, height, GL_RGBA);
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
	GLubyte* buffer = new GLubyte[width * height * 3];

	int i, j, c;
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8) == 0))) * 255; // bitwise AND and OR operations,
			buffer[i + j * height + 0] = (GLubyte)c; // which are faster than normal calculations
			buffer[i + j * height + 1] = (GLubyte)c;
			buffer[i + j * height + 2] = (GLubyte)c;
		}
	}
	return new Texture(buffer, width, height, GL_BGR_EXT);
}


