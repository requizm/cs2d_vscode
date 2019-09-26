#include "GameObject.h"
#include "../Others/Logger.h"
#include <glm/gtx/string_cast.hpp>

GameObject::GameObject()
	: localPosition(0, 0), localSize(1, 1), localRotation(0.0F), isCollision(false), isDestroyed(false) {}

GameObject::GameObject(glm::vec2 pos, Sprite sprite, glm::vec2 size, int objType)
	: localPosition(pos), localSize(size), localRotation(0.0F), sprite(sprite), isCollision(false), isDestroyed(false)
{
	this->objType = (ObjectType)objType;
	BuildTransform();
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
	default:
		str = "Bilinmeyen";
		break;
	}
	str += " olusturuldu";
	Logger::WriteLog(str);
}

GameObject::~GameObject() = default;

void GameObject::Draw(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->sprite, this->localPosition, this->localSize, this->localRotation);
}

void GameObject::DrawModel(SpriteRenderer &renderer)
{
	renderer.DrawSprite(this->sprite, this->GetTransform());
}

void GameObject::BuildTransform()
{
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(localPosition, 0.0F)); // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
	//model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
	model = glm::translate(model, glm::vec3(0.5F * localSize.x, 0.5F * localSize.y, 0.0F));   // Move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(localRotation), glm::vec3(0.0F, 0.0F, 1.0F));	 // Then rotate
	model = glm::translate(model, glm::vec3(-0.5F * localSize.x, -0.5F * localSize.y, 0.0F)); // Move origin back
	model = glm::scale(model, glm::vec3(localSize, 1.0F));									  // Last scale

	SetTransform(model);
}

glm::mat4 GameObject::GetTransform()
{
	//Logger::WriteLog("GameObject->GetTransform() " + glm::to_string(localTranform) + "");
	return localTranform;
}

glm::vec2 GameObject::GetPosition() const
{
	//Logger::WriteLog("GameObject->GetPosition() " + glm::to_string(localPosition) + " ");
	return localPosition;
}

void GameObject::SetTransform(glm::mat4 transform)
{
	/*if (parent != nullptr)
	{
		//localTranform = glm::inverse(parent->GetTransform()) * transform;
		//m_mLocalTransform = parent->GetGlobalTransform().InvertedTR() * mGlobal;
		//globalTranform = transform;
		return;
	}*/
	//Logger::WriteLog("GameObject->SetTransform() " + glm::to_string(transform) + "");
	localTranform = transform;
}

void GameObject::SetParent(GameObject *go)
{
	if (parent != nullptr)
	{
		//globalTranform = GetGlobalTransform();
	}
	Logger::WriteLog("GameObject->SetParent()");
	parent = go;
	//localTranform = glm::inverse(parent->GetGlobalTransform()) * globalTranform;
}

void GameObject::RemoveParent()
{
	if (parent != nullptr)
	{
		Logger::WriteLog("GameObject->RemoveParent()");
		this->parent = nullptr;
		return;
	}
	Logger::WriteLog("GameObject->RemoveParent() -->parent zaten yok");
}

void GameObject::SetTransform(glm::vec2 pos, glm::vec2 size, GLfloat rot)
{
	this->localSize = size;
	this->localRotation = rot;
	SetPosition(pos);
	Logger::WriteLog("GameObject->SetTransform() ->pos(" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + "), size(" + std::to_string(size.x) + ", " + std::to_string(size.y) + ") rot(" + std::to_string(rot) + ") ");
}

void GameObject::SetPosition(const glm::vec2 pos)
{
	this->localPosition = pos;
	BuildTransform();
	//Logger::WriteLog("GameObject->SetPosition(" + std::to_string(pos.x) + " " + std::to_string(pos.y) + ")");
}

void GameObject::SetPosition(const float x, const float y)
{
	this->localPosition.x = x;
	this->localPosition.y = y;
	BuildTransform();
	//Logger::WriteLog("GameObject->SetPosition(" + std::to_string(x) + ", " + std::to_string(y) + " )");
}

void GameObject::SetSize(glm::vec2 size)
{
	this->localSize = size;
	BuildTransform();
	Logger::WriteLog("GameObject->SetSize(" + std::to_string(size.x) + ", " + std::to_string(size.y) + ")");
}

void GameObject::SetRotation(GLfloat rot)
{
	this->localRotation = rot;
	BuildTransform();
	//Logger::WriteLog("GameObject->SetRotation(" + std::to_string(rot) + ")");
}

GameObject GameObject::GetParentObject() const
{
	Logger::WriteLog("GameObject->SetRotation()");
	return *parent;
}

int GameObject::GetObjectType() const
{
	Logger::WriteLog("GameObject->GetObjectType()");
	return (int)this->objType;
}

void GameObject::Destroy()
{
	Logger::WriteLog("GameObject->Destroy()");
	OnDestroy();
	isDestroyed = true;
}

void GameObject::OnDestroy()
{
	Logger::WriteLog("GameObject->OnDestroy()");
}

GLboolean GameObject::IsDestroyed() const
{
	//Logger::WriteLog("GameObject->IsDestroyed() " + std::to_string(isDestroyed) + "");
	return isDestroyed;
}

GLboolean GameObject::IsParent() const
{
	bool returnn;
	if (parent)
		returnn = true;
	returnn = false;
	Logger::WriteLog("GameObject->IsParent() " + std::to_string(returnn) + "");
	return returnn;
}

GLboolean GameObject::IsCollision() const
{
	//Logger::WriteLog("GameObject->IsCollision() " + std::to_string(isCollision) + "");
	return isCollision;
}