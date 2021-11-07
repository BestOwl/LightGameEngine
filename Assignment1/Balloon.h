#pragma once
#include "GameObject.h"
#include "NaiveEngineUtil.h"

using namespace NaiveEngine;

typedef Color BalloonColor;

class Balloon :
    public GameObject
{
public:
    Balloon(GLfloat x, GLfloat y, BalloonColor color);

    virtual void Draw();
    virtual bool Tick();

private:
    BalloonColor color;
};

