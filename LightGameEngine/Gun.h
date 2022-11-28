#pragma once
#include "GameObject.h"

using namespace LightGameEngine;

class Gun :
    public GameObject
{
public:
    Gun(Vector3 initPos, GLuint magCapacity);
    virtual void Draw() = 0;
    virtual bool Tick() override;

    virtual GLuint GetAmmoCapacity();
    virtual GLuint GetCurrentAmmo();

    virtual void ReloadAmmo();
    virtual bool Fire();

protected:
    GLuint magAmmoCapacity;
    GLuint magAmmo;
    GLuint coolingTime = 8;
    GLuint cooling = 0;

};

