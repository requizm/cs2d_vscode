#include "Weapon.hpp"

#include "../Scene/StartGame.hpp"


Weapon::~Weapon() = default;

void Weapon::DrawModel(SpriteRenderer &renderer)
{
    if (!IsParent() || (selected && IsParent()))
    {
        renderer.DrawSprite(this->sprites[currentIndex], transform);
    }
}

void Weapon::Update() {}

void Weapon::SetParent(Object *value)
{
    if (IsParent())
    {
        return;
    }
    const Vector2<int> newSize = Vector2<int>(GameParameters::SIZE_TILE, GameParameters::SIZE_TILE);
    this->SetSize(newSize);
    SetPosition(value->GetPosition());
    Vector2<int> dif = Utils::ScreenToWorld(StartGame::instance().camera->view,
                                            InputManager::mousePos) -
                       this->GetPosition();
    Vector2<float> a = dif.Normalize();
    const Vector2<float> newPosF = Vector2<float>(GetPosition().x + a.x * GameParameters::SIZE_TILE / 4,
                                                  GetPosition().y + a.y * GameParameters::SIZE_TILE / 4);
    const Vector2<int> newPosI = Vector2<int>(static_cast<int>(newPosF.x), static_cast<int>(newPosF.y));
    SetPosition(newPosI, false);
    parent = value;
    setSelect(true);
    localTransform =
        Projection::inverse(parent->GetTransform()) * transform;
}
void Weapon::RemoveParent()
{
    Vector2 t = parent->GetPositionOfCenter();
    Object::RemoveParent();
    setCellPosition(Utils::PositionToCell(t));
    setSelect(false);

    if (weaponType == WeaponType::MAIN)
    {
        this->SetSize(Vector2<int>(GameParameters::SIZE_TILE * 2,
                                   GameParameters::SIZE_TILE));
        const Vector2<int> newPos = Vector2<int>(GetPosition().x - GameParameters::SIZE_TILE / 2,
                                                 GetPosition().y);
        this->SetPosition(newPos, false);
    }
}

void Weapon::setSelect(bool value)
{
    if (value != this->selected)
    {
        this->selected = value;
        if (value)
        {
            // onselect
            if (IsParent())
            {
                currentIndex = 0;
            }
        }
        else
        {
            // ondeselect
            if (!IsParent())
            {
                currentIndex = 1;
            }
            else
            {
                currentIndex = 1;
            }
        }
    }
}

bool Weapon::getSelect() { return this->selected; }

bool Weapon::isDropable() { return this->dropable; }

bool Weapon::isAmmoAndWeapon() { return this->ammoAndWeapon; }