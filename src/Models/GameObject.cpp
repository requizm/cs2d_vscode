#include "GameObject.hpp"

GameObject::GameObject()
	: globalPosition(0, 0), globalSize(1, 1), globalRotation(0.0F), isCollision(false), isDestroyed(false), localRotation(0), localPosition(0, 0), localSize(1, 1), objType(ObjectType::GAMEOBJECT)
{
	this->setID(Utils::GenerateID());
}

GameObject::GameObject(Vector2<int> pos, const Sprite &sprite, Vector2<int> size, int objType)
	: globalPosition(pos), globalSize(size), globalRotation(0), sprite(sprite), isCollision(false), isDestroyed(false), localRotation(0), localPosition(pos)
{
	this->objType = (ObjectType)objType;
	this->setID(Utils::GenerateID());
	BuildTransform();
}

GameObject::~GameObject() = default;

void GameObject::Draw(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->sprite, this->globalPosition, this->globalSize, this->globalRotation);
}

void GameObject::DrawModel(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->sprite, this->GetTransform());
}

void GameObject::BuildTransform()
{
	Matrix4 model = Matrix4(1.0F);
	model = Projection::translate(model, Vector3(static_cast<float>(globalPosition.x), static_cast<float>(globalPosition.y), 0.0F));
	model = Projection::translate(model, Vector3(0.5F * static_cast<float>(globalSize.x), 0.5F * static_cast<float>(globalSize.y), 0.0F));	 // Move origin of rotation to center of quad
	model = Projection::rotate(model, Projection::radians(static_cast<float>(globalRotation)), Vector3(0.0F, 0.0F, 1.0F));					 // Then rotate
	model = Projection::translate(model, Vector3(-0.5F * static_cast<float>(globalSize.x), -0.5F * static_cast<float>(globalSize.y), 0.0F)); // Move origin back
	model = Projection::scale(model, Vector3(static_cast<float>(globalSize.x), static_cast<float>(globalSize.y), 1.0F));
	SetTransform(model);
}

Matrix4<float> GameObject::GetTransform()
{
	if (IsParent())
	{
		return parent->GetTransform() * localTransform;
	}
	return globalTransform;
}

Vector2<int> GameObject::GetPosition()
{
	return globalPosition;
}

Vector2<int> GameObject::GetPositionOfCenter()
{
	return Vector2<int>(GetPosition().x + GetSize().x / 2, GetPosition().y + GetSize().y / 2);
}

Vector2<int> GameObject::GetSize()
{
	return globalSize;
}

void GameObject::SetTransform(const Matrix4<float> &transform)
{
	if (IsParent())
	{
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
		return;
	}
	globalTransform = transform;
}

void GameObject::SetParent(GameObject *go)
{
	if (IsParent())
	{
		//globalTransform = GetTransform();
	}
	parent = go;
	//parentPositionDelta = localPosition - go->GetPosition();
	//localTransform = glm::inverse(parent->GetTransform()) * globalTransform;
}

void GameObject::RemoveParent()
{
	if (IsParent())
	{
		this->parent = nullptr;
		return;
	}
}

void GameObject::setID(int id)
{
	this->id = id;
}

void GameObject::SetTransform(Vector2<int> pos, Vector2<int> size, int rot)
{
	this->globalSize = size;
	this->globalRotation = rot;
	SetPosition(pos);
}

void GameObject::SetPosition(const Vector2<int> pos)
{
	this->globalPosition = pos;
	//localPosition = pos;
	BuildTransform();
}

void GameObject::SetPosition(const int x, const int y)
{
	this->globalPosition = Vector2<int>(x, y);
	/*localPosition.x = x;
	localPosition.y = y;*/
	BuildTransform();
}

void GameObject::SetSize(Vector2<int> size)
{
	this->globalSize = size;
	BuildTransform();
}

void GameObject::SetRotation(int rot)
{
	this->globalRotation = rot;
	BuildTransform();
}

void GameObject::setCellPosition(int x, int y)
{
	SetPosition(x * Game_Parameters::SIZE_TILE, y * Game_Parameters::SIZE_TILE);
}
void GameObject::setCellPosition(Vector2<int> pos)
{
	SetPosition(pos.x * Game_Parameters::SIZE_TILE, pos.y * Game_Parameters::SIZE_TILE);
}

GameObject *GameObject::GetParent()
{
	return parent;
}

int GameObject::GetObjectType()
{
	return (int)this->objType;
}

void GameObject::Destroy()
{
	OnDestroy();
	isDestroyed = true;
}

void GameObject::OnDestroy()
{
}

GLboolean GameObject::IsDestroyed() const
{
	return isDestroyed;
}

int GameObject::GetID() const
{
	return this->id;
}

bool GameObject::IsParent()
{
	bool returnn;
	if (parent != nullptr)
	{
		returnn = true;
	}
	else
	{
		returnn = false;
	}
	return returnn;
}

GLboolean GameObject::IsCollision() const
{
	return isCollision;
}

std::string GameObject::GetObjectTypeString()
{
	std::string str;
	switch ((int)this->objType)
	{
	case 0:
		str = "Player";
		break;
	case 1:
		str = "Weapon";
		break;
	case 2:
		str = "GameObject";
		break;
	case 3:
		str = "Tile";
		break;
	default:
		str = "Bilinmeyen";
		break;
	}
	return str;
}