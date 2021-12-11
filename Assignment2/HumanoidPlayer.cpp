#include "HumanoidPlayer.h"

HumanoidPlayer::HumanoidPlayer(Vector3 initPos) : PlayerBase(initPos)
{
	body = new Humanoid(Vector3{ 0, 0, 0 });
	this->ChildrenObjects.push_back(body);

	/*body->SetShoulderYaw(HandSide::Left, 90);
	body->SetShoulderPitch(HandSide::Left, -45);
	body->SetElbowPitch(HandSide::Left, -45);
	body->SetElbowYaw(HandSide::Left, 45);*/
	body->SetShoulderYaw(HandSide::Left, 100.f);
	body->SetShoulderPitch(HandSide::Left, -90.f);
}

void HumanoidPlayer::Draw()
{
}

Vector3 HumanoidPlayer::GetCameraPos()
{
	return this->GetPos() + Vector3{ 0.5f, 0.75f, 0.f };
}
