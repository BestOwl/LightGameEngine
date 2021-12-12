/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#pragma once

#include "Texture.h"

using namespace LightGameEngine;

class TextureStore
{
public:
	static void Init();

	static CubeTexture* Skybox;
	static Texture* Terrain;
};
