#pragma once
#include "GameObject.h"

using namespace NaiveEngine;

class Balloon :
    public GameObject
{
public:
    Balloon(GLfloat x, GLfloat y);

    virtual void Draw();
    virtual bool Tick();
    
};

