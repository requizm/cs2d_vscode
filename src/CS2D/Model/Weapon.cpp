#include "Weapon.hpp"

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
}

void Weapon::SetParent(GameObject *go)
{
	if (IsParent())
	{
		return;
	}
	SetPosition(go->GetPositionOfCenter());
	SetPosition(GetPosition().x - Game_Parameters::SIZE_TILE, GetPosition().y - Game_Parameters::SIZE_TILE / 2);
	parent = go;
	selected = true;
	localTransform = Projection::inverse(parent->GetTransform()) * globalTransform;
}
void Weapon::RemoveParent()
{
	if (IsParent())
	{
		Vector2 t = parent->GetPositionOfCenter();
		this->parent = nullptr;
		setCellPosition(Utils::PositionToCell(t));
		this->SetPosition(GetPosition().x - Game_Parameters::SIZE_TILE / 2, GetPosition().y);

		/*if (weaponType == WeaponType::MAIN)
		{
			this->SetSize(Vector2<int>(Game_Parameters::SIZE_TILE, Game_Parameters::SIZE_TILE));
		}*/
		return;
	}
}