/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once
#include "GameObject.h"
#include "Texture.h"

using namespace LightGameEngine;

class Skybox :
    public GameObject
{
public:
    Skybox(Vector3 initPos);
    ~Skybox();
    virtual void Draw() override;

private:
    Texture* front;
    Texture* back;
    Texture* left;
    Texture* right;
    Texture* top;
    Texture* bottom;
};

