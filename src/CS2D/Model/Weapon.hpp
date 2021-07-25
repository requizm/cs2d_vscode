#ifndef WEAPON_H
#define WEAPON_H

#include "../../Core/Model/GameObject.hpp"
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
    Weapon();
    Weapon(const Vector2<int> &pos, const Sprite &sprite,
           const Sprite &floorSprite, const std::string &weaponName,
           WeaponType type, int maxAmmo, int curAmmo, int curAmmoInMag,
           const int maxAmmoInMag, bool dropable, bool ammoAndWeapon);
    ~Weapon() = default;

    int curAmmoInMag = 0;
    int maxAmmoInMag = 0;
    int curAmmo = 0;
    int maxAmmo = 0;
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
    bool selected = false;
    int currentIndex;  // 0=hand   1=floor
    bool dropable;
    bool ammoAndWeapon;
};

#endif  // WEAPON_H