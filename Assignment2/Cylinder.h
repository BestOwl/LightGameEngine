#pragma once
#include "GameObject.h"

#include <string>

using namespace LightGameEngine;

namespace LightGameEngine::GeometricPrimitives
{
    class Cylinder :
        public GameObject
    {
    public:
        Cylinder(Vector3 initPos, GLfloat radius, GLfloat height, const std::wstring& texturePath);
        virtual void Draw() override;
    };
}


