#include "ControlPlayer.h"
#include "Engine.h"
#include "Bullet.h"

#define _USE_MATH_DEFINES
#include <math.h>

ControlPlayer::ControlPlayer(Vector3 initPos) : HumanoidPlayer(initPos)
{

	//this->hasMovementLimit = true;
	this->IsPhysicsEnabled = true;
}

bool ControlPlayer::Tick()
{
	bool dirty = false;
	InputStatus* key = Engine::GetKeyboardStatus();
	//std::cout << key->Forward << "	" << key->Backward << "	" << key->Left << "	" << key->Right << std::endl;

	GLfloat step = 0.5f;

	Vector3 moveVec = { 0, 0, 0 };
	if (key->Forward)
	{
		GLfloat yawInRadians = this->yaw * M_PI / 180;
		moveVec += Vector3{ cosf(yawInRadians) * step, 0, sinf(yawInRadians) * step };
		dirty = true;
	}
	if (key->Backward)
	{
		GLfloat yawInRadians = this->yaw * M_PI / 180;
		moveVec += Vector3{ -cosf(yawInRadians) * step, 0, -sinf(yawInRadians) * step };
		dirty = true;
	}
	if (key->Left)
	{
		GLfloat yawInRadians = (this->yaw - 90) * M_PI / 180;
		moveVec += Vector3{ cosf(yawInRadians) * step, 0, sinf(yawInRadians) * step };
		dirty = true;
	}
	if (key->Right)
	{
		GLfloat yawInRadians = (this->yaw + 90) * M_PI / 180;
		moveVec += Vector3{ cosf(yawInRadians) * step, 0, sinf(yawInRadians) * step };
		dirty = true;
	}
	if (key->Space)
	{
		//printf_s("Y speed: %f", this->Speed.y);
  		if (this->Speed.y == 0)
		{
			
		}
		moveVec += Vector3{ 0, 1, 0 };
		dirty = true;
	}

	if (key->MouseLeftBtn)
	{
		bool fireSuccessful = this->GetHoldGun()->Fire();
		if (fireSuccessful)
		{
			Engine::AddSceneObject(new Bullet(this->GetPos(), this->GetLookAtVector()));
		}
	}
	if (key->MouseRightBtn)
	{
		this->rmbPressed = true;
	}
	else
	{
		if (this->rmbPressed)
		{
			this->scopeOpend = !this->scopeOpend;
		}
		this->rmbPressed = false;
	}

	if (key->R)
	{
		this->GetHoldGun()->ReloadAmmo();
	}

	if (dirty)
	{
		this->Move(moveVec);
	}

	return HumanoidPlayer::Tick() || dirty;
}

Gun* ControlPlayer::GetHoldGun()
{
	return (Gun*) this->GetHoldObject();
}

Vector3 ControlPlayer::getCameraOffset()
{
	if (this->scopeOpend)
	{
		return Vector3{ 0.45f, 0.6f, 0.35f };
	}
	else
	{
		return HumanoidPlayer::getCameraOffset();
	}
}



