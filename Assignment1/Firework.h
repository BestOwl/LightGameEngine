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

typedef ParticleColor FireworkColor;

class Firework :
    public GameObject
{
public:
    Firework(GLfloat x, GLfloat y, FireworkColor fireworkColor, GLint flyHeight = 50);
    virtual void Draw();
    virtual bool Tick();

private:
    GLint flyHeight;
    FireworkColor fireworkColor;

    FireworkState state = Flying;
    GLfloat initalX;
    GLfloat initalY;

    void Explode();
};

