#pragma once
#include "GameObject.h"

using namespace NaiveEngine;

class Balloon :
    public GameObject
{
public:
    virtual void Draw();
    virtual bool Tick();
    using GameObject::GameObject;
};

