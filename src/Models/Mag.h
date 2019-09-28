#ifndef MAG_H
#define MAG_H

#include "GameObject.h"
#include "../Others/Game_Parameters.h"

enum AmmoType
{
	PRIMARY, SECONDARY
};

class Mag :GameObject
{
public:
	Mag() = default;

	Mag(glm::vec2 pos, const Sprite& sprite, const int value, AmmoType type, glm::vec2 size = glm::vec2(Game_Parameters::SCREEN_WIDTH / 26.5, Game_Parameters::SCREEN_WIDTH / 26.5))
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
