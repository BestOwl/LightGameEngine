#pragma once
#include "HumanoidPlayer.h"
#include "ControlPlayer.h"

#include <functional>

class BotPlayer :
    public HumanoidPlayer
{
public:
    BotPlayer(Vector3 initPos, ControlPlayer* mainPlayer, std::function<void()> killedCallback);
    virtual bool Tick() override;
    virtual void OnHit(GameObject* hitBy) override;
    virtual void Move(Vector3 direction) override;

protected:
    std::function<void()> killedCallback;
    ControlPlayer* mainPlayer;
};

