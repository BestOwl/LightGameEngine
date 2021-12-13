/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once
#include "AABBox.h"

namespace LightGameEngine
{
	class CollisionEngine
	{
	public:
		std::vector<AABBox*> AabbBoxes;
		AABBox* HitTest(AABBox* aabb);

		static CollisionEngine* GetInstance();

	private:
		/// <summary>
		/// Return true if hit
		/// </summary>
		bool hitTest(AABBox* a, AABBox* b);
		GLfloat axisOverlap(GLfloat amax, GLfloat amin, GLfloat bmax, GLfloat bmin);

		static CollisionEngine* _collisionEngine;
	};
}
