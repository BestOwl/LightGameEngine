/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#pragma once
#include "GameObject.h"
#include "Texture.h"

#include <string>

using namespace LightGameEngine;

namespace LightGameEngine::GeometricPrimitives
{
    class Cylinder :
        public GameObject
    {
    public:
        Cylinder(Vector3 initPos, GLfloat radius, GLfloat height, Vector3 axisVector, Texture* texture = NULL);
        virtual void Draw() override;

    protected:
        GLfloat radius;
        GLfloat height;
        Vector3 axisVector;
        Texture* texture;

    private:
        Vector3 offset;
    };
}


