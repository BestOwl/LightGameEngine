/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#include "Skybox.h"

using namespace LightGameEngine;
using namespace LightGameEngine::GeometricPrimitives;

const GLuint boxLength = 5000; 

Skybox::Skybox(Vector3 initPos) : Cube(initPos, boxLength, L"skybox.jpg")
{
}

