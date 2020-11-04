#include "GameObject.h"
#include <glm/gtx/string_cast.hpp>
#include "../Others/Logger.h"
#include "../Others/Game_Parameters.h"
#include "../Others/Utils.h"

GameObject::GameObject()
	: globalPosition(0.0F, 0.0F), globalSize(1, 1), globalRotation(0.0F), isCollision(false), isDestroyed(false), localRotation(0.0F), localPosition(0, 0), localSize(1, 1), objType(ObjectType::GAMEOBJECT)
{
	this->setID(Utils::GenerateID());
}

GameObject::GameObject(Vector2<float> pos, const Sprite &sprite, Vector2<float> size, int objType)
	: globalPosition(pos), globalSize(size), globalRotation(0.0F), sprite(sprite), isCollision(false), isDestroyed(false), localRotation(0.0F), localPosition(pos)
{
	this->objType = (ObjectType)objType;
	this->setID(Utils::GenerateID());
	BuildTransform();
	//Logger::WriteLog("" + GetObjectTypeString() + " olusturuldu");
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
	model = Projection::translate(model, Vector3(globalPosition.x, globalPosition.y, 0.0F));
	model = Projection::translate(model, Vector3(0.5F * globalSize.x, 0.5F * globalSize.y, 0.0F));	   // Move origin of rotation to center of quad
	model = Projection::rotate(model, Projection::radians(globalRotation), Vector3(0.0F, 0.0F, 1.0F)); // Then rotate
	model = Projection::translate(model, Vector3(-0.5F * globalSize.x, -0.5F * globalSize.y, 0.0F));   // Move origin back
	model = Projection::scale(model, Vector3(globalSize.x, globalSize.y, 1.0F));
	SetTransform(model);
}

Matrix4<float> GameObject::GetTransform()
{
	if (IsParent())
	{
		return parent->GetTransform() * localTransform;
	}
	//Logger::WriteLog("GameObject->GetTransform() " + glm::to_string(localTransform) + "");
	return globalTransform;
}

Vector2<float> GameObject::GetPosition()
{
	return globalPosition;
}

Vector2<float> GameObject::GetPositionOfCenter()
{
	return Vector2<float>(GetPosition().x + GetSize().x / 2, GetPosition().y + GetSize().y / 2);
}

Vector2<float> GameObject::GetSize()
{
	return globalSize;
}

void GameObject::SetTransform(Matrix4<float> transform)
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
	//Logger::WriteLog("GameObject->SetTransform() " + glm::to_string(transform) + "");
	globalTransform = transform;
}

void GameObject::SetParent(GameObject *go)
{
	if (IsParent())
	{
		//globalTransform = GetTransform();
	}
	Logger::WriteLog("" + GetObjectTypeString() + "->SetParent()");
	parent = go;
	//parentPositionDelta = localPosition - go->GetPosition();
	//localTransform = glm::inverse(parent->GetTransform()) * globalTransform;
}

void GameObject::RemoveParent()
{
	if (IsParent())
	{
		Logger::WriteLog("" + GetObjectTypeString() + "->RemoveParent()");
		this->parent = nullptr;
		return;
	}
	Logger::WriteLog("" + GetObjectTypeString() + "->RemoveParent() -->parent zaten yok");
}

void GameObject::setID(int id)
{
	this->id = id;
}

void GameObject::SetTransform(Vector2<float> pos, Vector2<float> size, GLfloat rot)
{
	this->globalSize = size;
	this->globalRotation = rot;
	SetPosition(pos);
	Logger::WriteLog("" + GetObjectTypeString() + "->SetTransform() ->pos(" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + "), size(" + std::to_string(size.x) + ", " + std::to_string(size.y) + ") rot(" + std::to_string(rot) + ") ");
}

void GameObject::SetPosition(const Vector2<float> pos)
{
	this->globalPosition = pos;
	//localPosition = pos;
	BuildTransform();
	//Logger::WriteLog("GameObject->SetPosition(" + std::to_string(pos.x) + " " + std::to_string(pos.y) + ")");
}

void GameObject::SetPosition(const float x, const float y)
{
	this->globalPosition = Vector2<float>(x, y);
	/*localPosition.x = x;
	localPosition.y = y;*/
	BuildTransform();
	//Logger::WriteLog("GameObject->SetPosition(" + std::to_string(x) + ", " + std::to_string(y) + " )");
}

void GameObject::SetSize(Vector2<float> size)
{
	this->globalSize = size;
	BuildTransform();
	Logger::WriteLog("" + GetObjectTypeString() + "->SetSize(" + std::to_string(size.x) + ", " + std::to_string(size.y) + ")");
}

void GameObject::SetRotation(GLfloat rot)
{
	this->globalRotation = rot;
	BuildTransform();
	//Logger::WriteLog("GameObject->SetRotation(" + std::to_string(rot) + ")");
}

void GameObject::setCellPosition(int x, int y)
{
	SetPosition(x * Game_Parameters::SIZE_TILE, y * Game_Parameters::SIZE_TILE);
}
void GameObject::setCellPosition(Vector2<int> pos)
{
	SetPosition(pos.x * Game_Parameters::SIZE_TILE, pos.y * Game_Parameters::SIZE_TILE);
}

GameObject GameObject::GetParentObject()
{
	Logger::WriteLog("" + GetObjectTypeString() + "->GetParentObject()");
	return *parent;
}

int GameObject::GetObjectType()
{
	Logger::WriteLog("" + GetObjectTypeString() + "->GetObjectType()");
	return (int)this->objType;
}

void GameObject::Destroy()
{
	Logger::WriteLog("" + GetObjectTypeString() + "->Destroy()");
	OnDestroy();
	isDestroyed = true;
}

void GameObject::OnDestroy()
{
	Logger::WriteLog("" + GetObjectTypeString() + "->OnDestroy()");
}

GLboolean GameObject::IsDestroyed() const
{
	//Logger::WriteLog("GameObject->IsDestroyed() " + std::to_string(isDestroyed) + "");
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
	//Logger::WriteLog("GameObject->IsParent() " + std::to_string(returnn) + "");
	return returnn;
}

GLboolean GameObject::IsCollision() const
{
	//Logger::WriteLog("GameObject->IsCollision() " + std::to_string(isCollision) + "");
	return isCollision;
}

Vector2<int> GameObject::PositionToCell(Vector2<float> pos)
{
	return Vector2<int>((int)(pos.x / Game_Parameters::SIZE_TILE), (int)(pos.y / Game_Parameters::SIZE_TILE));
}
Vector2<int> GameObject::PositionToCell(float x, float y)
{
	return Vector2<int>((int)(x / Game_Parameters::SIZE_TILE), (int)(y / Game_Parameters::SIZE_TILE));
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