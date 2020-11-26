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

void Weapon::Update()
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
	SetPosition(go->GetPositionOfCenter());
	SetPosition(GetPosition().x - Game_Parameters::SIZE_TILE, GetPosition().y - Game_Parameters::SIZE_TILE / 2);
	parent = go;
	selected = true;
	localTransform = Projection::inverse(parent->GetTransform()) * globalTransform;
	/*glm::mat4 temp = glm::inverse(glm::make_mat4(parent->GetTransform().values)) * glm::make_mat4(globalTransform.values);
	localTransform.values[0] = temp[0][0];
	localTransform.values[1] = temp[0][1];
	localTransform.values[2] = temp[0][2];
	localTransform.values[3] = temp[0][3];
	localTransform.values[4] = temp[1][0];
	localTransform.values[5] = temp[1][1];
	localTransform.values[6] = temp[1][2];
	localTransform.values[7] = temp[1][3];
	localTransform.values[8] = temp[2][0];
	localTransform.values[9] = temp[2][1];
	localTransform.values[10] = temp[2][2];
	localTransform.values[11] = temp[2][3];
	localTransform.values[12] = temp[3][0];
	localTransform.values[13] = temp[3][1];
	localTransform.values[14] = temp[3][2];
	localTransform.values[15] = temp[3][3];*/

	/*Matrix4<float> test = Projection::inverse(parent->GetTransform()) * globalTransform;
	if(test == localTransform)
	{
		Logger::DebugLog("za");
	}*/

	//parentPositionDelta = localPosition - go->GetPosition();
	//localTransform = glm::inverse(parent->GetTransform()) * globalTransform;
	//this->SetSize(Vector2<float>(Game_Parameters::SCREEN_HEIGHT / 20, Game_Parameters::SCREEN_HEIGHT / 20));
}
void Weapon::RemoveParent()
{
	if (IsParent())
	{
		Logger::WriteLog("Weapon->RemoveParent()");
		Vector2 t = parent->GetPositionOfCenter();
		this->parent = nullptr;
		setCellPosition(PositionToCell(t));
		this->SetPosition(GetPosition().x - Game_Parameters::SIZE_TILE / 2, GetPosition().y);

		/*if (weaponType == WeaponType::MAIN)
		{
			this->SetSize(Vector2<float>(Game_Parameters::SIZE_TILE, Game_Parameters::SIZE_TILE));
		}*/
		return;
	}
	Logger::WriteLog("Weapon->RemoveParent() -->parent zaten yok");
}