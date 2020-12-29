#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.hpp"
#include "../Others/Game_Parameters.hpp"
#include "../Others/Utils.hpp"
#include "../Others/Logger.hpp"
#include "Mag.hpp"

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

	/*Weapon(Player &player, const Sprite& sprite, const Sprite& floorSprite, std::string weaponName, const WeaponType type, const int maxAmmo, const int curAmmo, const int curAmmoInMag, const int maxAmmoInMag) : GameObject(player.GetGlobalPosition(), sprite, Vector2<int>(InputManager::Width / 26.5, InputManager::Width / 26.5), (int)ObjectType::WEAPON)
	{
		this->SetPosition(Vector2<int>(player.GetGlobalPosition().x, player.GetGlobalPosition().y + 50));
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

	Weapon(const Vector2<int> pos, const Sprite &sprite, const Sprite &floorSprite, const std::string &weaponName,
		   WeaponType type, int maxAmmo, int curAmmo, int curAmmoInMag,
		   const int maxAmmoInMag) : GameObject(Vector2<int>(Utils::PositionToCell(pos).x * Game_Parameters::SIZE_TILE, Utils::PositionToCell(pos).y * Game_Parameters::SIZE_TILE), floorSprite, Vector2<int>(Game_Parameters::SIZE_TILE, Game_Parameters::SIZE_TILE), (int)ObjectType::WEAPON)
	{
		this->weaponType = type;

		ammoType = (AmmoType)((int)weaponType);

		if (weaponType == WeaponType::MAIN)
		{
			this->SetSize(Vector2<int>(Game_Parameters::SIZE_TILE * 2, Game_Parameters::SIZE_TILE));
			this->SetPosition(GetPosition().x - Game_Parameters::SIZE_TILE / 2, GetPosition().y);
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
	void Update();

	void SetParent(GameObject *go) override;
	void RemoveParent() override;
};

#endif // !WEAPON_H