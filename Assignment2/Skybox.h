/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once
#include "GameObject.h"
#include "Cube.h"

using namespace LightGameEngine;
using namespace LightGameEngine::GeometricPrimitives;

class Skybox :
    public Cube
{
public:
    Skybox(Vector3 initPos);
};

