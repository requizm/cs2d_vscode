#include "Player.hpp"

#define PI 3.14159265

void Player::Draw(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->sprites[currentIndex], this->globalPosition, this->globalSize, this->globalRotation);
}

void Player::DrawModel(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->sprites[currentIndex], this->GetTransform());
}

Player::~Player() = default;

void Player::Update()
{
	if (lastMousePos != InputManager::mousePos)
	{
		const int komsu = static_cast<int>(InputManager::mousePos.x) - Game_Parameters::SCREEN_WIDTH / 2;
		const int karsi = static_cast<int>(InputManager::mousePos.y) - Game_Parameters::SCREEN_HEIGHT / 2;
		const float atan = atan2(static_cast<float>(karsi), static_cast<float>(komsu)) * 180.0F / static_cast<float>(PI);
		SetRotation(atan + 90.0F);
		lastMousePos = InputManager::mousePos;
	}
}

void Player::ProcessInput(Camera &cam, SpriteRenderer &r, SquareRenderer &s)
{
	ControllerInput(cam, r, s);
	SlotInput();
}

void Player::SetPosition(Vector2<int> pos, bool changeCell)
{
	this->globalPosition = pos;
	this->collider.SetPosition(this->GetPositionOfCenter());
	this->BuildTransform();
	Vector2<int> newCellPos = Utils::PositionToCell(this->GetPositionOfCenter());
	if (newCellPos != cellPos)
	{
		this->cellPos = newCellPos;
		for (auto &weapon : map->weapons)
		{
			if (!weaponLimit[((int)weapon->weaponType)] && !weapon->getSelect() && weapon->GetCellPos() == this->cellPos)
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
					main_weapon = weapon;
					break;
				case WeaponType::PISTOL:
					second_weapon = weapon;
					break;
				}
				break;
			}
		}
	}
}

void Player::SetPosition(Vector2<int> pos, Camera &cam, SpriteRenderer &r, SquareRenderer &s)
{
	this->SetPosition(pos);
	cam.setPosition(Vector2(this->GetPositionOfCenter().x - Game_Parameters::SCREEN_WIDTH / 2, this->GetPositionOfCenter().y - Game_Parameters::SCREEN_HEIGHT / 2));
	r.SetProjection(cam.cameraMatrix);
	s.SetProjection(cam.cameraMatrix);
}

void Player::SetPosition(const int x, const int y, bool changeCell)
{
	Vector2<int> newPos = Vector2<int>(x, y);
	this->SetPosition(newPos, changeCell);
}

void Player::ControllerInput(Camera &cam, SpriteRenderer &r, SquareRenderer &s)
{
	if (InputManager::isKey(KeyboardKeys::KEY_W))
	{
		Vector2<int> newPos = Vector2<int>(this->GetPosition().x, this->GetPosition().y - this->velocity * Timer::DeltaTime);
		if (!CheckCollision(newPos, MoveDirection::TOP))
		{
			this->SetPosition(newPos, cam, r, s);
		}
	}
	if (InputManager::isKey(KeyboardKeys::KEY_S))
	{
		Vector2<int> newPos = Vector2<int>(this->GetPosition().x, this->GetPosition().y + this->velocity * Timer::DeltaTime);
		if (!CheckCollision(newPos, MoveDirection::BOTTOM))
		{
			this->SetPosition(newPos, cam, r, s);
		}
	}
	if (InputManager::isKey(KeyboardKeys::KEY_A))
	{
		Vector2<int> newPos = Vector2<int>(this->GetPosition().x - this->velocity * Timer::DeltaTime, this->GetPosition().y);
		if (!CheckCollision(newPos, MoveDirection::LEFT))
		{
			this->SetPosition(newPos, cam, r, s);
		}
	}
	if (InputManager::isKey(KeyboardKeys::KEY_D))
	{
		Vector2<int> newPos = Vector2<int>(this->GetPosition().x + this->velocity * Timer::DeltaTime, this->GetPosition().y);
		if (!CheckCollision(newPos, MoveDirection::RIGHT))
		{
			this->SetPosition(newPos, cam, r, s);
		}
	}
}

bool Player::CheckCollision(Vector2<int> pos, MoveDirection direction)
{
	Tile *newTile;

	Vector2<int> posCenter = Vector2<int>(pos.x + this->GetSize().x / 2, pos.y + this->GetSize().y / 2);
	CircleCollider col = this->collider;
	col.SetPosition(posCenter);

	switch (direction)
	{
	case MoveDirection::RIGHT:
		newTile = map->GetTileByPosition(posCenter.x + this->GetSize().x / 2, posCenter.y - this->GetSize().y / 2);
		if (newTile == nullptr)
			return true;
		if (newTile->getType() == TileTypes::WALL || newTile->getType() == TileTypes::OBSTACLE)
		{
			if (col.Intersect(newTile->getCollider()))
			{
				return true;
			}
		}

		newTile = map->GetTileByPosition(posCenter.x + this->GetSize().x / 2, posCenter.y + this->GetSize().y / 2);
		if (newTile == nullptr)
			return true;
		if (newTile->getType() == TileTypes::WALL || newTile->getType() == TileTypes::OBSTACLE)
		{
			if (col.Intersect(newTile->getCollider()))
			{
				return true;
			}
		}
		break;
	case MoveDirection::LEFT:
		newTile = map->GetTileByPosition(posCenter.x - this->GetSize().x / 2, posCenter.y - this->GetSize().y / 2);
		if (newTile == nullptr)
			return true;
		if (newTile->getType() == TileTypes::WALL || newTile->getType() == TileTypes::OBSTACLE)
		{
			if (col.Intersect(newTile->getCollider()))
			{
				return true;
			}
		}
		newTile = map->GetTileByPosition(posCenter.x - this->GetSize().x / 2, posCenter.y + this->GetSize().y / 2);
		if (newTile == nullptr)
			return true;
		if (newTile->getType() == TileTypes::WALL || newTile->getType() == TileTypes::OBSTACLE)
		{
			if (col.Intersect(newTile->getCollider()))
			{
				return true;
			}
		}
		break;
	case MoveDirection::TOP:
		newTile = map->GetTileByPosition(posCenter.x + this->GetSize().x / 2, posCenter.y - this->GetSize().y / 2);
		if (newTile == nullptr)
			return true;
		if (newTile->getType() == TileTypes::WALL || newTile->getType() == TileTypes::OBSTACLE)
		{
			if (col.Intersect(newTile->getCollider()))
			{
				return true;
			}
		}
		newTile = map->GetTileByPosition(posCenter.x - this->GetSize().x / 2, posCenter.y - this->GetSize().y / 2);
		if (newTile == nullptr)
			return true;
		if (newTile->getType() == TileTypes::WALL || newTile->getType() == TileTypes::OBSTACLE)
		{
			if (col.Intersect(newTile->getCollider()))
			{
				return true;
			}
		}
		break;
	case MoveDirection::BOTTOM:
		newTile = map->GetTileByPosition(posCenter.x + this->GetSize().x / 2, posCenter.y + this->GetSize().y / 2);
		if (newTile == nullptr)
			return true;
		if (newTile->getType() == TileTypes::WALL || newTile->getType() == TileTypes::OBSTACLE)
		{
			if (col.Intersect(newTile->getCollider()))
			{
				return true;
			}
		}
		newTile = map->GetTileByPosition(posCenter.x - this->GetSize().x / 2, posCenter.y + this->GetSize().y / 2);
		if (newTile == nullptr)
			return true;
		if (newTile->getType() == TileTypes::WALL || newTile->getType() == TileTypes::OBSTACLE)
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
	if (InputManager::isKeyDown(KeyboardKeys::KEY_G) && selectedWeapon != nullptr)
	{
		selectedWeapon->RemoveParent();
		weaponLimit[((int)selectedWeapon->weaponType)] = false;

		switch (selectedWeapon->weaponType)
		{
		case WeaponType::MAIN:
			main_weapon = nullptr;
			if (second_weapon != nullptr)
			{
				selectedWeapon = second_weapon;
				selectedWeapon->setSelect(true);
			}
			break;
		case WeaponType::PISTOL:
			second_weapon = nullptr;
			if (main_weapon != nullptr)
			{
				selectedWeapon = main_weapon;
				selectedWeapon->setSelect(true);
			}
			break;
		default:
			selectedWeapon = nullptr;
			break;
		}
	}
	else if (InputManager::isKeyDown(KeyboardKeys::KEY_1) && main_weapon != nullptr && selectedWeapon != nullptr && selectedWeapon != main_weapon)
	{
		selectedWeapon->setSelect(false);
		selectedWeapon = main_weapon;
		selectedWeapon->setSelect(true);
	}
	else if (InputManager::isKeyDown(KeyboardKeys::KEY_2) && second_weapon != nullptr && selectedWeapon != nullptr && selectedWeapon != second_weapon)
	{
		selectedWeapon->setSelect(false);
		selectedWeapon = second_weapon;
		selectedWeapon->setSelect(true);
	}
}
void Player::SetMap(Map *map)
{
	//this->map = std::move(map);
	this->map = map;
}

void Player::setVelocity(const int velocity)
{
	this->velocity = velocity;
}

void Player::takeDamage(const int value)
{
	health -= value;
	if (health <= 0)
		Destroy();
}

void Player::OnDestroy()
{
}

void Player::Destroy()
{
	OnDestroy();
	isDestroyed = true;
}

int Player::getVelocity() const
{
	return velocity;
}

int Player::getHealth() const
{
	return health;
}

int Player::getMaxHealth() const
{
	return maxHealth;
}