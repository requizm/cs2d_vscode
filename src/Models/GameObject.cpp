#include "GameObject.h"
#include <glm/gtx/string_cast.hpp>
#include "../Others/Logger.h"
#include "../Others/Game_Parameters.h"
#include "../Others/Utils.h"

GameObject::GameObject()
	: globalPosition(0, 0), globalSize(1, 1), globalRotation(0.0F), isCollision(false), isDestroyed(false), localRotation(0.0F), localPosition(0, 0), localSize(1, 1), objType(ObjectType::GAMEOBJECT) 
	{
		this->setID(Utils::GenerateID());
	}

GameObject::GameObject(glm::vec2 pos, const Sprite &sprite, glm::vec2 size, int objType)
	: globalPosition(pos), globalSize(size), globalRotation(0.0F), sprite(sprite), isCollision(false), isDestroyed(false), localRotation(0.0F)
{
	this->objType = (ObjectType)objType;
	this->setID(Utils::GenerateID());
	BuildTransform();
	//Logger::WriteLog("" + GetObjectTypeString() + " olusturuldu");
}

GameObject::~GameObject() = default;

void GameObject::Draw(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->sprite, this->GetPosition(), this->globalSize, this->globalRotation);
}

void GameObject::DrawModel(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->sprite, this->GetTransform());
}

void GameObject::BuildTransform()
{
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(globalPosition, 0.0F));								// First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	model = glm::translate(model, glm::vec3(0.5F * globalSize.x, 0.5F * globalSize.y, 0.0F));   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(globalRotation), glm::vec3(0.0F, 0.0F, 1.0F));		// Then rotate
	model = glm::translate(model, glm::vec3(-0.5F * globalSize.x, -0.5F * globalSize.y, 0.0F)); // Move origin back
	model = glm::scale(model, glm::vec3(globalSize, 1.0F));
	SetTransform(model);
}

glm::mat4 GameObject::GetTransform()
{
	//BuildTransform();
	if (IsParent())
	{
		return parent->GetTransform() * localTransform;
	}
	//Logger::WriteLog("GameObject->GetTransform() " + glm::to_string(localTransform) + "");
	return globalTransform;
}

glm::vec2 GameObject::GetPosition()
{
	return globalPosition;
}

glm::vec2 GameObject::GetSize()
{
	return globalSize;
}

void GameObject::SetTransform(glm::mat4 transform)
{
	if (IsParent())
	{
		localTransform = glm::inverse(parent->GetTransform()) * transform;
		//m_mLocalTransform = parent->GetTransform().InvertedTR() * mGlobal;
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
	localTransform = glm::inverse(parent->GetTransform()) * globalTransform;
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

void GameObject::SetTransform(glm::vec2 pos, glm::vec2 size, GLfloat rot)
{
	this->globalSize = size;
	this->globalRotation = rot;
	SetPosition(pos);
	Logger::WriteLog("" + GetObjectTypeString() + "->SetTransform() ->pos(" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + "), size(" + std::to_string(size.x) + ", " + std::to_string(size.y) + ") rot(" + std::to_string(rot) + ") ");
}

void GameObject::SetPosition(const glm::vec2 pos)
{
	this->globalPosition = pos;
	BuildTransform();
	//Logger::WriteLog("GameObject->SetPosition(" + std::to_string(pos.x) + " " + std::to_string(pos.y) + ")");
}

void GameObject::SetPosition(const float x, const float y)
{
	this->globalPosition.x = x;
	this->globalPosition.y = y;
	BuildTransform();
	//Logger::WriteLog("GameObject->SetPosition(" + std::to_string(x) + ", " + std::to_string(y) + " )");
}

void GameObject::SetSize(glm::vec2 size)
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

glm::vec2 GameObject::PositionToCell(glm::vec2 pos)
{
	glm::vec2 temp = glm::vec2((int)(pos.x / Game_Parameters::SIZE_TILE), (int)(pos.y / Game_Parameters::SIZE_TILE));
	return temp;
}
glm::vec2 GameObject::PositionToCell(float x, float y)
{
	return glm::vec2((int)(x / Game_Parameters::SIZE_TILE), (int)(y / Game_Parameters::SIZE_TILE));
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