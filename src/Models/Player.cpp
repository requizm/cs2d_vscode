#include "Player.hpp"
#include "../Managers/InputManager.hpp"
#include "../Others/Logger.hpp"
#include "../Others/Timer.hpp"

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

void Player::ProcessInput()
{
	ControllerInput();
	SlotInput();
}

void Player::ControllerInput()
{
	if (InputManager::isKey(GLFW_KEY_W))
	{
		Vector2<int> newPos = Vector2<int>(this->GetPosition().x, this->GetPosition().y - this->velocity * Timer::DeltaTime);
		Tile *newTile = map->GetTileByPosition(Vector2<int>(newPos.x + this->GetSize().x / 2, newPos.y + this->GetSize().y / 2 - this->GetSize().y / 2));
		if (newTile != nullptr)
		{
			TileTypes newType = newTile->getType();
			if (newType == TileTypes::WALL || newType == TileTypes::OBSTACLE)
			{
				int a = 2;
			}
			else
			{
				this->SetPosition(newPos);
			}
		}
	}
	if (InputManager::isKey(GLFW_KEY_S))
	{
		Vector2<int> newPos = Vector2<int>(this->GetPosition().x, this->GetPosition().y + this->velocity * Timer::DeltaTime);
		Tile *newTile = map->GetTileByPosition(Vector2<int>(newPos.x + this->GetSize().x / 2, newPos.y + this->GetSize().y / 2 + this->GetSize().y / 2));
		if (newTile != nullptr)
		{
			TileTypes newType = newTile->getType();
			if (newType == TileTypes::WALL || newType == TileTypes::OBSTACLE)
			{
				int a = 2;
			}
			else
			{
				this->SetPosition(newPos);
			}
		}
	}
	if (InputManager::isKey(GLFW_KEY_A))
	{
		Vector2<int> newPos = Vector2<int>(this->GetPosition().x - this->velocity * Timer::DeltaTime, this->GetPosition().y);
		Tile *newTile = map->GetTileByPosition(Vector2<int>(newPos.x + this->GetSize().x / 2 - this->GetSize().x / 2, newPos.y + this->GetSize().y / 2));
		if (newTile != nullptr)
		{
			TileTypes newType = newTile->getType();
			if (newType == TileTypes::WALL || newType == TileTypes::OBSTACLE)
			{
				int a = 2;
			}
			else
			{
				this->SetPosition(newPos);
			}
		}
	}
	if (InputManager::isKey(GLFW_KEY_D))
	{
		Vector2<int> newPos = Vector2<int>(this->GetPosition().x + this->velocity * Timer::DeltaTime, this->GetPosition().y);
		Tile *newTile = map->GetTileByPosition(Vector2<int>(newPos.x + this->GetSize().x / 2 + this->GetSize().x / 2, newPos.y + this->GetSize().y / 2));

		if (newTile != nullptr)
		{
			TileTypes newType = newTile->getType();
			if (newType == TileTypes::WALL || newType == TileTypes::OBSTACLE)
			{
						}
			else
			{
				this->SetPosition(newPos);
			}
		}
	}
}
void Player::SlotInput()
{
}
void Player::SetMap(Map *map)
{
	Logger::WriteLog("Player->SetMap(" + map->GetName() + ")");
	//this->map = std::move(map);
	this->map = map;
}

void Player::setVelocity(const int velocity)
{
	Logger::WriteLog("Player->SetVelocity(" + std::to_string(velocity) + ")");
	this->velocity = velocity;
}

void Player::takeDamage(const int value)
{
	Logger::WriteLog("Player->takeDamage(" + std::to_string(value) + ")");
	health -= value;
	if (health <= 0)
		Destroy();
}

void Player::OnDestroy()
{
	Logger::WriteLog("Player->OnDestroy()");
}

void Player::Destroy()
{
	Logger::WriteLog("Player->Destroy()");
	OnDestroy();
	isDestroyed = true;
}

int Player::getVelocity() const
{
	Logger::WriteLog("Player->takeDamage(" + std::to_string(velocity) + ")");
	return velocity;
}

int Player::getHealth() const
{
	Logger::WriteLog("Player->getHealth(" + std::to_string(health) + ")");
	return health;
}

int Player::getMaxHealth() const
{
	Logger::WriteLog("Player->getMaxHealth(" + std::to_string(maxHealth) + ")");
	return maxHealth;
}