#pragma once
#include "Cube.h"

using namespace LightGameEngine;
using namespace LightGameEngine::GeometricPrimitives;

class Bullet :
    public Cube
{
public:
    Bullet(Vector3 initPos, Vector3 direction);
    virtual bool Tick() override;
    
    Vector3 Direction;
    GLuint FlyTime;

protected:
    GLuint currentFlyTime;
    
};

