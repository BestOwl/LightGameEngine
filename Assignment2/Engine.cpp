/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "Engine.h"
#include "EngineUtil.h"
#include "GameObject.h"

#include <GL/freeglut.h>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace LightGameEngine;

const int tick_interval = 16; // declare refresh interval in ms
const GLint viewingWidth = 1600;
const GLint viewingHeight = 900;
const float cameraFOV = 90; //Field Of View

static std::vector<GameObject*> sceneObjects;
static Player* objPlayer;
static KeyboardStatus keyboardStatus;

static GLfloat lastMouseX = 0;
static GLfloat lastMouseY = 0;

void RenderScene();
void RenderGameObject(GameObject* obj);
void OnTimer(int value);
void MouseMovePassive(int x, int y);
void KeyboardDown(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);

void Engine::Init(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(viewingWidth, viewingHeight);
	sceneObjects = std::vector<GameObject*>();
}

void Engine::Run()
{
	glutCreateWindow("Assignment 2");

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//OnAnimationTimer(0);

	glutDisplayFunc(RenderScene);
	glutPassiveMotionFunc(MouseMovePassive);
	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	//glutReshapeFunc(Reshape);
	//glutIdleFunc(IdleDisplay);
	glutTimerFunc(tick_interval, OnTimer, 1);

	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(viewingWidth / 2.0, viewingHeight / 2.0);

	glutMainLoop();
}

void Engine::AddSceneObject(GameObject* obj)
{
	sceneObjects.push_back(obj);
}

KeyboardStatus* LightGameEngine::Engine::GetKeyboardStatus()
{
	return &keyboardStatus;
}

void LightGameEngine::Engine::SetPlayer(Player* obj)
{
	objPlayer = obj;
}

void RenderScene()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);

	glPushMatrix();

	glLoadIdentity();
	gluPerspective(cameraFOV, (GLdouble) viewingWidth / (GLdouble) viewingHeight, 0.1, 5000);
	Vector3 cameraPos = objPlayer->GetCameraPos();
	Vector3 refPos = objPlayer->GetLookAtRef();
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
		refPos.x, refPos.y, refPos.z,
		0, 1, 0);

	// x-axis
	glLineWidth(1);

	glBegin(GL_LINES);
	glColor3ub(255, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(500, 0, 0);
	glEnd();

	// y-axis
	glBegin(GL_LINES);
	glColor3ub(0, 255, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 500, 0);
	glEnd();

	// z-axis
	glBegin(GL_LINES);
	glColor3ub(0, 0, 255);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 500);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3ub(150, 150, 0);
	glTranslatef(0, 0, 0);
	glutSolidCube(50);
	glPopMatrix();

	// draw foreground object
	for (GameObject* obj : sceneObjects)
	{
		RenderGameObject(obj);
	}

	RenderGameObject(objPlayer);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

#pragma region 2D UI overlay
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	gluOrtho2D(0, viewingWidth, viewingHeight, 0);

#ifdef _DEBUG
	EngineUtil::RasterStringSelectFont(20, ANSI_CHARSET, "Cascadia Code");
	glColor3ub(255, 255, 255);
	EngineUtil::DrawRasterString(4, 20, "Debug Mode");

	std::stringstream ss = std::stringstream();
	Vector3 pos = objPlayer->GetPos();
	ss << "Player Pos: " << std::fixed << std::setprecision(3) << "x: " << pos.x << "  y: " << pos.y << "  z: " << pos.z;
	EngineUtil::DrawRasterString(4, 40, ss.str().c_str());

	ss = std::stringstream();
	pos = objPlayer->GetCameraPos();
	ss << "Camera Pos: " << std::fixed << std::setprecision(3) << "x: " << pos.x << "  y: " << pos.y << "  z: " << pos.z;
	EngineUtil::DrawRasterString(4, 60, ss.str().c_str());

	ss = std::stringstream();
	pos = objPlayer->GetLookAtRef();
	ss << "LookAt Pos: " << std::fixed << std::setprecision(3) << "x: " << pos.x << "  y: " << pos.y << "  z: " << pos.z;
	EngineUtil::DrawRasterString(4, 80, ss.str().c_str());

	ss = std::stringstream();
	ss << std::fixed << std::setprecision(3) << "Yaw: " << objPlayer->GetYaw() << "  Pitch: " << objPlayer->GetPitch();
	EngineUtil::DrawRasterString(4, 100, ss.str().c_str());

#endif

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
#pragma endregion

	glFlush();
}

void RenderGameObject(GameObject* obj)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	Vector3 pos = obj->GetPos();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(obj->Rotation.x, 1, 0, 0);
	glRotatef(obj->Rotation.y, 0, 1, 0);
	glRotatef(obj->Rotation.z, 0, 0, 1);
	glScalef(obj->Scale.x, obj->Scale.y, obj->Scale.z);
	obj->Draw();

	for (GameObject* children : obj->ChildrenObjects)
	{
		RenderGameObject(children);
	}

	glPopMatrix();
}

bool TickObject(GameObject* obj)
{
	bool dirty = false;

	if (obj->Tick())
	{
		dirty = true;
	}

	auto i_childrenObj = begin(obj->ChildrenObjects);
	while (i_childrenObj != end(obj->ChildrenObjects))
	{
		if ((*i_childrenObj)->IsDestroyed)
		{
			GameObject* p_oldChildrenObj = *i_childrenObj;
			i_childrenObj = obj->ChildrenObjects.erase(i_childrenObj);
			delete p_oldChildrenObj;
		}
		else
		{
			if (TickObject(*i_childrenObj))
			{
				dirty = true;
			}
			++i_childrenObj;
		}
	}

	return dirty;
}

void OnTimer(int value)
{
	glutWarpPointer(viewingWidth / 2, viewingHeight / 2);
	bool dirty = false;

	auto i_obj = std::begin(sceneObjects);
	while (i_obj != end(sceneObjects))
	{
		if ((*i_obj)->IsDestroyed)
		{
			GameObject* p_oldObj = *i_obj;
			i_obj = sceneObjects.erase(i_obj);
			delete p_oldObj;
		}
		else
		{
			if (TickObject(*i_obj))
			{
				dirty = true;
			}

			++i_obj;
		}
	}

	if (TickObject(objPlayer))
	{
		dirty = true;
	}

	if (dirty)
	{
		glutPostRedisplay();
	}

	glutTimerFunc(tick_interval, OnTimer, 1);
}

void MouseMovePassive(int x, int y)
{
	int xDev = x - (viewingWidth / 2);
	int yDev = y - (viewingHeight / 2);

	objPlayer->AddYaw(xDev / 20.0);
	objPlayer->AddPitch(-yDev / 20.0);

	if (abs(xDev) > 0 || abs(yDev) > 0)
	{
		glutPostRedisplay();
	}
}

void KeyboardDown(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
	case 'w':
		keyboardStatus.Forward = true;
		break;
	case 'S':
	case 's':
		keyboardStatus.Backward = true;
		break;
	case 'A':
	case 'a':
		keyboardStatus.Left = true;
		break;
	case 'D':
	case 'd':
		keyboardStatus.Right = true;
		break;
	default:
		break;
	}
}

void KeyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'W':
	case 'w':
		keyboardStatus.Forward = false;
		break;
	case 'S':
	case 's':
		keyboardStatus.Backward = false;
		break;
	case 'A':
	case 'a':
		keyboardStatus.Left = false;
		break;
	case 'D':
	case 'd':
		keyboardStatus.Right = false;
		break;
	default:
		break;
	}
}
