/*
 * Hao Su's Naive Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once

#include <GL/freeglut.h>
#include <vector>

namespace NaiveEngine
{
	class GameObject
	{
	public:

		/// <summary>
		/// Get the current x pos
		/// </summary>
		/// <returns>x pos</returns>
		virtual GLfloat GetX();

		/// <summary>
		/// Get the current y pos
		/// </summary>
		/// <returns>y pos</returns>
		virtual GLfloat GetY();

		virtual void SetX(GLfloat newX);
		virtual void SetY(GLfloat newY);

		/// <summary>
		/// current rotation around x-axis in degress 
		/// </summary>
		/// <returns>x-axis rotation degress</returns>
		GLfloat RotateX = 0;

		/// <summary>
		/// current rotation around y-axis in degress
		/// </summary>
		/// <returns>y-axis rotation degress</returns>
		GLfloat RotateY = 0;

		/// <summary>
		/// current rotation around z-axis in degress
		/// </summary>
		/// <returns></returns>
		GLfloat RotateZ = 0;

		/// <summary>
		/// current zoom scale
		/// </summary>
		/// <returns>zoom scale</returns>
		GLfloat Scale = 1;

		std::vector<GameObject*> ChildrenObjects;

		/// <summary>
		/// Toggle physics simulation 
		/// </summary>
		/// <returns></returns>
		bool IsPhysicsEnabled = false;

		GLfloat VelocityX = 0;
		GLfloat VelocityY = 0;

		GLfloat Gravity = 0.3f;

		GLfloat AccelerateX = 0;
		GLfloat AccelerateY = 0;

		GLfloat GetActualAccelerateX();
		GLfloat GetActualAccelerateY();

		GLfloat GetAirDragForce(GLfloat velocity);

		//GLflaot AirDragX = (1 / 2) * 1.293 *

		/// <summary>
		/// If ture, this object will be removed from scene and destroyed at next Tick
		/// </summary>
		/// <returns></returns>
		bool IsDestroyed = false;

		/// <summary>
		/// Render the object using OpenGL
		/// </summary>
		virtual void Draw() = 0;

		/// <summary>
		/// Update the object state
		/// </summary>
		/// <returns>false if no update, otherwise return true</returns>
		virtual bool Tick();

		/// <summary>
		/// Initialize a GameObject object
		/// </summary>
		/// <param name="x">Init x pos</param>
		/// <param name="y">Init y pos</param>
		GameObject(GLfloat x, GLfloat y);
		~GameObject();

	protected:
		GLfloat x;
		GLfloat y;
	};
}



