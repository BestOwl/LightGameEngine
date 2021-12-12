/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once

#include <GL/glew.h>
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

	struct Vector2_struct
	{
		GLfloat x;
		GLfloat y;
	};
	typedef Vector2_struct Vector2;

	struct Vector3_struct  
	{
		GLfloat x;
		GLfloat y;
		GLfloat z;
	public:
		GLfloat GetNorm();
		void ScaleTo(GLfloat norm);
		Vector3_struct Scale(GLfloat norm);
		Vector3_struct CrossProduct(Vector3_struct vec3R);
	};
	typedef Vector3_struct Vector3;
	

	Vector3 operator+(const Vector3& vec3L, const Vector3& vec3R);
	Vector3& operator+=(Vector3& vec3L, const Vector3& vec3R);

	Vector3 operator-(const Vector3& vec3L, const Vector3& vec3R);

	Vector3 operator*(GLfloat scale, const Vector3& vec3);

	bool operator==(const Vector3& vec3L, const Vector3& vec3R);

	class EngineBasis
	{
	public:
		static Vector3 GetVectorFromYawAndPitch(GLfloat yaw, GLfloat pitch);
	};
}
