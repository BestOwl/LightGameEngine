/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "EngineBasis.h"

LightGameEngine::Vector3 LightGameEngine::operator+(const Vector3& vec3L, const Vector3& vec3R)
{
	return { vec3L.x + vec3R.x, vec3L.y + vec3R.y, vec3L.z + vec3R.z };
}

LightGameEngine::Vector3& LightGameEngine::operator+=(Vector3& vec3L, const Vector3& vec3R)
{
	vec3L.x += vec3R.x;
	vec3L.y += vec3R.y;
	vec3L.z += vec3R.z;
	return vec3L;
}


