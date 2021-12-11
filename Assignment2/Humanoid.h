/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#pragma once
#include "GameObject.h"

using namespace LightGameEngine;

enum HandSide
{
    Left = 0,
    Right
};

class LowerArm :
    public GameObject
{
public:
    LowerArm(Vector3 initPos);
    virtual void Draw() override;
};

class UpperArm :
    public GameObject
{
public:
    UpperArm(Vector3 initPos);
    virtual void Draw() override;

    GLfloat GetElbowYaw();
    GLfloat GetElbowPitch();

    void SetElbowYaw(GLfloat yaw);
    void SetElbowPitch(GLfloat pitch);

protected:
    LowerArm* lowerArm;
};

class Humanoid :
    public GameObject
{
public:
    Humanoid(Vector3 initPos);
    virtual void Draw() override;

    GLfloat GetShoulderYaw(HandSide hand);
    void SetShoulderYaw(HandSide hand, GLfloat yaw);

    GLfloat GetShoulderPitch(HandSide hand);
    void SetShoulderPitch(HandSide hand, GLfloat pitch);

    GLfloat GetElbowYaw(HandSide hand);
    void SetElbowYaw(HandSide hand, GLfloat yaw);

    GLfloat GetElbowPitch(HandSide hand);
    void SetElbowPitch(HandSide hand, GLfloat pitch);

protected:
    UpperArm* upperArmL;
    UpperArm* upperArmR;
};
