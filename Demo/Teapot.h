#pragma once
#include "GameObject.h"

using namespace LightGameEngine;

class Teapot :
    public GameObject
{
    using GameObject::GameObject;
    virtual void Draw();
};

