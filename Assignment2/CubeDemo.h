/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once
#include "GameObject.h"

using namespace LightGameEngine;

class CubeDemo :
    public GameObject
{

public:
    CubeDemo(Vector3 initPos);
    virtual void Draw();

private:
    static GLubyte* textureImage;
    static GLint textureImageWidth;
    static GLint textureImageHeight;
};
