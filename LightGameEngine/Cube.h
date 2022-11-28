/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once
#include "GameObject.h"
#include "Texture.h"

#include <string>

namespace LightGameEngine::GeometricPrimitives
{
	class Cube :
		public GameObject
	{
	public:
		Cube(Vector3 initPos, GLfloat sideLength, CubeTexture* texture);
		~Cube();

		virtual void Draw() override;

	private:
		GLfloat sideLength;
		GLfloat offset;
		CubeTexture* texture;
	};
}

