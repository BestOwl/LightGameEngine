#include "ControlPlayer.h"
#include "Engine.h"

#define _USE_MATH_DEFINES
#include <math.h>

ControlPlayer::ControlPlayer(Vector3 initPos) : HumanoidPlayer(initPos)
{

}

bool ControlPlayer::Tick()
{
	bool dirty = false;
	KeyboardStatus* key = Engine::GetKeyboardStatus();
	//std::cout << key->Forward << "	" << key->Backward << "	" << key->Left << "	" << key->Right << std::endl;

	GLfloat step = 0.05f;

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

	if (dirty)
	{
		this->SetPos(this->GetPos() + moveVec);
	}

	return dirty;
}



