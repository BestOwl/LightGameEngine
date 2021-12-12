#include "HumanoidPlayer.h"
#include "GunAK47.h"

#define _USE_MATH_DEFINES
#include <math.h>

HumanoidPlayer::HumanoidPlayer(Vector3 initPos) : PlayerBase(initPos)
{
	body = new Humanoid(Vector3{ 0, 0, 0 });
	this->ChildrenObjects.push_back(body);

	body->SetShoulderYaw(HandSide::Left, 52.f);
	body->SetShoulderPitch(HandSide::Left, -50.f);
	body->SetElbowPitch(HandSide::Left, -50.f);

	body->SetShoulderYaw(HandSide::Right, 40.f);
	body->SetShoulderPitch(HandSide::Right, -10.f);
	body->SetElbowYaw(HandSide::Right, 110.f);

	GunAK47* gunAk = new GunAK47(Vector3{ 0,0, -0.1f });
	gunAk->Rotation.z = -145.f;
	gunAk->Rotation.x = -10.f;
	gunAk->Rotation.y = -10.f;
	body->SetHoldObject(HandSide::Right, gunAk);

	this->onTerrain = nullptr;

	this->pitchMax = 70;
}

void HumanoidPlayer::Draw()
{
	body->Rotation.y = -this->GetYaw();
}

Vector3 HumanoidPlayer::GetCameraPos()
{
	const Vector2 cameraOffset = { 0.3f, 0.f }; // offset in x and z axis
	const GLfloat offsetNorm = sqrtf(cameraOffset.x * cameraOffset.x + cameraOffset.y * cameraOffset.y);

	GLfloat yawInRadian = this->GetYaw() * M_PI / 180;
	return this->GetPos() + Vector3{ offsetNorm * cosf(yawInRadian), 0.65f, offsetNorm * sinf(yawInRadian)};
}

void HumanoidPlayer::SetOnTerrain(Terrain* terrain)
{
	if (terrain == nullptr)
	{
		this->hasMovementLimit = false;
	}
	else
	{
		this->hasMovementLimit = true;
		terrain->GetTerrainBound(&this->posMin, &this->posMax);
	}

	this->onTerrain = terrain;
}

GameObject* HumanoidPlayer::GetHoldObject()
{
	return this->body->GetHoldObject(HandSide::Right);
}

void HumanoidPlayer::SetHoldObject(GameObject* obj)
{
	this->body->SetHoldObject(HandSide::Right, obj);
}
