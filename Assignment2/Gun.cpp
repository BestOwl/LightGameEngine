#include "Gun.h"

Gun::Gun(Vector3 initPos, GLuint magCapacity) : GameObject(initPos)
{
	this->magAmmoCapacity = magCapacity;
	this->magAmmo = magCapacity;
}

GLuint Gun::GetAmmoCapacity()
{
	return this->magAmmoCapacity;
}

GLuint Gun::GetCurrentAmmo()
{
	return this->magAmmo;
}

void Gun::ReloadAmmo()
{
	this->magAmmo = this->magAmmoCapacity;
}

void Gun::Fire(Vector3 direction)
{
	if (this->magAmmo > 0)
	{
		this->magAmmo--;
	}
}
