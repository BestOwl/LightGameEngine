/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#include "CollisionEngine.h"

using namespace LightGameEngine;

CollisionEngine* CollisionEngine::_collisionEngine;

std::vector<AABBox*> CollisionEngine::HitTest(AABBox* aabb)
{
    std::vector<AABBox*> aabbes;
    auto i_aabb = std::begin(this->AabbBoxes);
    while (i_aabb != std::end(this->AabbBoxes))
    {
        AABBox* p_Aabb = (*i_aabb);
        if (p_Aabb->ToBeDestoryed)
        {
            i_aabb = this->AabbBoxes.erase(i_aabb);
            delete p_Aabb;
        }
        else
        {
            if (aabb != p_Aabb)
            {
                if (this->hitTest(aabb, p_Aabb))
                {
                    aabbes.push_back(p_Aabb);
                }
            }

            ++i_aabb;
        }
    }
    return aabbes;
}

bool CollisionEngine::hitTest(AABBox* a, AABBox* b)
{
    GLfloat xOverlap = axisOverlap(a->MaxPos.x, a->MinPos.x, b->MaxPos.x, b->MinPos.x);
    GLfloat yOverlap = axisOverlap(a->MaxPos.y, a->MinPos.y, b->MaxPos.y, b->MinPos.y);
    GLfloat zOverlap = axisOverlap(a->MaxPos.z, a->MinPos.z, b->MaxPos.z, b->MinPos.z);

    const GLfloat threshold = 0.2f;
    return xOverlap > threshold && yOverlap > threshold && zOverlap > threshold;
}

GLfloat CollisionEngine::axisOverlap(GLfloat amax, GLfloat amin, GLfloat bmax, GLfloat bmin)
{
    GLfloat minMax = 0;
    GLfloat maxMin = 0;
    if (amax < bmax)
    {
        minMax = amax;
        maxMin = bmin;
    }
    else
    {
        minMax = bmax;
        maxMin = amin;
    }

    if (minMax > maxMin)
    {
        return minMax - maxMin;
    }
    else
    {
        return 0.f;
    }
}

CollisionEngine* LightGameEngine::CollisionEngine::GetInstance()
{
    if (_collisionEngine == nullptr)
    {
        _collisionEngine = new CollisionEngine();
    }
    return _collisionEngine;
}