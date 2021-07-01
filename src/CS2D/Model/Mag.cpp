#include "Mag.hpp"

Mag::Mag(Vector2<int> pos, const Sprite& sprite, const int value, AmmoType type,
         Vector2<int> size)
    : GameObject(pos, sprite, size)
{
    ammo = value;
    this->type = type;
}

void Mag::takeAmmo(const int value)
{
    ammo -= value;
    if (ammo <= 0)
        if (!IsDestroyed()) Destroy();
}

int Mag::getAmmo() const { return ammo; }