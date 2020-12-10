#ifndef MAG_H
#define MAG_H

#include "GameObject.hpp"
#include "../Others/Game_Parameters.hpp"

enum AmmoType
{
	PRIMARY, SECONDARY, EMPTY
};

class Mag :GameObject
{
public:
	Mag() = default;

	Mag(Vector2<float> pos, const Sprite& sprite, const int value, AmmoType type, Vector2<float> size = Vector2<float>(Game_Parameters::SCREEN_WIDTH / 26.5F, Game_Parameters::SCREEN_WIDTH / 26.5F))
		:GameObject(pos, sprite, size)
	{
		ammo = value;
		this->type = type;
	}

	void takeAmmo(int value);
	int getAmmo() const;

	AmmoType type;

private:
	int ammo;
};

#endif // !MAG_H
