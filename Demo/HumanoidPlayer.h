#pragma once
#include "PlayerBase.h"
#include "Humanoid.h"
#include "Terrain.h"

using namespace LightGameEngine;

class HumanoidPlayer :
    public PlayerBase
{
public:
    HumanoidPlayer(Vector3 initPos);
    virtual void Draw() override;
    virtual Vector3 GetCameraPos() override;
    virtual void SetPos(Vector3 pos) override;

    virtual void Move(Vector3 direction);
    virtual void SetOnTerrain(Terrain* terrain);

    GameObject* GetHoldObject();
    Vector3 GetHoldObjectWorldPos();
    void SetHoldObject(GameObject* obj);

protected:
    Humanoid* body;
    Terrain* onTerrain;
    GLfloat moveSpeed = 0.5f;

    GLfloat legWalkAngleMax = 25.0f;
    bool legMode = false;

    virtual Vector3 getCameraOffset();
};
