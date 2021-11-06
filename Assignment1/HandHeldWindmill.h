#pragma once
#include "GameObject.h"

using namespace NaiveEngine;

class HandHeldWindmill :
    public GameObject
{
public:
    using GameObject::GameObject;
    virtual void Draw();
    virtual bool Tick();

private:
    unsigned short rotate = 0;

};

