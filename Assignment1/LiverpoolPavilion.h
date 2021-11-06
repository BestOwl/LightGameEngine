#pragma once
#include "GameObject.h"

using namespace NaiveEngine;

class LiverpoolPavilion :
    public GameObject
{
public:
    virtual void Draw();
    using GameObject::GameObject;
};

