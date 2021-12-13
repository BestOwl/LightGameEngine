/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Engine.h"
#include "EngineUtil.h"

using namespace LightGameEngine;

const int tick_interval = 16; // declare refresh interval in ms
const GLint viewingWidth = 1600;
const GLint viewingHeight = 900;
const float cameraFOV = 70; //Field Of View

static std::vector<GameObject*> stageObjects;
static std::vector<GameObject*> sceneObjects;
static PlayerBase* _player;
static Cube* _skybox;
static InputStatus keyboardStatus;
static bool isPause;
static std::function<void()> _renderOverlayUICallback;
static BitmapFont* debugFont;

// fps
static int frames;
static GLfloat fps;
static LARGE_INTEGER pfc_counter_last;
static LARGE_INTEGER pfc_frequency;


void RenderScene();
void RenderGameObject(GameObject* obj);
void OnTimer(int value);
void OnMouseMove(int x, int y);
void OnMouseEntry(int entry);
void OnMouseButton(int button, int state, int x, int y);

void KeyboardDown(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void SpecialKeyDown(int key, int x, int y);
void SpecialKeyUp(int key, int x, int y);

void Engine::Init(int argc, char** argv, const std::string& windowName)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(viewingWidth, viewingHeight);

	// Init COM 
	EngineUtil::ThrowIfFail(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED));
	QueryPerformanceFrequency(&pfc_frequency);

	glutCreateWindow(windowName.c_str());
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		throw;
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//OnAnimationTimer(0);

	glutDisplayFunc(RenderScene);

	glutMotionFunc(OnMouseMove);
	glutPassiveMotionFunc(OnMouseMove);
	glutEntryFunc(OnMouseEntry);
	glutMouseFunc(OnMouseButton);
	glutSetCursor(GLUT_CURSOR_NONE);

	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);
	glutSpecialFunc(SpecialKeyDown);
	glutSpecialUpFunc(SpecialKeyUp);

	//glutReshapeFunc(Reshape);
	//glutIdleFunc(IdleDisplay);
	glutTimerFunc(tick_interval, OnTimer, 1);

	sceneObjects = std::vector<GameObject*>();
	stageObjects = std::vector<GameObject*>();

	debugFont = EngineUtil::RasterStringSelectFont(20, ANSI_CHARSET, "Consolas Bold");
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

void LightGameEngine::Engine::AddStageObject(GameObject* obj)
{
	stageObjects.push_back(obj);
}

InputStatus* LightGameEngine::Engine::GetKeyboardStatus()
{
	return &keyboardStatus;
}

void Engine::SetPlayer(PlayerBase* obj)
{
	if (_player != nullptr)
	{
		stageObjects.erase(std::remove(stageObjects.begin(), stageObjects.end(), _player));
	}
	_player = obj;
	stageObjects.push_back(obj);
}

void Engine::SetSkybox(Cube* skybox)
{
	if (_skybox != nullptr)
	{
		stageObjects.erase(std::remove(stageObjects.begin(), stageObjects.end(), _skybox));
	}
	_skybox = skybox;
	stageObjects.push_back(skybox);
}

void Engine::SetPauseState(bool pause)
{
	isPause = pause;
}

bool LightGameEngine::Engine::GetPauseState()
{
	return isPause;
}

void LightGameEngine::Engine::RenderOverlayUICallback(std::function<void()> func)
{
	_renderOverlayUICallback = func;
}

void RenderScene()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glAlphaFunc(GL_GREATER, 0.5);
	glEnable(GL_ALPHA_TEST);

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
	glPushAttrib(GL_CURRENT_BIT);
	glLineWidth(1);
	// x-axis
	glColor3ub(255, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(500, 0, 0);
	glEnd();

	// y-axis
	glColor3ub(0, 255, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 500, 0);
	glEnd();

	// z-axis
	glColor3ub(0, 0, 255);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 500);
	glEnd();
	glPopAttrib();
#endif // _DEBUG

	// Lighting
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	GLfloat light_global_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_global_ambient);
	//glEnable(GL_COLOR_MATERIAL);

	Vector3 l0_pos = { 0, 500, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, (GLfloat*)&l0_pos);
	GLfloat l0_ambient[] = { 0.8, 0.8, 0.8 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_ambient);
	glEnable(GL_LIGHT0);

	// Texture Mapping
	glEnable(GL_TEXTURE_2D);

	// draw foreground object
	for (GameObject* obj : sceneObjects)
	{
		RenderGameObject(obj);
	}

	_skybox->SetPos(_player->GetPos());
	for (GameObject* obj : stageObjects)
	{
		RenderGameObject(obj);
	}

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

	_renderOverlayUICallback();


#ifdef _DEBUG
	
	glColor3ub(255, 255, 255);
	EngineUtil::DrawRasterString(debugFont, 4, 20, "Debug Mode");

	std::stringstream ss = std::stringstream();
	ss << "FPS: " << fps;
	EngineUtil::DrawRasterString(debugFont, 104, 20, ss.str());

	ss = std::stringstream();
	Vector3 pos = _player->GetPos();
	ss << "Player Pos: " << std::fixed << std::setprecision(3) << "x: " << pos.x << "  y: " << pos.y << "  z: " << pos.z;
	EngineUtil::DrawRasterString(debugFont, 4, 40, ss.str().c_str());

	ss = std::stringstream();
	ss << "Camera Pos: " << std::fixed << std::setprecision(3) << "x: " << cameraPos.x << "  y: " << cameraPos.y << "  z: " << cameraPos.z;
	EngineUtil::DrawRasterString(debugFont, 4, 60, ss.str().c_str());

	ss = std::stringstream();
	ss << "LookAt Vector: " << std::fixed << std::setprecision(3) << "x: " << lookAtVector.x << "  y: " << lookAtVector.y << "  z: " << lookAtVector.z;
	EngineUtil::DrawRasterString(debugFont, 4, 80, ss.str().c_str());

	ss = std::stringstream();
	ss << "UpVector Pos: " << std::fixed << std::setprecision(3) << "x: " << upVector.x << "  y: " << upVector.y << "  z: " << upVector.z;
	EngineUtil::DrawRasterString(debugFont, 4, 100, ss.str().c_str());

	ss = std::stringstream();
	ss << std::fixed << std::setprecision(3) << "Yaw: " << _player->GetYaw() << "  Pitch: " << _player->GetPitch();
	EngineUtil::DrawRasterString(debugFont, 4, 120, ss.str().c_str());

	ss = std::stringstream();
	ss << std::fixed << std::setprecision(3) << "UpVector Yaw: " << _player->GetUpVectorYaw() << "  UpVector Pitch: " << _player->GetUpVectorPitch();
	EngineUtil::DrawRasterString(debugFont, 4, 140, ss.str().c_str());

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

	AABBox* aabb = obj->GetAABbox();
	if (aabb != NULL)
	{
		GLfloat xLen = aabb->MaxPos.x - aabb->MinPos.x;
		GLfloat yLen = aabb->MaxPos.y - aabb->MinPos.y;
		GLfloat zLen = aabb->MaxPos.z - aabb->MinPos.z;
		glBegin(GL_LINE_LOOP);


		glVertex3f(aabb->MinPos.x, aabb->MinPos.y, aabb->MinPos.z);
		glVertex3f(aabb->MinPos.x + xLen, aabb->MinPos.y, aabb->MinPos.z);
		glVertex3f(aabb->MinPos.x + xLen, aabb->MinPos.y, aabb->MinPos.z + zLen);
		glVertex3f(aabb->MinPos.x, aabb->MinPos.y, aabb->MinPos.z + zLen);

		glVertex3f(aabb->MinPos.x, aabb->MinPos.y + yLen, aabb->MinPos.z);
		glVertex3f(aabb->MinPos.x + xLen, aabb->MinPos.y + yLen, aabb->MinPos.z);
		glVertex3f(aabb->MinPos.x + xLen, aabb->MinPos.y + yLen, aabb->MinPos.z + zLen);
		glVertex3f(aabb->MinPos.x, aabb->MinPos.y + yLen, aabb->MinPos.z + zLen);

		//glVertex3fv((GLfloat*)&this->aabb->MaxPos);

		glEnd();
	}

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

void OnMouseMove(int x, int y)
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

void OnMouseButton(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			keyboardStatus.MouseLeftBtn = true;
		}
		else
		{
			keyboardStatus.MouseLeftBtn = false;
		}
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
		{
			keyboardStatus.MouseMiddleBtn = true;
		}
		else
		{
			keyboardStatus.MouseMiddleBtn = false;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			keyboardStatus.MouseRightBtn = true;
		}
		else
		{
			keyboardStatus.MouseRightBtn = false;
		}
		break;
	default:
		break;
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
	case ' ':
		keyboardStatus.Space = true;
		std::cout << "Jump status set" << std::endl;
		break;
	case 'r':
	case 'R':
		keyboardStatus.R = true;
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
	case ' ':
		keyboardStatus.Space = false;
		std::cout << "Jump status clear" << std::endl;
		break;
	case 'r':
	case 'R':
		keyboardStatus.R = false;
		break;
	default:
		break;
	}
}

void SpecialKeyDown(int key, int x, int y)
{
}

void SpecialKeyUp(int key, int x, int y)
{
}
