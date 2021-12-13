#pragma once
#include "HumanoidPlayer.h"
#include "Gun.h"

using namespace LightGameEngine;

class ControlPlayer :
    public HumanoidPlayer
{
public:
    ControlPlayer(Vector3 initPos);
    virtual bool Tick() override;
    
    Gun* GetHoldGun();


protected:
    bool scopeOpend = false;
    bool rmbPressed = false;

    virtual Vector3 getCameraOffset() override;
};

