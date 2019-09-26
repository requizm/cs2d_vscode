#include "Mag.h"

void Mag::takeAmmo(const int value)
{
	ammo -= value;
	if (ammo <= 0)
		if (!IsDestroyed())
			Destroy();
}

int Mag::getAmmo() const
{
	return ammo;
}