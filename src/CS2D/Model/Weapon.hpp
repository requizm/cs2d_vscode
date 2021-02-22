#ifndef WEAPON_H
#define WEAPON_H

#include "../../Core/Manager/InputManager.hpp"
#include "../../Core/Manager/Logger.hpp"
#include "../../Core/Manager/Utils.hpp"
#include "../../Core/Model/Camera.hpp"
#include "../../Core/Model/GameObject.hpp"
#include "../Other/GameParameters.hpp"
#include "Mag.hpp"


enum WeaponType
{
    MAIN,
    PISTOL,
    KNIFE,
    BOMB
};

class Weapon : public GameObject
{
   public:
    Weapon()
        : GameObject()
    {
        objType = ObjectType::WEAPON;
    }

    Weapon(const Vector2<int> pos, const Sprite &sprite,
           const Sprite &floorSprite, const std::string &weaponName,
           WeaponType type, int maxAmmo, int curAmmo, int curAmmoInMag,
           const int maxAmmoInMag, bool dropable, bool ammoAndWeapon)
        : GameObject(
              Vector2<int>(
                  Utils::PositionToCell(pos).x * GameParameters::SIZE_TILE,
                  Utils::PositionToCell(pos).y * GameParameters::SIZE_TILE),
              floorSprite,
              Vector2<int>(GameParameters::SIZE_TILE,
                           GameParameters::SIZE_TILE),
              ObjectType::WEAPON),
          currentIndex(1),
          selected(false)
    {
        this->weaponType = type;

        ammoType = (AmmoType)((int)weaponType);

        if (weaponType == WeaponType::MAIN)
        {
            this->SetSize(Vector2<int>(GameParameters::SIZE_TILE * 2,
                                       GameParameters::SIZE_TILE));
            const Vector2<int> newPos = Vector2<int>(GetPosition().x - GameParameters::SIZE_TILE / 2,
                                                     GetPosition().y);
            this->SetPosition(newPos, false);
        }

        this->maxAmmo = maxAmmo;
        this->curAmmo = curAmmo;
        this->curAmmoInMag = curAmmoInMag;
        this->maxAmmoInMag = maxAmmoInMag;
        this->weaponName = weaponName;
        this->sprites[0] = sprite;
        this->sprites[1] = floorSprite;

        this->dropable = dropable;
        this->ammoAndWeapon = ammoAndWeapon;
        ;
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

    void DrawModel(SpriteRenderer &renderer) override;
    void Update();

    void SetParent(Object *value) override;
    void RemoveParent() override;

    void setSelect(bool value);
    bool getSelect();

    bool isDropable();
    bool isAmmoAndWeapon();

   private:
    bool selected = false;
    int currentIndex = 1;  // 0=hand   1=floor
    bool dropable = true;
    bool ammoAndWeapon = false;
};

#endif  // WEAPON_H