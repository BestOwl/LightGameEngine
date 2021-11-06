#pragma once
#include "Player.h"

using namespace NaiveEngine;

class PlayerLiverBird :
    public Player
{
public:
    using Player::Player;
    virtual void Draw();

    virtual void SetX(GLfloat newX);

private:
    char rotateMode = 0;
};

