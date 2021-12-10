/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "TextureStore.h"

CubeTexture* TextureStore::Skybox;

void TextureStore::Init()
{
	Skybox = new CubeTexture(L"skybox.jpg");
}
