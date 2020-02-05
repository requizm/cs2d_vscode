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
		//this->SetSize(glm::vec2(InputManager::Height / 20, InputManager::Height / 20));
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
	localTransform = glm::inverse(parent->GetTransform()) * globalTransform;
	this->SetSize(glm::vec2(Game_Parameters::SCREEN_HEIGHT / 20, Game_Parameters::SCREEN_HEIGHT / 20));
}
void Weapon::RemoveParent()
{
	if (IsParent())
	{
		Logger::WriteLog("Weapon->RemoveParent()");

		#pragma region 
	/*	BuildTransform();
		//this->globalTransform = GetTransform();
		double dArray[16] = {0.0};
		double sArray[9] = {0.0};

		glm::mat4 zaa = GetTransform();

		const float *pSource = (const float *)glm::value_ptr(GetTransform());
		for (int i = 0; i < 16; i++)
			dArray[i] = pSource[i];

		float scalingFactor = static_cast<float>((dArray[0] * dArray[0] + dArray[1] * dArray[1] + dArray[2] * dArray[2]));
		float a[9];
		a[0] = dArray[0];
		a[3] = dArray[4];
		a[6] = dArray[8];
		a[1] = dArray[1];
		a[4] = dArray[5];
		a[7] = dArray[9];
		a[2] = dArray[2];
		a[5] = dArray[6];
		a[8] = dArray[10];
		glm::mat3 b = glm::make_mat3(a);
		glm::mat3 rotationMatrix = (1.0f / scalingFactor) * b;
		const float *sSource = (const float *)glm::value_ptr(rotationMatrix);
		for (int i = 0; i < 9; i++)
			sArray[i] = sSource[i];

		//Logger::DebugLog(std::to_string(scalingFactor));
		float sy = sqrt(sArray[5] * sArray[5] + sArray[8] * sArray[8]);
		bool singular = sy < 1e-6; // If

		float x, y, z;
		//	if (!singular)
		//	{
		x = atan2(sArray[5], sArray[8]);
		y = atan2(sArray[2] * -1, sy);
		z = atan2(sArray[1], sArray[0]);
		//	}
		//	else
		//	{
		//		x = atan2(sArray[5] * -1, sArray[4]);
		//		y = atan2(sArray[6] * -1, sy);
		//		z = 0;
		//	}

		float rot = glm::degrees(z);*/
		

		
		//this->SetPosition(dArray[12], dArray[13]);
		//this->SetRotation(rot);
		#pragma endregion
		
		this->parent = nullptr;
		if (weaponType == WeaponType::MAIN)
		{
			this->SetSize(glm::vec2(Game_Parameters::SIZE_TILE, Game_Parameters::SIZE_TILE));
		}
		return;
	}
	Logger::WriteLog("Weapon->RemoveParent() -->parent zaten yok");
}