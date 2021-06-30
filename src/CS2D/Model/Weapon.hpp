#ifndef WEAPON_H
#define WEAPON_H

#include "../../Core/Manager/InputManager.hpp"
#include "../../Core/Manager/Logger.hpp"
#include "../../Core/Manager/Utils.hpp"
#include "../../Core/Model/Camera.hpp"
#include "../../Core/Model/GameObject.hpp"

#include "../Other/GameParameters.hpp"
#include "../Other/SceneManager.hpp"
#include "Tile.hpp"
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
        : curAmmoInMag(0),
          maxAmmoInMag(0),
          curAmmo(0),
          maxAmmo(0),
          ammoType(),
          weaponType(),
          selected(false)
    {
        this->objType = (ObjectType)ObjectType::WEAPON;
    }

    /*Weapon(Player &player, const Sprite& sprite, const Sprite& floorSprite,
    std::string weaponName, const WeaponType type, const int maxAmmo, const int
    curAmmo, const int curAmmoInMag, const int maxAmmoInMag) :
    GameObject(player.GetGlobalPosition(), sprite,
    Vector2<int>(InputManager::Width / 26.5, InputManager::Width / 26.5),
    (int)ObjectType::WEAPON)
    {
            this->SetPosition(Vector2<int>(player.GetGlobalPosition().x,
    player.GetGlobalPosition().y + 50)); this->SetMoveParent(&player);
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
              (int)ObjectType::WEAPON),
          currentIndex(1),
          selected(false)
    {
        this->weaponType = type;

        ammoType = (AmmoType)((int)weaponType);

        if (weaponType == WeaponType::MAIN)
        {
            this->SetSize(Vector2<int>(GameParameters::SIZE_TILE * 2,
                                       GameParameters::SIZE_TILE));
            this->SetPosition(GetPosition().x - GameParameters::SIZE_TILE / 2,
                              GetPosition().y, false);
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

    void Draw(SpriteRenderer &renderer) override;
    void DrawModel(SpriteRenderer &renderer) override;
    void Update();

    void SetParent(GameObject *go) override;
    void RemoveParent() override;

    void setSelect(bool value);
    bool getSelect();

    bool isDropable();
    bool isAmmoAndWeapon();

   private:
    bool selected;
    int currentIndex;  // 0=hand   1=floor
    bool dropable;
    bool ammoAndWeapon;
};

#endif  // WEAPON_H