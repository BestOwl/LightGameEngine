#pragma once
#include "Gun.h"

class GunAK47 :
    public Gun
{
public:
    GunAK47(Vector3 initPos);
    virtual void Draw() override;
};

class MagAK47 :
    public GameObject
{
    using GameObject::GameObject;
    virtual void Draw() override;
};
