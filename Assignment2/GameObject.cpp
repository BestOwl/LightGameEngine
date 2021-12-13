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
	if (this->aabb != nullptr)
	{
		Vector3 pos = this->GetPos();
		this->aabb->MinPos = pos + this->relativeAabb->MinPos;
		this->aabb->MaxPos = pos + this->relativeAabb->MaxPos;
	}
}

void LightGameEngine::GameObject::SetAABbox(AABBox box)
{
	if (this->relativeAabb)
	{
		relativeAabb->MinPos = box.MinPos;
		relativeAabb->MaxPos = box.MaxPos;
		aabb->MinPos = this->GetPos() + box.MinPos;
		aabb->MaxPos = this->GetPos() + box.MaxPos;
	}
	else
	{
		relativeAabb = new AABBox(box.MinPos, box.MaxPos);
		aabb = new AABBox(this->GetPos() + box.MinPos, this->GetPos() + box.MaxPos);
		CollisionEngine::GetInstance()->AabbBoxes.push_back(aabb);
	}
}

AABBox* LightGameEngine::GameObject::GetAABbox()
{
	return this->aabb;
}

void LightGameEngine::GameObject::OnHit(GameObject* hitBy)
{
}

Vector3 LightGameEngine::GameObject::GetActualAcceleration()
{
	return 
	{
		this->Acceleration.x - this->Speed.x * this->AirDrag,
		this->Acceleration.y - this->Speed.y * this->AirDrag - this->Gravity, // origin AccelerateY - air drag - gravity
		this->Acceleration.z - this->Speed.z * this->AirDrag
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
		this->Speed += accr;

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
		Vector3 newPos = this->GetPos();
		if (!(this->Speed == Vector3{ 0, 0, 0 }))
		{
			newPos += this->Speed;

			if (this->aabb != nullptr)
			{
				AABBox* aabb = CollisionEngine::GetInstance()->HitTest(this->aabb);
				if (aabb != nullptr)
				{
					printf_s("Hit!\n");
				}
			}

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

	if (this->aabb)
	{
		this->aabb->ToBeDestoryed = true;
	}
	if (this->relativeAabb)
	{
		delete relativeAabb;
	}
}
