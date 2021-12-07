/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once

#include <GL/freeglut.h>

namespace LightGameEngine
{
	typedef struct
	{
		bool Forward;
		bool Backward;
		bool Left;
		bool Right;
	} KeyboardStatus;

	typedef struct {
		GLfloat x;
		GLfloat y;
		GLfloat z;
	} Vector3;

	Vector3 operator+(const Vector3& vec3L, const Vector3& vec3R);
	Vector3& operator+=(Vector3& vec3L, const Vector3& vec3R);
}
