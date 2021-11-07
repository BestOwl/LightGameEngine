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

	protected:
		bool hasMovementLimit = false;
		GLint xMax = 0;
		GLint xMin = 0;
		GLint yMax = 0;
		GLint yMin = 0;
	};
}



