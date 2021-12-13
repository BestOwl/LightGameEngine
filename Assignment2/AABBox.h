/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once
#include "EngineBasis.h"

#include <vector>

using namespace LightGameEngine;


namespace LightGameEngine
{
	class GameObject;

	class AABBox
	{
	public:
		AABBox(Vector3 min, Vector3 max);

		Vector3 MinPos;
		Vector3 MaxPos;
		GameObject* Obj;

		bool ToBeDestoryed = false;
	};
}
