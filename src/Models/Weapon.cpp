#include "Weapon.h"

Weapon::~Weapon() = default;

void Weapon::Draw(SpriteRenderer &renderer)
{
	if (parent == nullptr)
	{
		/*if (this->weaponType == WeaponType::MAIN)
		{
			SetSize(glm::vec2(150.0F, 75.0F));
		}
		else
		{
			SetSize(glm::vec2(75.0F, 75.0F));
		}*/
		renderer.DrawSprite(this->sprites[1], this->localPosition, this->localSize, this->localRotation);
	}
	else if (this->selected)
	{
		SetSize(glm::vec2(75.0F, 75.0F));
		renderer.DrawSprite(this->sprites[0], this->localPosition, this->localSize, this->localRotation);
	}
}

void Weapon::DrawModel(SpriteRenderer &renderer)
{
	if (parent == nullptr)
	{
		/*if (this->weaponType == WeaponType::MAIN)
		{
			SetSize(glm::vec2(150.0F, 75.0F));
		}
		else
		{
			SetSize(glm::vec2(75.0F, 75.0F));
		}*/

		renderer.DrawSprite(this->sprites[1], this->GetTransform());
	}
	else if (this->selected && parent != nullptr)
	{
		renderer.DrawSprite(this->sprites[0], this->GetTransform());
	}
}

void Weapon::Update(float dt)
{
	/*if (parent == nullptr && weaponType == WeaponType::MAIN)
	{
		
	}
	else if (parent != nullptr && weaponType == WeaponType::MAIN)
	{
		//this->SetSize(glm::vec2(InputManager::Height / 20, InputManager::Height / 20));
	}*/
}

void Weapon::SetParent(GameObject *go)
{
	if (parent != nullptr)
	{
		//globalTranform = GetGlobalTransform();
	}
	Logger::WriteLog("Weapon->SetParent()");
	parent = go;
	//localTranform = glm::inverse(parent->GetGlobalTransform()) * globalTranform;
	this->SetSize(glm::vec2(Game_Parameters::SCREEN_HEIGHT / 20, Game_Parameters::SCREEN_HEIGHT / 20));
}
void Weapon::RemoveParent()
{
	if (parent != nullptr)
	{
		Logger::WriteLog("Weapon->RemoveParent()");
		this->parent = nullptr;
		if (weaponType == WeaponType::MAIN)
		{
			this->SetSize(glm::vec2(Game_Parameters::SCREEN_HEIGHT / 10, Game_Parameters::SCREEN_HEIGHT / 20));
		}
		return;
	}
	Logger::WriteLog("Weapon->RemoveParent() -->parent zaten yok");
}