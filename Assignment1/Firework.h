#pragma once
#include "GameObject.h"

using namespace NaiveEngine;

class Firework :
    public GameObject
{
public:
    Firework(GLfloat x, GLfloat y);
    virtual void Draw();
    virtual bool Tick();

private:
    const GLint flyHeight = 200;
    unsigned char state = 0;
    GLfloat initalX;
    GLfloat initalY;
};

