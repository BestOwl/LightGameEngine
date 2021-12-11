#pragma once
#include "PlayerBase.h"
#include "Humanoid.h"

using namespace LightGameEngine;

class HumanoidPlayer :
    public PlayerBase
{
public:
    HumanoidPlayer(Vector3 initPos);
    virtual void Draw() override;
    virtual Vector3 GetCameraPos() override;


protected:
    Humanoid* body;
};

