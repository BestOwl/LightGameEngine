#include "BotPlayer.h"
#include "Bullet.h"

#define _USE_MATH_DEFINES
#include <math.h>

BotPlayer::BotPlayer(Vector3 initPos, ControlPlayer* mainPlayer, std::function<void()> killedCallback) : HumanoidPlayer(initPos)
{
    this->moveSpeed = 0.2f;
    this->IsPhysicsEnabled = true;
    this->killedCallback = killedCallback;
    this->mainPlayer = mainPlayer;
}

bool BotPlayer::Tick()
{
    Vector3 v = mainPlayer->GetPos() - this->GetPos();
    this->Move(v);

    return HumanoidPlayer::Tick() || true;
}

void BotPlayer::OnHit(GameObject* hitBy)
{
    Bullet* bullet = dynamic_cast<Bullet*>(hitBy);
    if (bullet != nullptr)
    {
        if (this->killedCallback)
        {
            this->killedCallback();
        }
        this->IsDestroyed = true;
    }
}

void BotPlayer::Move(Vector3 direction)
{
    HumanoidPlayer::Move(direction);
    if (direction.x == 0)
    {
        this->yaw = 0;
    }
    else
    {
        this->yaw = atanf(direction.z / direction.x) * 180.f / M_PI;
        if (direction.x < 0)
        {
            this->yaw = this->wrapYaw(this->yaw + 180);
        }
    }
}
