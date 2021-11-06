#pragma once
#include "GameObject.h"

namespace NaiveEngine
{
	class Player :
		public GameObject
	{
	public:
		using GameObject::GameObject;
		virtual void Draw();

		void SetX(GLfloat newX);
		void SetY(GLfloat newY);
	};
}



