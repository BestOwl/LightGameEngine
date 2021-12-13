#include "Gun.h"

Gun::Gun(Vector3 initPos, GLuint magCapacity) : GameObject(initPos)
{
	this->magAmmoCapacity = magCapacity;
	this->magAmmo = magCapacity;
}

bool Gun::Tick()
{
	if (cooling != 0)
	{
		cooling++;
		if (cooling == coolingTime)
		{
			cooling = 0;
		}
	}
	return false;
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

bool Gun::Fire()
{
	if (this->magAmmo > 0 && cooling == 0)
	{
		this->magAmmo--;
		this->cooling = 1;
		return true;
	}
	return false;
}
