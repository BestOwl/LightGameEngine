#pragma once
#include "GameObject.h"

using namespace NaiveEngine;

class Cloud :
    public GameObject
{
public:
    using GameObject::GameObject;
    virtual void Draw();
};

