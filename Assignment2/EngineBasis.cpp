/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "EngineBasis.h"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace LightGameEngine;

Vector3 LightGameEngine::operator+(const Vector3& vec3L, const Vector3& vec3R)
{
	return { vec3L.x + vec3R.x, vec3L.y + vec3R.y, vec3L.z + vec3R.z };
}

Vector3& LightGameEngine::operator+=(Vector3& vec3L, const Vector3& vec3R)
{
	vec3L.x += vec3R.x;
	vec3L.y += vec3R.y;
	vec3L.z += vec3R.z;
	return vec3L;
}

Vector3 LightGameEngine::operator-(const Vector3& vec3L, const Vector3& vec3R)
{
	return Vector3{ vec3L.x - vec3R.x, vec3L.y - vec3R.y, vec3L.z - vec3R.z };
}

Vector3 LightGameEngine::operator*(GLfloat scale, const Vector3& vec3)
{
	return Vector3
	{
		scale * vec3.x,
		scale * vec3.y,
		scale * vec3.z,
	};
}

bool LightGameEngine::operator==(const Vector3& vec3L, const Vector3& vec3R)
{
	return vec3L.x == vec3R.x && vec3L.y == vec3R.y && vec3L.z == vec3R.z;
}

void Vector3_struct::ScaleTo(GLfloat norm)
{
	GLfloat originNorm = this->GetNorm();
	GLfloat scale = norm / originNorm;

	this->x = this->x * scale;
	this->y = this->y * scale;
	this->z = this->z * scale;
}

Vector3_struct LightGameEngine::Vector3_struct::Scale(GLfloat norm)
{
	GLfloat scale = norm / this->GetNorm();
	return Vector3_struct{ this->x * scale, this->y * scale, this->z * scale };
}

Vector3_struct LightGameEngine::Vector3_struct::CrossProduct(Vector3_struct vec3R)
{
	return Vector3_struct
	{
		this->y * vec3R.z - this->z * vec3R.y,
		-(this->x * vec3R.z - this->z * vec3R.x),
		this->x * vec3R.y - this->y * vec3R.x
	};
}

GLfloat Vector3_struct::GetNorm()
{
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3 LightGameEngine::EngineBasis::GetVectorFromYawAndPitch(GLfloat yaw, GLfloat pitch)
{
	float yawInRadian = yaw * M_PI / 180.0;
	float pitchInRadian = pitch * M_PI / 180.0;
	return Vector3
	{
		1.f * cosf(pitchInRadian) * cosf(yawInRadian),  //x
		1.f * sinf(pitchInRadian),						//y
		1.f * cosf(pitchInRadian) * sinf(yawInRadian)   //z
	};
}
