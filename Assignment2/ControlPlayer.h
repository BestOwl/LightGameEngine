#pragma once
#include "HumanoidPlayer.h"

using namespace LightGameEngine;

class ControlPlayer :
    public HumanoidPlayer
{
public:
    ControlPlayer(Vector3 initPos);
    virtual bool Tick() override;
    

protected:
    
};

