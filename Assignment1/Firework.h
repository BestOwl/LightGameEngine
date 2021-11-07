#pragma once
#include "GameObject.h"
#include "Particle.h"

using namespace NaiveEngine;

enum FireworkState
{
    Flying,
    Explode,
    Drop
};

class Firework :
    public GameObject
{
public:
    Firework(GLfloat x, GLfloat y);
    virtual void Draw();
    virtual bool Tick();

private:
    const GLint flyHeight = 50;
    FireworkState state = Flying;
    GLfloat initalX;
    GLfloat initalY;

    void Explode();
};

