/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#include "Player.h"
#include "Engine.h"

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

void LightGameEngine::Player::Draw()
{
	glColor3ub(0, 255, 0);
	glutSolidCube(1);
}

bool LightGameEngine::Player::Tick()
{
	bool dirty = false;
	KeyboardStatus* key = Engine::GetKeyboardStatus();
	//std::cout << key->Forward << "	" << key->Backward << "	" << key->Left << "	" << key->Right << std::endl;

	int step = 5;

	Vector3 moveVec = { 0, 0, 0 };
	if (key->Forward)
	{
		GLfloat yawInRadians = this->yaw * M_PI / 180;
		moveVec += Vector3{ cos(yawInRadians) * step, 0, sin(yawInRadians) * step };
		dirty = true;
	}
	if (key->Backward)
	{
		GLfloat yawInRadians = this->yaw * M_PI / 180;
		moveVec += Vector3{ -cos(yawInRadians) * step, 0, -sin(yawInRadians) * step };
		dirty = true;
	}
	if (key->Left)
	{
		GLfloat yawInRadians = (this->yaw - 90) * M_PI / 180;
		moveVec += Vector3{ cos(yawInRadians) * step, 0, sin(yawInRadians) * step };
		dirty = true;
	}
	if (key->Right)
	{
		GLfloat yawInRadians = (this->yaw + 90) * M_PI / 180;
		moveVec += Vector3{ cos(yawInRadians) * step, 0, sin(yawInRadians) * step };
		dirty = true;
	}

	if (dirty)
	{
		this->SetPos(this->GetPos() + moveVec);
	}

	return dirty;
}

void LightGameEngine::Player::SetPos(Vector3 pos)
{
	if (this->hasMovementLimit)
	{
		pos.x = std::min(pos.x, this->posMax.x);
		pos.x = std::max(pos.x, this->posMin.x);

		pos.y = std::min(pos.y, this->posMax.y);
		pos.y = std::max(pos.y, this->posMin.y);

		pos.z = std::min(pos.z, this->posMax.z);
		pos.z = std::max(pos.z, this->posMin.z);
	}
	GameObject::SetPos(pos);
}

LightGameEngine::Vector3 LightGameEngine::Player::GetCameraPos()
{
	Vector3 cameraPos = this->pos;
	cameraPos.y += 10;
	return cameraPos;
}

LightGameEngine::Vector3 LightGameEngine::Player::GetLookAtRef()
{
	Vector3 ref = this->GetCameraPos();
	float yawAngle = this->yaw * M_PI / 180.0;
	ref.x += 1 * cos(yawAngle);
	ref.z += 1 * sin(yawAngle);
	
	ref.y += 1 * sin(this->pitch * M_PI / 180.0);

	//std::cout << "yaw: " << this->yaw << std::endl;

	return ref;
}

void LightGameEngine::Player::AddYaw(GLfloat degree)
{
	this->yaw += degree;
	if (this->yaw > this->yawMax)
	{
		this->yaw = 0 + (this->yaw - this->yawMax);
	}
	else if (this->yaw < this->yawMin)
	{
		this->yaw = this->yawMax - (0 - this->yaw);
	}
}

void LightGameEngine::Player::AddPitch(GLfloat degree)
{
	this->pitch += degree;
	if (this->pitch > this->pitchMax)
	{
		this->pitch = pitchMax;
	}
	else if (this->pitch < this->pitchMin)
	{
		this->pitch = pitchMin;
	}
}

GLfloat LightGameEngine::Player::GetYaw()
{
	return this->yaw;
}

GLfloat LightGameEngine::Player::GetPitch()
{
	return this->pitch;
}

