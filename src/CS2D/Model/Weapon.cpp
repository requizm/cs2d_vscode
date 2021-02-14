#include "Weapon.hpp"
#include "../Scene/StartGame.hpp"

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
	if (!IsParent() || (selected && IsParent()))
	{
		renderer.DrawSprite(this->sprites[currentIndex], this->GetTransform());
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
	this->SetSize(Vector2<int>(GameParameters::SIZE_TILE, GameParameters::SIZE_TILE));
	SetPosition(go->GetPosition());
	Vector2<int> dif = Utils::ScreenToWorld(StartGame::instance().camera->view, InputManager::mousePos) - this->GetPosition();
	Vector2<float> a = dif.Normalize();
	SetPosition(GetPosition().x + a.x * GameParameters::SIZE_TILE / 4, GetPosition().y + a.y * GameParameters::SIZE_TILE / 4, false);
	parent = go;
	setSelect(true);
	localTransform = Projection::inverse(parent->GetTransform()) * globalTransform;
}
void Weapon::RemoveParent()
{
	if (IsParent())
	{
		Vector2 t = parent->GetPositionOfCenter();
		this->parent = nullptr;
		setCellPosition(Utils::PositionToCell(t));
		setSelect(false);

		if (weaponType == WeaponType::MAIN)
		{
			this->SetSize(Vector2<int>(GameParameters::SIZE_TILE * 2, GameParameters::SIZE_TILE));
			this->SetPosition(GetPosition().x - GameParameters::SIZE_TILE / 2, GetPosition().y, false);
		}
	}
}

void Weapon::setSelect(bool value)
{
	if (value != this->selected)
	{
		this->selected = value;
		if (value)
		{
			//onselect
			if (IsParent())
			{
				currentIndex = 0;
			}
		}
		else
		{
			//ondeselect
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

bool Weapon::getSelect()
{
	return this->selected;
}

bool Weapon::isDropable()
{
	return this->dropable;
}

bool Weapon::isAmmoAndWeapon()
{
	return this->ammoAndWeapon;
}