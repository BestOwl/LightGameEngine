/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#include "GameObject.h"

using namespace LightGameEngine;

Vector3 LightGameEngine::GameObject::GetPos()
{
	return this->pos;
}

void LightGameEngine::GameObject::SetPos(Vector3 pos)
{
	this->pos = pos;
}

Vector3 LightGameEngine::GameObject::GetActualAcceleration()
{
	return 
	{
		this->Acceleration.x - this->Speed.x * 0.1f,
		this->Acceleration.y - this->Speed.y * 0.1f - this->Gravity, // origin AccelerateY - air drag - gravity
		this->Acceleration.z - this->Speed.z * 0.1f
	};
}

void LightGameEngine::GameObject::Draw()
{
}

bool GameObject::Tick()
{
	if (this->IsPhysicsEnabled)
	{
		Vector3 accr = this->GetActualAcceleration();

		this->Speed.x += accr.x;
		this->Speed.y += accr.y;
		this->Speed.z += accr.z;

		if (abs(this->Speed.x) < 0.0001)
		{
			this->Speed.x = 0;
		}
		if (abs(this->Speed.y) < 0.0001)
		{
			this->Speed.y = 0;
		}
		if (abs(this->Speed.z) < 0.0001)
		{
			this->Speed.z = 0;
		}

		bool dirty = false;
		Vector3 newPos = this->pos;
		if (this->Speed.x != 0)
		{
			newPos.x += this->Speed.x;
			dirty = true;
		}
		if (this->Speed.y != 0)
		{
			newPos.y += this->Speed.y;
			dirty = true;
		}
		if (this->Speed.z != 0)
		{
			newPos.z += this->Speed.z;
			dirty = true;
		}

		if (dirty)
		{
			this->SetPos(newPos);
			return true;
		}
	}

	return false;
}

GameObject::GameObject(Vector3 initPos)
{
	this->pos = initPos;
	this->ChildrenObjects = std::vector<GameObject*>();
}

GameObject::~GameObject()
{
	for (GameObject* childrenObj : this->ChildrenObjects)
	{
		if (childrenObj)
		{
			delete childrenObj;
		}
	}
}
