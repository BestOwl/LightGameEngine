/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "Humanoid.h"
#include "Cube.h"
#include "Sphere.h"
#include "TextureStore.h"

using namespace LightGameEngine::GeometricPrimitives;

Humanoid::Humanoid(Vector3 initPos) : GameObject(initPos)
{
	//this->ChildrenObjects.push_back(new Cube(Vector3{ 0, 0, 0 }, 100, L"cube_induction.png"));
	Cube* body = new Cube(Vector3{ 0.f, 0.f, 0.f }, 1, TextureStore::HumanBody);
	body->Scale = Vector3{ 0.5f, 1.f, 0.8f };
	this->ChildrenObjects.push_back(body);

	Sphere* head = new Sphere(Vector3{ 0.f, 0.8f, 0.f }, 0.4f, TextureStore::Head);
	head->Rotation.x = 90;
	head->Rotation.z = 90;
	head->Scale = Vector3{ 0.6f, 0.6f, 1.f };
	this->ChildrenObjects.push_back(head);

	upperArms[static_cast<int>(HandSide::Left)] = new UpperArm(Vector3{ 0.1f, 0.5f, -0.45f });
	upperArms[static_cast<int>(HandSide::Right)] = new UpperArm(Vector3{ 0.1f, 0.5f, 0.45f });
	this->ChildrenObjects.push_back(upperArms[static_cast<int>(HandSide::Left)]);
	this->ChildrenObjects.push_back(upperArms[static_cast<int>(HandSide::Right)]);

	legs[static_cast<int>(HandSide::Left)] = new Leg(Vector3{ 0, -0.7f, -0.3f });
	legs[static_cast<int>(HandSide::Right)] = new Leg(Vector3{ 0, -0.7f, 0.3f });
	this->ChildrenObjects.push_back(legs[static_cast<int>(HandSide::Left)]);
	this->ChildrenObjects.push_back(legs[static_cast<int>(HandSide::Right)]);
}

GLfloat Humanoid::GetShoulderYaw(HandSide hand)
{
	return upperArms[static_cast<int>(hand)]->Rotation.z;
}

void Humanoid::SetShoulderYaw(HandSide hand, GLfloat yaw)
{
	upperArms[static_cast<int>(hand)]->Rotation.z = yaw;
}

GLfloat Humanoid::GetShoulderPitch(HandSide hand)
{
	return upperArms[static_cast<int>(hand)]->Rotation.x;
}

void Humanoid::SetShoulderPitch(HandSide hand, GLfloat pitch)
{
	upperArms[static_cast<int>(hand)]->Rotation.x = pitch;
}

GLfloat Humanoid::GetElbowYaw(HandSide hand)
{
	return upperArms[static_cast<int>(hand)]->GetElbowYaw();
}

void Humanoid::SetElbowYaw(HandSide hand, GLfloat yaw)
{
	upperArms[static_cast<int>(hand)]->SetElbowYaw(yaw);
}

void Humanoid::SetElbowPitch(HandSide hand, GLfloat pitch)
{
	upperArms[static_cast<int>(hand)]->SetElbowPitch(pitch);
}

GLfloat Humanoid::GetLegPitch(HandSide leg)
{
	return legs[static_cast<int>(leg)]->Rotation.z;
}

void Humanoid::SetLegPitch(HandSide leg, GLfloat pitch)
{
	legs[static_cast<int>(leg)]->Rotation.z = pitch;
}

GameObject* Humanoid::GetHoldObject(HandSide hand)
{
	return upperArms[static_cast<int>(hand)]->GetHoldObject();
}

Vector3 Humanoid::GetHandWorldPos(HandSide hand)
{
	if (hand == HandSide::Left)
	{
		return this->GetPos() + upperArms[static_cast<int>(HandSide::Left)]->GetHandWorldPos();
	}
	else
	{
		return this->GetPos() + upperArms[static_cast<int>(HandSide::Right)]->GetHandWorldPos();
	}
}

void Humanoid::SetHoldObject(HandSide hand, GameObject* obj)
{
	upperArms[static_cast<int>(hand)]->SetHoldObject(obj);
}

GLfloat Humanoid::GetElbowPitch(HandSide hand)
{
	return upperArms[static_cast<int>(hand)]->GetElbowYaw();
}

UpperArm::UpperArm(Vector3 initPos) : GameObject(initPos)
{
	Cube* arm = new Cube(Vector3{ 0.f, -0.3125f, 0.f }, 0.5f, TextureStore::UpperArmCube);
	arm->Scale = Vector3{ 0.2f, 1.25f, 0.2f };
	this->ChildrenObjects.push_back(arm);

	lowerArm = new LowerArm({ Vector3{0.f, -0.6f, 0.f} });
	this->ChildrenObjects.push_back(lowerArm);
}

void UpperArm::Draw()
{
}

GLfloat UpperArm::GetElbowYaw()
{
	return this->lowerArm->Rotation.z;
}

GLfloat UpperArm::GetElbowPitch()
{
	return this->lowerArm->Rotation.x;
}

void UpperArm::SetElbowYaw(GLfloat yaw)
{
	this->lowerArm->Rotation.z = yaw;
}

void UpperArm::SetElbowPitch(GLfloat pitch)
{
	this->lowerArm->Rotation.x = pitch;
}

GameObject* UpperArm::GetHoldObject()
{
	return this->lowerArm->GetHoldObject();
}

void UpperArm::SetHoldObject(GameObject* obj)
{
	this->lowerArm->SetHoldObject(obj);
}

Vector3 UpperArm::GetHandWorldPos()
{
	return this->GetPos() + this->lowerArm->GetPos();
}

LowerArm::LowerArm(Vector3 initPos) : GameObject(initPos)
{
	Cube* arm = new Cube(Vector3{ 0.f, -0.25f, 0.f }, 0.5f, TextureStore::SkinCube);
	arm->Scale = Vector3{ 0.2f, 1.25f, 0.2f };
	this->ChildrenObjects.push_back(arm);

	this->hand = new Hand(Vector3{ 0.f, -0.55f, 0.f });
	this->ChildrenObjects.push_back(this->hand);
}

GameObject* LowerArm::GetHoldObject()
{
	return this->hand->GetHoldObject();
}

void LowerArm::SetHoldObject(GameObject* obj)
{
	this->hand->SetHoldObject(obj);
}

Vector3 LowerArm::GetHandWorldPos()
{
	return this->GetPos() + this->hand->GetPos();
}

Hand::Hand(Vector3 initPos) : GameObject(initPos)
{
	Sphere* hand = new Sphere(Vector3{ 0.f, 0.f, 0.f }, 0.05f, TextureStore::Skin);
	this->ChildrenObjects.push_back(hand);
}

GameObject* Hand::GetHoldObject()
{
	return this->holdObject;
}

void Hand::SetHoldObject(GameObject* obj)
{
	if (this->holdObject != nullptr)
	{
		this->ChildrenObjects.erase(std::remove(this->ChildrenObjects.begin(), this->ChildrenObjects.end(), holdObject));
	}
	this->holdObject = obj;
	this->ChildrenObjects.push_back(this->holdObject);
}

Leg::Leg(Vector3 initPos) : GameObject(initPos)
{
	Cube* cube = new Cube(Vector3{0.f, -0.25f, 0.f}, 0.1f, NULL);
	cube->Scale.y = 9.0f;
	this->ChildrenObjects.push_back(cube);
}
