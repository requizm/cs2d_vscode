#include "Player.hpp"

#include "../../Core/Manager/InputManager.hpp"
#include "../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../Core/Manager/ResourceManager.hpp"
#include "../../Core/Manager/Timer.hpp"
#include "../../Core/Manager/Utils.hpp"
#include "../Other/SceneManager.hpp"
#include "../Scene/StartGame.hpp"
#include "Tile.hpp"


#if defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

#define PI 3.14159265

void Player::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(this->sprites[currentIndex], this->globalPosition,
                        this->globalSize, this->globalRotation);
}

void Player::DrawModel(SpriteRenderer &renderer)
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    renderer.DrawSprite(this->sprites[currentIndex], this->GetTransform());
    knifeWeapons.at(0)->DrawModel(renderer);
}

Player::~Player()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    delete knifeWeapons.at(0);
}

void Player::Init()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    weaponLimit[2] = true;
    auto *knf =
        new Weapon(GetPosition(), Sprite(ResourceManager::GetTexture("knife")),
                   Sprite(ResourceManager::GetTexture("knife")), "knife",
                   WeaponType::KNIFE, 1, 1, 1, 1, false, false);
    knf->SetRotation(this->globalRotation + 0);
    knf->SetParent(this);
    selectedWeapon = knf;
    knifeWeapons.push_back(knf);
}

void Player::Update()
{
    if (lastMousePos != InputManager::mousePos)
    {
        const int komsu = InputManager::mousePos.x -
                          GameParameters::SCREEN_WIDTH / 2;
        const int karsi = InputManager::mousePos.y -
                          GameParameters::SCREEN_HEIGHT / 2;
        const float atan =
            atan2(static_cast<float>(karsi), static_cast<float>(komsu)) *
            180.0F / static_cast<float>(PI);
        SetRotation(static_cast<int>(atan + 90.0F));
        lastMousePos = InputManager::mousePos;
    }
}

void Player::ProcessInput()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    ControllerInput();
    SlotInput();
}

void Player::SetPosition(Vector2<int> pos, bool changeCell)
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    this->globalPosition = pos;
    this->collider.SetPosition(this->GetPositionOfCenter());
    this->BuildTransform();

    StartGame *startGame = SceneManager::instance().GetActiveScene<StartGame>();

    startGame->camera->setPosition(Vector2(
        this->GetPositionOfCenter().x - GameParameters::SCREEN_WIDTH / 2,
        this->GetPositionOfCenter().y - GameParameters::SCREEN_HEIGHT / 2));
    startGame->renderer->SetProjection(
        startGame->camera->cameraMatrix);
    startGame->squareRenderer.SetProjection(
        startGame->camera->cameraMatrix);

    Vector2<int> newCellPos =
        Utils::PositionToCell(this->GetPositionOfCenter());
    if (newCellPos != cellPos)
    {
        this->cellPos = newCellPos;
        for (auto &weapon : map->weapons)
        {
            if (!weaponLimit[((int)weapon->weaponType)] &&
                !weapon->getSelect() && weapon->GetCellPos() == this->cellPos &&
                !weapon->IsParent() && weapon->isDropable())
            {
                if (!weapon->isAmmoAndWeapon())
                {
                    weaponLimit[((int)weapon->weaponType)] = true;
                    weapon->SetRotation(this->globalRotation + 180);
                    weapon->SetParent(this);
                    if (selectedWeapon != nullptr)
                    {
                        selectedWeapon->setSelect(false);
                    }
                    selectedWeapon = weapon;
                    switch (weapon->weaponType)
                    {
                        case WeaponType::MAIN:
                            mainWeapons.push_back(weapon);
                            break;
                        case WeaponType::PISTOL:
                            pistolWeapons.push_back(weapon);
                            break;
                        case WeaponType::KNIFE:
                            knifeWeapons.push_back(weapon);
                            break;
                    }
                }
                else
                {
                    bool found = false;
                    for (auto &bomb : bombWeapons)
                    {
                        if (bomb->weaponName == weapon->weaponName)
                        {
                            if (bomb->curAmmo + 1 <= bomb->maxAmmo)
                            {
                                bomb->curAmmo++;
                                weapon->SetParent(this);
                                weapon->setSelect(false);
                                found = true;
                            }
                            break;
                        }
                    }
                    if (!found)
                    {
                        weapon->SetRotation(this->globalRotation + 180);
                        weapon->SetParent(this);
                        if (selectedWeapon != nullptr)
                        {
                            selectedWeapon->setSelect(false);
                        }
                        selectedWeapon = weapon;
                        bombWeapons.push_back(weapon);
                    }
                }
            }
        }
    }
}

void Player::SetPosition(const int x, const int y, bool changeCell)
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    Vector2<int> newPos = Vector2<int>(x, y);
    this->SetPosition(newPos, changeCell);
}

void Player::ControllerInput()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    if (InputManager::isKey(KeyboardKeys::KEY_W))
    {
        Vector2<int> newPos = Vector2<int>(
            this->GetPosition().x,
            static_cast<int>(static_cast<float>(this->GetPosition().y) - static_cast<float>(this->velocity) * Timer::DeltaTime));
        if (!CheckCollision(newPos, MoveDirection::TOP))
        {
            this->SetPosition(newPos, true);
        }
    }
    if (InputManager::isKey(KeyboardKeys::KEY_S))
    {
        Vector2<int> newPos = Vector2<int>(
            this->GetPosition().x,
            static_cast<int>(static_cast<float>(this->GetPosition().y) + static_cast<float>(this->velocity) * Timer::DeltaTime));
        if (!CheckCollision(newPos, MoveDirection::BOTTOM))
        {
            this->SetPosition(newPos, true);
        }
    }
    if (InputManager::isKey(KeyboardKeys::KEY_A))
    {
        Vector2<int> newPos = Vector2<int>(
            static_cast<int>(static_cast<float>(this->GetPosition().x) - static_cast<float>(this->velocity) * Timer::DeltaTime),
            this->GetPosition().y);
        if (!CheckCollision(newPos, MoveDirection::LEFT))
        {
            this->SetPosition(newPos, true);
        }
    }
    if (InputManager::isKey(KeyboardKeys::KEY_D))
    {
        Vector2<int> newPos = Vector2<int>(
            static_cast<int>(static_cast<float>(this->GetPosition().x) + static_cast<float>(this->velocity) * Timer::DeltaTime),
            this->GetPosition().y);
        if (!CheckCollision(newPos, MoveDirection::RIGHT))
        {
            this->SetPosition(newPos, true);
        }
    }
}

bool Player::CheckCollision(Vector2<int> pos, MoveDirection direction)
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    Tile *newTile;

    Vector2<int> posCenter = Vector2<int>(pos.x + this->GetSize().x / 2,
                                          pos.y + this->GetSize().y / 2);
    CircleCollider col = this->collider;
    col.SetPosition(posCenter);

    switch (direction)
    {
        case MoveDirection::RIGHT:
            newTile =
                map->GetTileByPosition(posCenter.x + this->GetSize().x / 2,
                                       posCenter.y - this->GetSize().y / 2);
            if (newTile == nullptr) return true;
            if (newTile->getType() == TileTypes::WALL ||
                newTile->getType() == TileTypes::OBSTACLE)
            {
                if (col.Intersect(newTile->getCollider()))
                {
                    return true;
                }
            }

            newTile =
                map->GetTileByPosition(posCenter.x + this->GetSize().x / 2,
                                       posCenter.y + this->GetSize().y / 2);
            if (newTile == nullptr) return true;
            if (newTile->getType() == TileTypes::WALL ||
                newTile->getType() == TileTypes::OBSTACLE)
            {
                if (col.Intersect(newTile->getCollider()))
                {
                    return true;
                }
            }
            break;
        case MoveDirection::LEFT:
            newTile =
                map->GetTileByPosition(posCenter.x - this->GetSize().x / 2,
                                       posCenter.y - this->GetSize().y / 2);
            if (newTile == nullptr) return true;
            if (newTile->getType() == TileTypes::WALL ||
                newTile->getType() == TileTypes::OBSTACLE)
            {
                if (col.Intersect(newTile->getCollider()))
                {
                    return true;
                }
            }
            newTile =
                map->GetTileByPosition(posCenter.x - this->GetSize().x / 2,
                                       posCenter.y + this->GetSize().y / 2);
            if (newTile == nullptr) return true;
            if (newTile->getType() == TileTypes::WALL ||
                newTile->getType() == TileTypes::OBSTACLE)
            {
                if (col.Intersect(newTile->getCollider()))
                {
                    return true;
                }
            }
            break;
        case MoveDirection::TOP:
            newTile =
                map->GetTileByPosition(posCenter.x + this->GetSize().x / 2,
                                       posCenter.y - this->GetSize().y / 2);
            if (newTile == nullptr) return true;
            if (newTile->getType() == TileTypes::WALL ||
                newTile->getType() == TileTypes::OBSTACLE)
            {
                if (col.Intersect(newTile->getCollider()))
                {
                    return true;
                }
            }
            newTile =
                map->GetTileByPosition(posCenter.x - this->GetSize().x / 2,
                                       posCenter.y - this->GetSize().y / 2);
            if (newTile == nullptr) return true;
            if (newTile->getType() == TileTypes::WALL ||
                newTile->getType() == TileTypes::OBSTACLE)
            {
                if (col.Intersect(newTile->getCollider()))
                {
                    return true;
                }
            }
            break;
        case MoveDirection::BOTTOM:
            newTile =
                map->GetTileByPosition(posCenter.x + this->GetSize().x / 2,
                                       posCenter.y + this->GetSize().y / 2);
            if (newTile == nullptr) return true;
            if (newTile->getType() == TileTypes::WALL ||
                newTile->getType() == TileTypes::OBSTACLE)
            {
                if (col.Intersect(newTile->getCollider()))
                {
                    return true;
                }
            }
            newTile =
                map->GetTileByPosition(posCenter.x - this->GetSize().x / 2,
                                       posCenter.y + this->GetSize().y / 2);
            if (newTile == nullptr) return true;
            if (newTile->getType() == TileTypes::WALL ||
                newTile->getType() == TileTypes::OBSTACLE)
            {
                if (col.Intersect(newTile->getCollider()))
                {
                    return true;
                }
            }
            break;
    }

    return false;
}
void Player::SlotInput()
{
    if (InputManager::isKeyDown(KeyboardKeys::KEY_G) &&
        selectedWeapon != nullptr && selectedWeapon->isDropable())
    {
        if (!selectedWeapon->isAmmoAndWeapon())
        {
            selectedWeapon->RemoveParent();
            weaponLimit[((int)selectedWeapon->weaponType)] = false;

            switch (selectedWeapon->weaponType)
            {
                case WeaponType::MAIN:
                    if (mainWeapons.size() >= 2)
                    {
                        mainWeapons.at(mainIndex) = nullptr;
                        mainWeapons.erase(mainWeapons.begin() + mainIndex);
                        selectedWeapon = mainWeapons.at(mainWeapons.size() - 1);
                        mainIndex = mainWeapons.size() - 1;
                        selectedWeapon->setSelect(true);
                    }
                    else if (!pistolWeapons.empty())
                    {
                        mainWeapons.at(0) = nullptr;
                        mainWeapons.erase(mainWeapons.begin() + 0);
                        selectedWeapon = pistolWeapons.at(0);
                        selectedWeapon->setSelect(true);
                        mainIndex = 0;
                    }
                    else
                    {
                        mainWeapons.at(0) = nullptr;
                        mainWeapons.erase(mainWeapons.begin() + 0);
                        selectedWeapon = knifeWeapons.at(0);
                        selectedWeapon->setSelect(true);
                        mainIndex = 0;
                    }
                    break;
                case WeaponType::PISTOL:
                    if (!pistolWeapons.size() >= 2)
                    {
                        pistolWeapons.at(pistolIndex) = nullptr;
                        pistolWeapons.erase(pistolWeapons.begin() +
                                            pistolIndex);
                        selectedWeapon =
                            pistolWeapons.at(pistolWeapons.size() - 1);
                        pistolIndex = pistolWeapons.size() - 1;
                        selectedWeapon->setSelect(true);
                    }
                    else if (!mainWeapons.empty())
                    {
                        pistolWeapons.at(0) = nullptr;
                        pistolWeapons.erase(pistolWeapons.begin() + 0);
                        selectedWeapon = mainWeapons.at(0);
                        selectedWeapon->setSelect(true);
                        pistolIndex = 0;
                    }
                    else
                    {
                        pistolWeapons.at(0) = nullptr;
                        pistolWeapons.erase(pistolWeapons.begin() + 0);
                        selectedWeapon = knifeWeapons.at(0);
                        selectedWeapon->setSelect(true);
                        pistolIndex = 0;
                    }
                    break;
                case WeaponType::KNIFE:
                    if (!knifeWeapons.size() >= 2)
                    {
                        knifeWeapons.at(knifeIndex) = nullptr;
                        knifeWeapons.erase(knifeWeapons.begin() + knifeIndex);
                        selectedWeapon =
                            knifeWeapons.at(knifeWeapons.size() - 1);
                        knifeIndex = knifeWeapons.size() - 1;
                        selectedWeapon->setSelect(true);
                    }
                    else
                    {
                        knifeWeapons.at(0) = nullptr;
                        knifeWeapons.erase(knifeWeapons.begin() + 0);
                        selectedWeapon = knifeWeapons.at(0);
                        selectedWeapon->setSelect(true);
                        knifeIndex = 0;
                    }
                    break;
            }
        }
        else
        {
            if (selectedWeapon->curAmmo > 1)
            {
                for (auto &wp : map->weapons)
                {
                    if (wp->IsParent() && !wp->getSelect() &&
                        wp->weaponName == selectedWeapon->weaponName)
                    {
                        wp->RemoveParent();
                        selectedWeapon->curAmmo = selectedWeapon->curAmmo - 1;
                        return;
                    }
                }
            }

            if (bombWeapons.size() >= 2)
            {
                bombWeapons.at(mainIndex) = nullptr;
                bombWeapons.erase(bombWeapons.begin() + mainIndex);
                selectedWeapon = bombWeapons.at(bombWeapons.size() - 1);
                mainIndex = bombWeapons.size() - 1;
                selectedWeapon->setSelect(true);
            }
            else if (mainWeapons.size() >= 1)
            {
                bombWeapons.at(0) = nullptr;
                bombWeapons.erase(bombWeapons.begin() + 0);
                selectedWeapon = mainWeapons.at(0);
                selectedWeapon->setSelect(true);
            }
            else if (pistolWeapons.size() >= 1)
            {
                bombWeapons.at(0) = nullptr;
                bombWeapons.erase(bombWeapons.begin() + 0);
                selectedWeapon = pistolWeapons.at(0);
                selectedWeapon->setSelect(true);
            }
            else
            {
                bombWeapons.at(0) = nullptr;
                bombWeapons.erase(bombWeapons.begin() + 0);
                selectedWeapon = knifeWeapons.at(0);
                selectedWeapon->setSelect(true);
            }
        }
    }
    else if (InputManager::isKeyDown(KeyboardKeys::KEY_1) &&
             !mainWeapons.empty() && selectedWeapon != nullptr &&
             selectedWeapon != mainWeapons.at(mainIndex))
    {
        if (selectedWeapon->weaponType != WeaponType::MAIN)
        {
            selectedWeapon->setSelect(false);
            mainIndex = 0;
            selectedWeapon = mainWeapons.at(mainIndex);
            selectedWeapon->setSelect(true);
        }
        else if (mainWeapons.size() >= 2)
        {
            selectedWeapon->setSelect(false);
            if (mainIndex + 1 == mainWeapons.size())
            {
                mainIndex = 0;
            }
            else
            {
                mainIndex = mainIndex + 1;
            }
            selectedWeapon = mainWeapons.at(mainIndex);
            selectedWeapon->setSelect(true);
        }
    }
    else if (InputManager::isKeyDown(KeyboardKeys::KEY_2) &&
             !pistolWeapons.empty() && selectedWeapon != nullptr &&
             selectedWeapon != pistolWeapons.at(pistolIndex))
    {
        if (selectedWeapon->weaponType != WeaponType::PISTOL)
        {
            selectedWeapon->setSelect(false);
            pistolIndex = 0;
            selectedWeapon = pistolWeapons.at(pistolIndex);
            selectedWeapon->setSelect(true);
        }
        else if (pistolWeapons.size() >= 2)
        {
            selectedWeapon->setSelect(false);
            if (pistolIndex + 1 == pistolWeapons.size())
            {
                pistolIndex = 0;
            }
            else
            {
                pistolIndex = pistolIndex + 1;
            }
            selectedWeapon = pistolWeapons.at(pistolIndex);
            selectedWeapon->setSelect(true);
        }
    }
    else if (InputManager::isKeyDown(KeyboardKeys::KEY_3) &&
             !knifeWeapons.empty() && selectedWeapon != nullptr &&
             selectedWeapon != knifeWeapons.at(knifeIndex))
    {
        if (selectedWeapon->weaponType != WeaponType::KNIFE)
        {
            selectedWeapon->setSelect(false);
            knifeIndex = 0;
            selectedWeapon = knifeWeapons.at(knifeIndex);
            selectedWeapon->setSelect(true);
        }
        else if (knifeWeapons.size() >= 2)
        {
            selectedWeapon->setSelect(false);
            if (knifeIndex + 1 == knifeWeapons.size())
            {
                knifeIndex = 0;
            }
            else
            {
                knifeIndex = knifeIndex + 1;
            }
            selectedWeapon = knifeWeapons.at(knifeIndex);
            selectedWeapon->setSelect(true);
        }
    }
    else if (InputManager::isKeyDown(KeyboardKeys::KEY_4) &&
             !bombWeapons.empty() && selectedWeapon != nullptr &&
             selectedWeapon != bombWeapons.at(bombIndex))
    {
        if (selectedWeapon->weaponType != WeaponType::BOMB)
        {
            selectedWeapon->setSelect(false);
            bombIndex = 0;
            selectedWeapon = bombWeapons.at(bombIndex);
            selectedWeapon->setSelect(true);
        }
        else if (bombWeapons.size() >= 2)
        {
            selectedWeapon->setSelect(false);
            if (bombIndex + 1 == bombWeapons.size())
            {
                bombIndex = 0;
            }
            else
            {
                bombIndex = bombIndex + 1;
            }
            selectedWeapon = bombWeapons.at(bombIndex);
            selectedWeapon->setSelect(true);
        }
    }
}
void Player::SetMap(Map *map)
{
    // this->map = std::move(map);
    this->map = map;
}

void Player::setVelocity(const int velocity) { this->velocity = velocity; }

void Player::takeDamage(const int value)
{
    health -= value;
    if (health <= 0) Destroy();
}

void Player::OnDestroy() {}

void Player::Destroy()
{
    OnDestroy();
    isDestroyed = true;
}

int Player::getVelocity() const { return velocity; }

int Player::getHealth() const { return health; }

int Player::getMaxHealth() const { return maxHealth; }