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
        Cylinder(Vector3 initPos, GLfloat radius, GLfloat height, Vector3 axisVector, const std::wstring& texturePath);
        ~Cylinder();
        virtual void Draw() override;

    protected:
        GLfloat radius;
        GLfloat height;
        Vector3 axisVector;

    private:
        Texture* texture;
        Vector3 offset;
    };
}


