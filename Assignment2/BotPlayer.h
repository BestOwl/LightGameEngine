#pragma once
#include "HumanoidPlayer.h"
class BotPlayer :
    public HumanoidPlayer
{
public:
    BotPlayer(Vector3 initPos);
    virtual bool Tick() override;
};

