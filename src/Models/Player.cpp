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
		this->SetPosition(Vector2<float>(this->GetPosition().x, this->GetPosition().y - this->velocity * Timer::DeltaTime));
	}
	if (InputManager::isKey(GLFW_KEY_S))
	{
		this->SetPosition(Vector2<float>(this->GetPosition().x, this->GetPosition().y + this->velocity * Timer::DeltaTime));
	}
	if (InputManager::isKey(GLFW_KEY_A))
	{
		this->SetPosition(Vector2<float>(this->GetPosition().x - this->velocity * Timer::DeltaTime, this->GetPosition().y));
	}
	if (InputManager::isKey(GLFW_KEY_D))
	{
		this->SetPosition(Vector2<float>(this->GetPosition().x + this->velocity * Timer::DeltaTime, this->GetPosition().y));
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

void Player::setVelocity(const float velocity)
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

float Player::getVelocity() const
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