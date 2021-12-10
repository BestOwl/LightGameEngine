/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#include "PlayerBase.h"
#include "Engine.h"

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace LightGameEngine;

void PlayerBase::Draw()
{
	glColor3ub(0, 255, 0);
	glutSolidCube(1);
}

bool PlayerBase::Tick()
{
	bool dirty = false;
	KeyboardStatus* key = Engine::GetKeyboardStatus();
	//std::cout << key->Forward << "	" << key->Backward << "	" << key->Left << "	" << key->Right << std::endl;

	GLfloat step = 0.05f;

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

void PlayerBase::SetPos(Vector3 pos)
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

Vector3 PlayerBase::GetCameraPos()
{
	Vector3 cameraPos = this->pos;
	cameraPos.y += 10;
	return cameraPos;
}

Vector3 PlayerBase::GetLookAtVector()
{
	return EngineBasis::GetVectorFromYawAndPitch(this->yaw, this->pitch);
}

Vector3 PlayerBase::GetUpVector()
{
	return EngineBasis::GetVectorFromYawAndPitch(this->GetUpVectorYaw(), this->GetUpVectorPitch());
}

void PlayerBase::AddYaw(GLfloat degree)
{
	this->yaw = this->wrapYaw(this->yaw + degree);
}

void PlayerBase::AddPitch(GLfloat degree)
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

GLfloat PlayerBase::GetYaw()
{
	return this->yaw;
}

GLfloat PlayerBase::GetPitch()
{
	return this->pitch;
}

GLfloat LightGameEngine::PlayerBase::GetUpVectorYaw()
{
	return this->wrapYaw(this->yaw + 180);
}

GLfloat LightGameEngine::PlayerBase::GetUpVectorPitch()
{
	return 90 - this->pitch;
}

GLfloat PlayerBase::wrapYaw(GLfloat yaw)
{
	if (yaw > this->yawMax)
	{
		yaw = 0 + (yaw - this->yawMax);
	}
	else if (yaw < this->yawMin)
	{
		yaw = this->yawMax - (0 - yaw);
	}
	return yaw;
}

