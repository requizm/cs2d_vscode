#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"
#include "../Others/Game_Parameters.h"
#include "Mag.h"

enum WeaponType
{
	MAIN,
	PISTOL,
	KNIFE
};

class Weapon : public GameObject
{
public:
	Weapon() : curAmmoInMag(0), maxAmmoInMag(0), curAmmo(0), maxAmmo(0), ammoType(), weaponType(), selected(false)
	{
		this->objType = (ObjectType)ObjectType::WEAPON;
	}

	/*Weapon(Player &player, const Sprite& sprite, const Sprite& floorSprite, std::string weaponName, const WeaponType type, const int maxAmmo, const int curAmmo, const int curAmmoInMag, const int maxAmmoInMag) : GameObject(player.GetGlobalPosition(), sprite, glm::vec2(InputManager::Width / 26.5, InputManager::Width / 26.5), (int)ObjectType::WEAPON)
	{
		this->SetPosition(glm::vec2(player.GetGlobalPosition().x, player.GetGlobalPosition().y + 50));
		this->SetMoveParent(&player);
		this->weaponType = type;
		if (weaponType == WeaponType::MAIN)
			ammoType = AmmoType::PRIMARY;
		else if (weaponType == WeaponType::GUN)
			ammoType = AmmoType::SECONDARY;
		this->maxAmmo = maxAmmo;
		this->curAmmo = curAmmo;
		this->curAmmoInMag = curAmmoInMag;
		this->maxAmmoInMag = maxAmmoInMag;
		this->weaponName = weaponName;
		this->sprites[0] = sprite;
		this->sprites[1] = floorSprite;
		player.addWeapon(*this);
	}*/

	Weapon(const glm::vec2 pos, const Sprite &sprite, const Sprite &floorSprite,const std::string &weaponName,
		   WeaponType type, int maxAmmo, int curAmmo, int curAmmoInMag,
		   const int maxAmmoInMag) : GameObject(glm::vec2(PositionToCell(pos).x * Game_Parameters::SIZE_TILE, PositionToCell(pos).y * Game_Parameters::SIZE_TILE), floorSprite,
												glm::vec2(Game_Parameters::SIZE_TILE, Game_Parameters::SIZE_TILE), (int)ObjectType::WEAPON)
	{
		this->weaponType = type;
		if (weaponType == WeaponType::MAIN)
		{
			ammoType = AmmoType::PRIMARY;
			this->SetSize(glm::vec2(Game_Parameters::SIZE_TILE * 2, Game_Parameters::SIZE_TILE));
		}

		else if (weaponType == WeaponType::PISTOL)
		{
			ammoType = AmmoType::SECONDARY;
		}

		this->maxAmmo = maxAmmo;
		this->curAmmo = curAmmo;
		this->curAmmoInMag = curAmmoInMag;
		this->maxAmmoInMag = maxAmmoInMag;
		this->weaponName = weaponName;
		this->sprites[0] = sprite;
		this->sprites[1] = floorSprite;
		selected = false;
	}

	~Weapon();

	int curAmmoInMag;
	int maxAmmoInMag;
	int curAmmo;
	int maxAmmo;
	AmmoType ammoType;
	WeaponType weaponType;
	std::string weaponName;
	Sprite sprites[2];
	bool selected;

	void Draw(SpriteRenderer &renderer) override;
	void DrawModel(SpriteRenderer &renderer) override;
	void Update(float dt);

	void SetParent(GameObject *go) override;
	void RemoveParent() override;
};

#endif // !WEAPON_H