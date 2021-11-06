#pragma once
#include "GameObject.h"

using namespace NaiveEngine;

class CentralBuilding :
    public GameObject
{
public:
    virtual void Draw();
    using GameObject::GameObject;
};

