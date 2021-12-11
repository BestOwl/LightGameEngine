/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "Humanoid.h"
#include "Cube.h"
#include "Sphere.h"

#include <GL/freeglut.h>

using namespace LightGameEngine::GeometricPrimitives;

Humanoid::Humanoid(Vector3 initPos) : GameObject(initPos)
{
	//this->ChildrenObjects.push_back(new Cube(Vector3{ 0, 0, 0 }, 100, L"cube_induction.png"));
	Cube* body = new Cube(Vector3{ 0.f, 0.f, 0.f }, 1, NULL);
	body->Scale = Vector3{ 0.5f, 1.f, 0.8f };
	this->ChildrenObjects.push_back(body);

	Sphere* head = new Sphere(Vector3{ 0.f, 0.8f, 0.f }, 0.4f);
	head->Scale = Vector3{ 0.8f, 1.f, 0.8f };
	this->ChildrenObjects.push_back(head);

	this->upperArmL = new UpperArm(Vector3{ 0.1f, 0.5f, 0.45f });
	this->ChildrenObjects.push_back(this->upperArmL);

	this->upperArmR = new UpperArm(Vector3{ 0.1f, 0.5f, -0.45f });
	this->ChildrenObjects.push_back(this->upperArmR);
}

void Humanoid::Draw()
{
}

GLfloat Humanoid::GetShoulderYaw(HandSide hand)
{
	return this->upperArmL->Rotation.z;
}

void Humanoid::SetShoulderYaw(HandSide hand, GLfloat yaw)
{
	this->upperArmL->Rotation.z = yaw;
}

GLfloat Humanoid::GetShoulderPitch(HandSide hand)
{
	return this->upperArmL->Rotation.x;
}

void Humanoid::SetShoulderPitch(HandSide hand, GLfloat pitch)
{
	this->upperArmL->Rotation.x = pitch;
}

GLfloat Humanoid::GetElbowYaw(HandSide hand)
{
	return this->upperArmL->GetElbowYaw();
}

void Humanoid::SetElbowYaw(HandSide hand, GLfloat yaw)
{
	this->upperArmL->SetElbowYaw(yaw);
}

void Humanoid::SetElbowPitch(HandSide hand, GLfloat pitch)
{
	this->upperArmL->SetElbowPitch(pitch);
}

GLfloat Humanoid::GetElbowPitch(HandSide hand)
{
	return this->upperArmL->GetElbowYaw();
}

UpperArm::UpperArm(Vector3 initPos) : GameObject(initPos)
{
	Cube* arm = new Cube(Vector3{ 0.f, -0.3125f, 0.f }, 0.5f, NULL);
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

LowerArm::LowerArm(Vector3 initPos) : GameObject(initPos)
{
	Cube* arm = new Cube(Vector3{ 0.f, -0.25f, 0.f }, 0.5f, NULL);
	arm->Scale = Vector3{ 0.2f, 1.25f, 0.2f };
	this->ChildrenObjects.push_back(arm);

	Sphere* hand = new Sphere(Vector3{ 0.f, -0.55f, 0.f }, 0.05f);
	this->ChildrenObjects.push_back(hand);
}

void LowerArm::Draw()
{
}
