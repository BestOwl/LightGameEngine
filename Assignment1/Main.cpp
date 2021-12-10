/*
 * Hao Su's Naive Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#define FREEGLUT_STATIC
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include <vector>

#include "NaiveEngineUtil.h"
#include "LiverpoolPavilion.h"
#include "CentralBuilding.h"
#include "Balloon.h"
#include "PlayerLiverBird.h"
#include "HandHeldWindmill.h"
#include "Cloud.h"
#include "Firework.h"

using namespace NaiveEngine;

const int tick_interval = 16; // declare refresh interval in ms
const int animation_interval = 2000;

void RenderScene();
void Reshape(int w, int h);
void OnTimer(int value);
void OnAnimationTimer(int value);
void OnSpecialKeyEvent(int key, int x, int y);
void OnKeyEvent(unsigned char key, int x, int y);

std::vector<GameObject*> sceneObjects = std::vector<GameObject*>();
bool zoom = false;
PlayerLiverBird _player = PlayerLiverBird(0, 0);

const GLint viewingWidth = 800;
const GLint viewingHeight = 600;
const GLint orthoL = -(viewingWidth / 2);;
const GLint orthoR = viewingWidth / 2;
const GLint orthoB = -(viewingHeight / 2);
const GLint orthoT = viewingHeight / 2;
GLint viewingOffsetX;
GLint viewingOffsetY;
const GLint viewingOffsetXmax = viewingWidth / 2;
const GLint viewingOffsetXmin = 0;
const GLint viewingOffsetYmax = 0;
const GLint viewingOffsetYmin = 0;

void ShowUserGuide()
{
	MessageBox(NULL, L"Welcome to this game\n\n W or left arrow - move to left\nD or right arrow - move to right\n Space - fly\n z - Zoom toggle\n\nPress F1 to see this guide again.", L"User Guide - Fly me to the XJTLU: 15th Anniversary Edition", MB_OK);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(viewingWidth, viewingHeight);
	glutCreateWindow("Fly me to the XJTLU: 15th Anniversary Edition - Press F1 to see the User Guide");

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	NaiveEngineUtil::Init();
	NaiveEngineUtil::SelectFont(16, "MSYHL.TTC");
	//NaiveEngineUtil::DrawString("S");

	sceneObjects.push_back(new Cloud(-320, 250));
	sceneObjects.push_back(new Cloud(-120, 200));
	sceneObjects.push_back(new Cloud(100, 180));
	sceneObjects.push_back(new Cloud(450, 240));
	sceneObjects.push_back(new LiverpoolPavilion(-240, -220));
	sceneObjects.push_back(new CentralBuilding(100, -150));
	sceneObjects.push_back(new HandHeldWindmill(-50, -100));
	sceneObjects.push_back(new HandHeldWindmill(400, -80));
	sceneObjects.push_back(new HandHeldWindmill(650, -90));

	OnAnimationTimer(0);

	glutDisplayFunc(RenderScene);
	glutSpecialFunc(OnSpecialKeyEvent);
	glutKeyboardFunc(OnKeyEvent);
	glutReshapeFunc(Reshape);
	//glutIdleFunc(IdleDisplay);
	glutTimerFunc(tick_interval, OnTimer, 1);

	glutMainLoop();
}

void RenderGameObject(GameObject* obj)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(obj->GetX(), obj->GetY(), 0);
	glRotatef(obj->RotateX, 1, 0, 0);
	glRotatef(obj->RotateY, 0, 1, 0);
	glRotatef(obj->RotateZ, 0, 0, 1);
	glScalef(obj->Scale, obj->Scale, 1);
	obj->Draw();

	for (GameObject* children : obj->ChildrenObjects)
	{
		RenderGameObject(children);
	}

	glPopMatrix();
}

void RenderScene()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(orthoL + viewingOffsetX, 
		orthoR + viewingOffsetX, 
		orthoB + viewingOffsetY, 
		orthoT + viewingOffsetY);

	if (zoom)
	{
		glViewport(std::max(-(_player.GetX() + 400), -800.0f), -(_player.GetY() + 300), viewingWidth * 2, viewingHeight * 2);
	}
	else 
	{
		glViewport(0, 0, viewingWidth, viewingHeight);
	}

#pragma region render background

	// draw sky
	glBegin(GL_POLYGON);
	glColor3ub(120, 184, 225);
	glVertex2f(-400, 300);

	glColor3ub(58, 125, 200);
	glVertex2f(800, 300);

	glColor3ub(240, 236, 244);
	glVertex2f(800, -300);
	glVertex2f(-400, -300);

	glEnd();

	// draw river
	glColor3ub(26, 138, 180);
	glRectf(-400, -300, 800, -225);

#pragma region draw grass field
	glColor3ub(98, 201, 3);
	glRectf(-400, -225, 800, -125);

	GLfloat yOffsetLast = -1000;
	for (GLfloat i = -400.0; i < 800.0; i += 0.1f)
	{
		GLfloat yOffset = 30 * sin(i / 48);

		if (yOffset > 0)
		{
			if (yOffsetLast <= 0)
			{
				glBegin(GL_POLYGON);
			}
			glVertex2f(i, -125 + yOffset);
		}
		else if (yOffset < 0 && yOffsetLast >= 0)
		{
			glEnd();
		}

		yOffsetLast = yOffset;
	}
#pragma endregion // draw grass field




#pragma endregion // render background

	

	// draw foreground object
	for (GameObject* obj : sceneObjects)
	{
		RenderGameObject(obj);
	}

	glColor3ub(255, 255, 255);
	glShadeModel(GL_SMOOTH);
	NaiveEngineUtil::RasterStringSelectFont(48, ANSI_CHARSET, "Comic Sans MS");
	NaiveEngineUtil::DrawRasterString(0, 250, "XJTLU 15th Anniversary");

	RenderGameObject(&_player);

	glFlush();
}

void Reshape(int w, int h)
{
	glutReshapeWindow(viewingWidth, viewingHeight);
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
	bool dirty = false;
	
	auto i_obj = begin(sceneObjects);
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

	TickObject(&_player);

	if (dirty)
	{
		glutPostRedisplay();
	}

	glutTimerFunc(tick_interval, OnTimer, 1);
}

void OnAnimationTimer(int value)
{
	int i = value * 200;
	srand(time(NULL) + i);
	for (int i = 0; i < 6; i++)
	{
		GLint x = rand() % viewingWidth + viewingOffsetX - viewingWidth / 2;
		GLint y = rand() % (viewingHeight / 2) - 300;
		Color color
		{
			rand() % 255,
			rand() % 255,
			rand() % 255,
		};
		if (value)
		{
			sceneObjects.push_back(new Balloon(x, y, color));
		}
		else 
		{
			GLint flyHeight = rand() % 300 + 100;
			
			sceneObjects.push_back(new Firework(x, y, color, flyHeight));
		}

	}

	glutTimerFunc(animation_interval, OnAnimationTimer, !value);
}

static int player_movement_step = 10;
void MovePlayerLeft()
{
	_player.SetX(_player.GetX() - player_movement_step);
	GLint offset = _player.GetX() - (orthoL + viewingOffsetX);
	if (offset < 100)
	{
		viewingOffsetX -= player_movement_step;
		if (viewingOffsetX < viewingOffsetXmin)
		{
			viewingOffsetX = viewingOffsetXmin;
		}
	}
}

void MovePlayerRight()
{
	_player.SetX(_player.GetX() + player_movement_step);
	GLint offset = orthoR + viewingOffsetX - _player.GetX();
	if (offset < 100)
	{
		viewingOffsetX += player_movement_step;
		if (viewingOffsetX > viewingOffsetXmax)
		{
			viewingOffsetX = viewingOffsetXmax;
		}
	}
}

void OnSpecialKeyEvent(int key, int x, int y)
{
	//static int player_movement_step = 10;
	bool dirty = false;

	GLint offset;
	switch (key)
	{
	//case GLUT_KEY_UP: // Move Up
	//	objPlayer.SetY(objPlayer.GetY() + player_movement_step);
	//	dirty = true;
	//	break;
	//case GLUT_KEY_DOWN: // Move Down
	//	objPlayer.SetY(objPlayer.GetY() - player_movement_step);
	//	dirty = true;
	//	break;
	case GLUT_KEY_RIGHT: // Move Right
		MovePlayerRight();
		
		dirty = true;
		break;
	case GLUT_KEY_LEFT: // Move Left
		MovePlayerLeft();

		dirty = true;
		break;
	case GLUT_KEY_F1:
		ShowUserGuide();
		break;
	default:
		break;
	}

	if (dirty)
	{
		glutPostRedisplay();
	}
}

void OnKeyEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case ' ':
		_player.VelocityY += 5;
		break;
	case 'z':
		zoom = !zoom;
		glutPostRedisplay();
	case 'a':
	case 'A':
		MovePlayerLeft();
		break;
	case 'd':
	case 'D':
		MovePlayerRight();
		break;
	default:
		break;
	}
}

