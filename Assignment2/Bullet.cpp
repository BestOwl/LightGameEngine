#include "Bullet.h"
#include "TextureStore.h"

Bullet::Bullet(Vector3 initPos, Vector3 direction) : Cube(initPos, 0.3f, TextureStore::MetalCube)
{
	this->IsPhysicsEnabled = true;
	this->Gravity = 0.f;
	this->AirDrag = 0.f;
	this->Direction = direction;
	this->Speed = 5 * direction.Scale(1);
	this->FlyTime = 1000;
	this->currentFlyTime = 0;
	this->SetAABbox(AABBox(Vector3{ -0.15, -0.15f, -0.15f }, Vector3{ 0.15f, 0.15f, 0.15f }));
}

bool Bullet::Tick()
{
	this->currentFlyTime++;

	if (this->currentFlyTime == this->FlyTime)
	{
		this->IsDestroyed = true;
	}

	return Cube::Tick();
}
