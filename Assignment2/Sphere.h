/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#pragma once
#include "GameObject.h"
#include "Texture.h"

using namespace LightGameEngine;

namespace LightGameEngine::GeometricPrimitives
{
    class Sphere :
        public GameObject
    {
    public:
        Sphere(Vector3 initPos, GLfloat radius, Texture* texture = NULL);
        virtual void Draw() override;

    protected:
        GLfloat radius;
        Texture* texture;
    };
}
