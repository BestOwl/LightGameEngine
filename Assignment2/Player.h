/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once
#include "GameObject.h"

namespace LightGameEngine
{
	class Player :
		public GameObject
	{
	public:
		using GameObject::GameObject;
		virtual void Draw();
		virtual bool Tick();

		virtual void SetPos(Vector3 pos);

		Vector3 GetCameraPos();
		/// <summary>
		/// Get the reference point used in glLookAt 
		/// </summary>
		/// <returns></returns>
		Vector3 GetLookAtRef();

		void AddYaw(GLfloat degree);
		void AddPitch(GLfloat degree);

		GLfloat GetYaw();
		GLfloat GetPitch();

	protected:
		bool hasMovementLimit = false;
		Vector3 posMax;
		Vector3 posMin;

		/// <summary>
		/// camera yaw degree. 
		/// </summary>
		/// 0 degree equal to the positive direction of x-axis.
		GLfloat yaw;
		GLfloat yawMin = 0;
		GLfloat yawMax = 360;

		GLfloat pitch;
		GLfloat pitchMin = -90;
		GLfloat pitchMax = 90;
	};
}



