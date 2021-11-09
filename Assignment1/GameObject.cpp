#include "GameObject.h"

using namespace NaiveEngine;

GLfloat GameObject::GetX()
{
	return this->x;
}

GLfloat GameObject::GetY()
{
	return this->y;
}

void GameObject::SetX(GLfloat newX)
{
	this->x = newX;
}

void NaiveEngine::GameObject::SetY(GLfloat newY)
{
	this->y = newY;
}

GLfloat GameObject::GetActualAccelerateX()
{
	return this->AccelerateX - this->VelocityX * 0.1f;
}

GLfloat GameObject::GetActualAccelerateY()
{
	// origin AccelerateY - air drag - gravity
	return this->AccelerateY - this->VelocityY * 0.1f - this->Gravity;
}

GLfloat GameObject::GetAirDragForce(GLfloat velocity)
{
	constexpr GLfloat AirDragCoefficient = 0.47;
	constexpr GLfloat AirDensity = 1.293;
	constexpr GLfloat Area = 0.5;
	return (AirDragCoefficient * AirDensity * Area * velocity * velocity) / 2.0f;
}

bool GameObject::Tick()
{
	if (this->IsPhysicsEnabled)
	{
		GLfloat accrX = this->GetActualAccelerateX();
		GLfloat accrY = this->GetActualAccelerateY();
		if (accrX != 0)
		{
			this->VelocityX += accrX;
		}
		if (accrY != 0)
		{
			this->VelocityY += accrY;
		}

		if (abs(this->VelocityX) < 0.0001)
		{
			this->VelocityX = 0;
		}
		if (abs(this->VelocityY) < 0.0001)
		{
			this->VelocityY = 0;
		}

		bool dirty = false;
		if (this->VelocityX != 0)
		{
			this->SetX(this->GetX() + this->VelocityX);
			dirty = true;
		}
		if (this->VelocityY != 0)
		{
			this->SetY(this->GetY() + this->VelocityY);
			dirty = true;
		}

		if (dirty)
		{
			return true;
		}
	}

	return false;
}

GameObject::GameObject(GLfloat x, GLfloat y)
{
	this->x = x;
	this->y = y;
	this->ChildrenObjects = std::vector<GameObject*>();
}

GameObject::~GameObject()
{
	for (GameObject* childrenObj : this->ChildrenObjects)
	{
		if (childrenObj)
		{
			delete childrenObj;
		}
	}
}
