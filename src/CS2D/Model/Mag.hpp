#ifndef MAG_H
#define MAG_H

#include "../../Core/Model/GameObject.hpp"
#include "../Other/GameParameters.hpp"


enum AmmoType
{
    PRIMARY,
    SECONDARY,
    EMPTY
};

class Mag : GameObject
{
   public:
    Mag() = default;

    Mag(const Vector2<int> &pos, const Sprite &sprite, const int value, AmmoType type,
        const Vector2<int> &size = Vector2<int>(GameParameters::SCREEN_WIDTH / 26,
                                                GameParameters::SCREEN_WIDTH / 26));

    void takeAmmo(int value);
    int getAmmo() const;

    AmmoType type;

   private:
    int ammo;
};

#endif  // !MAG_H
