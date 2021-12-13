#include "BotPlayer.h"

BotPlayer::BotPlayer(Vector3 initPos) : HumanoidPlayer(initPos)
{
    this->moveSpeed = 0.05f;
    this->IsPhysicsEnabled = true;
}

bool BotPlayer::Tick()
{
    this->Move(Vector3{ 1, 0, 0 });
    return HumanoidPlayer::Tick() || true;
}
