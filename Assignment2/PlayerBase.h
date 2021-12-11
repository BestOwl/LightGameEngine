/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once
#include "GameObject.h"

namespace LightGameEngine
{
	class PlayerBase :
		public GameObject
	{
	public:
		using GameObject::GameObject;
		virtual void Draw() override;

		virtual void SetPos(Vector3 pos);

		virtual Vector3 GetCameraPos();
		/// <summary>
		/// Get the reference point vector (camera pos as origin) used in glLookAt.
		/// </summary>
		Vector3 GetLookAtVector();

		/// <summary>
		/// Get the up vector (camera pos as origin) used in glLookAt.
		/// </summary>
		Vector3 GetUpVector();

		void AddYaw(GLfloat degree);
		void AddPitch(GLfloat degree);

		GLfloat GetYaw();
		GLfloat GetPitch();

		GLfloat GetUpVectorYaw();
		GLfloat GetUpVectorPitch();

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

		/// <summary>
		/// Warp yaw to valid range
		/// </summary>
		/// <param name="yaw"></param>
		/// <returns></returns>
		GLfloat wrapYaw(GLfloat yaw);
	};
}



