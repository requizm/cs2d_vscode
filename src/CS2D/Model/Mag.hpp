#ifndef MAG_H
#define MAG_H

#include "../../Core/Model/GameObject.hpp"
#include "../Other/Game_Parameters.hpp"

enum AmmoType
{
	PRIMARY, SECONDARY, EMPTY
};

class Mag :GameObject
{
public:
	Mag() = default;

	Mag(Vector2<int> pos, const Sprite& sprite, const int value, AmmoType type, Vector2<int> size = Vector2<int>(Game_Parameters::SCREEN_WIDTH / 26, Game_Parameters::SCREEN_WIDTH / 26))
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
