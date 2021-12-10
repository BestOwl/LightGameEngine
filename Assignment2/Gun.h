#pragma once
#include "GameObject.h"

using namespace LightGameEngine;

class Gun :
    public GameObject
{
    using GameObject::GameObject;
    virtual void Draw() = 0;
};

