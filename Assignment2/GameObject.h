/*
 * Hao Su's Light Game Engine
 * Author: Hao Su <hao.su19@student.xjtlu.edu.cn>
 * Copyright (c) 2021 Hao Su
 */
#pragma once

#include <vector>
#include "EngineBasis.h"
#include "AABBox.h"
#include "CollisionEngine.h"

namespace LightGameEngine
{
	class GameObject
	{
	public:

		/// <summary>
		/// Get the current pos
		/// </summary>
		virtual Vector3 GetPos();

		virtual void SetPos(Vector3 pos);
		
		/// <summary>
		/// Current rotation degree
		/// </summary>
		Vector3 Rotation;

		/// <summary>
		/// Current zoom scale
		/// </summary>
		Vector3 Scale = { 1, 1, 1 };

		std::vector<GameObject*> ChildrenObjects;

		/// <summary>
		/// Toggle physics simulation 
		/// </summary>
		/// <returns></returns>
		bool IsPhysicsEnabled = false;
		void SetAABbox(AABBox box);
		AABBox* GetAABbox();
		virtual void OnHit(GameObject* hitBy);

		/// <summary>
		/// Current speed
		/// </summary>
		Vector3 Speed;

		GLfloat Gravity = 0.05f;
		GLfloat AirDrag = 0.05f;

		Vector3 Acceleration;
		Vector3 GetActualAcceleration();

		/// <summary>
		/// If ture, this object will be removed from scene and destroyed at next Tick
		/// </summary>
		/// <returns></returns>
		bool IsDestroyed = false;

		/// <summary>
		/// Render the object using OpenGL
		/// </summary>
		virtual void Draw();

		/// <summary>
		/// Update the object state
		/// </summary>
		/// <returns>false if no update, otherwise return true</returns>
		virtual bool Tick();

		/// <summary>
		/// Initialize a GameObject object
		/// </summary>
		/// <param name="initPos">Init pos</param>
		GameObject(Vector3 initPos);
		~GameObject();

	protected:
		Vector3 pos;

	private:
		AABBox* relativeAabb;
		AABBox* aabb;
	};
}



