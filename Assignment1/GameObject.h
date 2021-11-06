/*
 * Hao Su's Naive Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once

#include <GL/freeglut.h>

namespace NaiveEngine
{
	class GameObject
	{
	public:
		/// <summary>
		/// Render the object using OpenGL
		/// </summary>
		virtual void Draw() = 0;

		/// <summary>
		/// Get the current x pos
		/// </summary>
		/// <returns>x pos</returns>
		GLfloat getX();

		/// <summary>
		/// Get the current y pos
		/// </summary>
		/// <returns>y pos</returns>
		GLfloat getY();

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

	protected:
		GLfloat x;
		GLfloat y;
	};
}



