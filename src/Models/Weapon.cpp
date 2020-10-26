#include "Weapon.h"

Weapon::~Weapon() = default;

void Weapon::Draw(SpriteRenderer &renderer)
{
	if (parent == nullptr)
	{
		renderer.DrawSprite(this->sprites[1], this->globalPosition, this->globalSize, this->globalRotation);
	}
	else if (this->selected)
	{

		renderer.DrawSprite(this->sprites[0], this->globalPosition, this->globalSize, this->globalRotation);
	}
	else
	{
		renderer.DrawSprite(this->sprites[1], this->globalPosition, this->globalSize, this->globalRotation);
	}
}

void Weapon::DrawModel(SpriteRenderer &renderer)
{
	if (parent == nullptr)
	{
		renderer.DrawSprite(this->sprites[1], this->GetTransform());
	}
	else if (this->selected && parent != nullptr)
	{
		renderer.DrawSprite(this->sprites[0], this->GetTransform());
	}
	else
	{
		renderer.DrawSprite(this->sprites[1], this->GetTransform());
	}
}

void Weapon::Update(float dt)
{
	/*if (parent == nullptr && weaponType == WeaponType::MAIN)
	{
		
	}
	else if (parent != nullptr && weaponType == WeaponType::MAIN)
	{
		//this->SetSize(Vector2<float>(InputManager::Height / 20, InputManager::Height / 20));
	}*/
}

void Weapon::SetParent(GameObject *go)
{
	if (IsParent())
	{
		return;
	}
	Logger::WriteLog("Weapon->SetParent()");
	parent = go;
	//parentPositionDelta = localPosition - go->GetPosition();
	//localTransform = glm::inverse(parent->GetTransform()) * globalTransform;
	this->SetSize(Vector2<float>(Game_Parameters::SCREEN_HEIGHT / 20, Game_Parameters::SCREEN_HEIGHT / 20));
}
void Weapon::RemoveParent()
{
	if (IsParent())
	{
		Logger::WriteLog("Weapon->RemoveParent()");

		this->parent = nullptr;
		if (weaponType == WeaponType::MAIN)
		{
			this->SetSize(Vector2<float>(Game_Parameters::SIZE_TILE, Game_Parameters::SIZE_TILE));
		}
		return;
	}
	Logger::WriteLog("Weapon->RemoveParent() -->parent zaten yok");
}