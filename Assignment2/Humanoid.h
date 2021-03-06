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

enum class HandSide
{
    Left = 0,
    Right = 1
};

class Hand :
    public GameObject
{
public:
    Hand(Vector3 initPos);

    GameObject* GetHoldObject();
    void SetHoldObject(GameObject* obj);

private:
    GameObject* holdObject = nullptr;
};

class LowerArm :
    public GameObject
{
public:
    LowerArm(Vector3 initPos);

    GameObject* GetHoldObject();
    void SetHoldObject(GameObject* obj);
    Vector3 GetHandWorldPos();

private:
    Hand* hand;
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

    GameObject* GetHoldObject();
    void SetHoldObject(GameObject* obj);
    Vector3 GetHandWorldPos();

protected:
    LowerArm* lowerArm;
};

class Leg :
    public GameObject
{
public:
    Leg(Vector3 initPos);
};

class Humanoid :
    public GameObject
{
public:
    Humanoid(Vector3 initPos);

    GLfloat GetShoulderYaw(HandSide hand);
    void SetShoulderYaw(HandSide hand, GLfloat yaw);

    GLfloat GetShoulderPitch(HandSide hand);
    void SetShoulderPitch(HandSide hand, GLfloat pitch);

    GLfloat GetElbowYaw(HandSide hand);
    void SetElbowYaw(HandSide hand, GLfloat yaw);

    GLfloat GetElbowPitch(HandSide hand);
    void SetElbowPitch(HandSide hand, GLfloat pitch);

    GLfloat GetLegPitch(HandSide leg);
    void SetLegPitch(HandSide leg, GLfloat pitch);

    GameObject* GetHoldObject(HandSide hand);
    void SetHoldObject(HandSide hand, GameObject* obj);
    Vector3 GetHandWorldPos(HandSide hand);


protected:
    UpperArm* upperArms[2];
    Leg* legs[2];
};
