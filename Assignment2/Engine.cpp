/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include "Engine.h"
#include "EngineUtil.h"

#include <GL/freeglut.h>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace LightGameEngine;

const int tick_interval = 16; // declare refresh interval in ms
const GLint viewingWidth = 1600;
const GLint viewingHeight = 900;
const float cameraFOV = 70; //Field Of View

static std::vector<GameObject*> sceneObjects;
static PlayerBase* _player;
static Cube* _skybox;
static KeyboardStatus keyboardStatus;
static bool isPause;

// fps
static int frames;
static GLfloat fps;
static LARGE_INTEGER pfc_counter_last;
static LARGE_INTEGER pfc_frequency;


void RenderScene();
void RenderGameObject(GameObject* obj);
void OnTimer(int value);
void MouseMovePassive(int x, int y);
void OnMouseEntry(int entry);
void KeyboardDown(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);

void Engine::Init(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(viewingWidth, viewingHeight);

	// Init COM 
	EngineUtil::ThrowIfFail(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED));
	QueryPerformanceFrequency(&pfc_frequency);

	glutCreateWindow("Assignment 2");

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//OnAnimationTimer(0);

	glutDisplayFunc(RenderScene);

	glutPassiveMotionFunc(MouseMovePassive);
	glutEntryFunc(OnMouseEntry);
	glutSetCursor(GLUT_CURSOR_NONE);

	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	//glutReshapeFunc(Reshape);
	//glutIdleFunc(IdleDisplay);
	glutTimerFunc(tick_interval, OnTimer, 1);

	sceneObjects = std::vector<GameObject*>();
}

void Engine::Run()
{
	
	
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

void Engine::SetPlayer(PlayerBase* obj)
{
	_player = obj;
}

void Engine::SetSkybox(Cube* skybox)
{
	_skybox = skybox;
}

void Engine::SetPauseState(bool pause)
{
	isPause = pause;
}

bool LightGameEngine::Engine::GetPauseState()
{
	return isPause;
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
	Vector3 cameraPos = _player->GetCameraPos();
	Vector3 lookAtVector = _player->GetLookAtVector();
	Vector3 upVector = _player->GetUpVector();
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
		cameraPos.x + lookAtVector.x, cameraPos.y + lookAtVector.y, cameraPos.z + lookAtVector.z,
		upVector.x, upVector.y, upVector.z);

#ifdef _DEBUG
	glLineWidth(1);
	// x-axis
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
#endif // _DEBUG

	// Lighting
	glEnable(GL_LIGHTING);
	GLfloat light_global_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
	glEnable(GL_COLOR_MATERIAL);

	Vector3 l0_pos = { 0, 500, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, (GLfloat*)&l0_pos);
	GLfloat l0_ambient[] = { 0.8, 0.8, 0.8 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_ambient);
	glEnable(GL_LIGHT0);

	// draw foreground object
	for (GameObject* obj : sceneObjects)
	{
		RenderGameObject(obj);
	}

	RenderGameObject(_player);
	_skybox->SetPos(_player->GetPos());
	RenderGameObject(_skybox);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

#ifndef LG_ENGINE_OVERLAY
#define LG_ENGINE_OVERLAY
#endif // !LG_ENGINE_OVERLAY

#ifdef LG_ENGINE_OVERLAY
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	gluOrtho2D(0, viewingWidth, viewingHeight, 0);

	glDisable(GL_LIGHTING);

	frames++;
	LARGE_INTEGER pfc_counter;
	QueryPerformanceCounter(&pfc_counter);

	if ((pfc_counter.QuadPart - pfc_counter_last.QuadPart) / pfc_frequency.QuadPart >= 1)
	{
		fps = frames;
		frames = 0;
		pfc_counter_last = pfc_counter;
	}


#ifdef _DEBUG
	EngineUtil::RasterStringSelectFont(20, ANSI_CHARSET, "Cascadia Code");
	glColor3ub(255, 255, 255);
	EngineUtil::DrawRasterString(4, 20, "Debug Mode");

	std::stringstream ss = std::stringstream();
	ss << "FPS: " << fps;
	EngineUtil::DrawRasterString(104, 20, ss.str().c_str());

	//ss = std::stringstream();
	//Vector3 pos = objPlayer->GetPos();
	//ss << "Player Pos: " << std::fixed << std::setprecision(3) << "x: " << pos.x << "  y: " << pos.y << "  z: " << pos.z;
	//EngineUtil::DrawRasterString(4, 40, ss.str().c_str());

	//ss = std::stringstream();
	//ss << "Camera Pos: " << std::fixed << std::setprecision(3) << "x: " << cameraPos.x << "  y: " << cameraPos.y << "  z: " << cameraPos.z;
	//EngineUtil::DrawRasterString(4, 60, ss.str().c_str());

	//ss = std::stringstream();
	//ss << "LookAt Vector: " << std::fixed << std::setprecision(3) << "x: " << lookAtVector.x << "  y: " << lookAtVector.y << "  z: " << lookAtVector.z;
	//EngineUtil::DrawRasterString(4, 80, ss.str().c_str());

	//ss = std::stringstream();
	//ss << "UpVector Pos: " << std::fixed << std::setprecision(3) << "x: " << upVector.x << "  y: " << upVector.y << "  z: " << upVector.z;
	//EngineUtil::DrawRasterString(4, 100, ss.str().c_str());

	//ss = std::stringstream();
	//ss << std::fixed << std::setprecision(3) << "Yaw: " << objPlayer->GetYaw() << "  Pitch: " << objPlayer->GetPitch();
	//EngineUtil::DrawRasterString(4, 120, ss.str().c_str());

	//ss = std::stringstream();
	//ss << std::fixed << std::setprecision(3) << "UpVector Yaw: " << objPlayer->GetUpVectorYaw() << "  UpVector Pitch: " << objPlayer->GetUpVectorPitch();
	//EngineUtil::DrawRasterString(4, 140, ss.str().c_str());

#endif

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
#endif // LG_ENGINE_OVERLAY

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
	if (!Engine::GetPauseState())
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

		if (TickObject(_player))
		{
			dirty = true;
		}

		if (dirty)
		{
			glutPostRedisplay();
		}
	}
	
	glutTimerFunc(tick_interval, OnTimer, 1);
}

void MouseMovePassive(int x, int y)
{
	int xDev = x - (viewingWidth / 2);
	int yDev = y - (viewingHeight / 2);

	_player->AddYaw(xDev / 20.0);
	_player->AddPitch(-yDev / 20.0);

	if (xDev != 0 || yDev != 0)
	{
		glutPostRedisplay();
	}
}

void OnMouseEntry(int entry)
{
	if (entry == GLUT_LEFT)
	{
		Engine::SetPauseState(true);
	}
	else if (entry == GLUT_ENTERED)
	{
		glutWarpPointer(viewingWidth / 2, viewingHeight / 2);
		Engine::SetPauseState(false);
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
