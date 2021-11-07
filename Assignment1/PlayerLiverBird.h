#pragma once
#include "Player.h"

using namespace NaiveEngine;

class PlayerLiverBird :
    public Player
{
public:
    PlayerLiverBird(GLfloat x, GLfloat y);
    virtual void Draw();
    virtual bool Tick();

    virtual void SetX(GLfloat newX);

private:
    char rotateMode = 0;
    GLfloat windDegree = 0;
};

