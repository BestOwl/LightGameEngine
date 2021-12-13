#pragma once
#include "GameObject.h"

using namespace LightGameEngine;

class Gun :
    public GameObject
{
public:
    Gun(Vector3 initPos, GLuint magCapacity);
    virtual void Draw() = 0;

    virtual GLuint GetAmmoCapacity();
    virtual GLuint GetCurrentAmmo();

    virtual void ReloadAmmo();
    virtual void Fire(Vector3 direction);

protected:
    GLuint magAmmoCapacity;
    GLuint magAmmo;

};

