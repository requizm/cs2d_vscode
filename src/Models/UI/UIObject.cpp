#include "UIObject.h"

UIObject::UIObject() = default;

UIObject::UIObject(glm::vec2 position, glm::vec2 size, float scale, TextRenderer &renderer)
{
	this->objType = UIObjectType::UIOBJECT;
	Logger::WriteLog("" + GetObjectTypeString() + "->" + GetObjectTypeString() + "(pos(" + std::to_string(position.x) + "," + std::to_string(position.y) + "), size(" + std::to_string(size.x) + "," + std::to_string(size.y) + "), " + std::to_string(scale) + ", TextRenderer");
	this->position = position;
	this->scale = scale;
	this->size = size;
	this->enable = true;
	this->visible = true;
	this->mouseEvents = true;
	this->rend = &renderer;

	this->scrollable = false;
	this->dependParent = false;
}

UIObject::UIObject(glm::vec2 position, glm::vec2 size, float scale, TextRenderer &renderer, UIObjectType type)
{
	this->objType = type;
	Logger::WriteLog("" + GetObjectTypeString() + "->UIObject(pos(" + std::to_string(position.x) + "," + std::to_string(position.y) + "), size(" + std::to_string(size.x) + "," + std::to_string(size.y) + "), " + std::to_string(scale) + ", TextRenderer");
	this->position = position;
	this->scale = scale;
	this->size = size;
	this->enable = true;
	this->visible = true;
	this->mouseEvents = true;
	this->rend = &renderer;

	this->scrollable = false;
	this->dependParent = false;
}

UIObject::UIObject(glm::vec2 position, glm::vec2 size, float scale)
{
	this->objType = UIObjectType::UIOBJECT;
	Logger::WriteLog("" + GetObjectTypeString() + "->" + GetObjectTypeString() + "(pos(" + std::to_string(position.x) + "," + std::to_string(position.y) + "), size(" + std::to_string(size.x) + "," + std::to_string(size.y) + "), " + std::to_string(scale) + "");
	this->position = position;
	this->scale = scale;
	this->size = size;
	this->enable = true;
	this->visible = true;
	this->mouseEvents = true;

	this->scrollable = false;
	this->dependParent = false;
}

UIObject::UIObject(glm::vec2 position, glm::vec2 size, float scale, UIObjectType type)
{
	this->objType = type;
	Logger::WriteLog("" + GetObjectTypeString() + "->UIObject(pos(" + std::to_string(position.x) + "," + std::to_string(position.y) + "), size(" + std::to_string(size.x) + "," + std::to_string(size.y) + "), " + std::to_string(scale) + "");
	this->position = position;
	this->scale = scale;
	this->size = size;
	this->enable = true;
	this->visible = true;
	this->mouseEvents = true;
	
	this->scrollable = false;
	this->dependParent = false;
}

UIObject::UIObject(glm::vec2 position, float scale, TextRenderer &renderer)
{
	this->objType = UIObjectType::UIOBJECT;
	Logger::WriteLog("" + GetObjectTypeString() + "->" + GetObjectTypeString() + "(pos(" + std::to_string(position.x) + "," + std::to_string(position.y) + ")," + std::to_string(scale) + ", TextRenderer");
	this->position = position;
	this->scale = scale;
	this->enable = true;
	this->visible = true;
	this->mouseEvents = true;
	this->rend = &renderer;

	this->scrollable = false;
	this->dependParent = false;
}

UIObject::UIObject(glm::vec2 position, float scale, TextRenderer &renderer, UIObjectType type)
{
	this->objType = type;
	Logger::WriteLog("" + GetObjectTypeString() + "->UIObject(pos(" + std::to_string(position.x) + "," + std::to_string(position.y) + ")," + std::to_string(scale) + ", TextRenderer");
	this->position = position;
	this->scale = scale;
	this->enable = true;
	this->visible = true;
	this->mouseEvents = true;
	this->rend = &renderer;

	this->scrollable = false;
	this->dependParent = false;
}

UIObject::~UIObject() = default;

bool onenabletrigger = false;
void UIObject::Update(const float dt)
{
}

void UIObject::OnEnable()
{
	Logger::WriteLog("" + GetObjectTypeString() + "->OnEnable()");
}

void UIObject::OnDisable()
{
	Logger::WriteLog("" + GetObjectTypeString() + "->OnDisable()");
}

void UIObject::ProcessInput()
{
	
}

void UIObject::setPosition(const glm::vec2 position)
{
	this->position = position;
}

void UIObject::setPosition(const int x, const int y)
{
	this->position.x = x;
	this->position.y = y;
}

void UIObject::setParentCenterPos()
{
	if (isParent())
		setPosition(parent->getSize().x / 2 - this->getSize().x / 2, parent->getSize().y / 2 - this->getSize().y / 2);
}

void UIObject::setSize(const glm::vec2 size)
{
	this->size = size;
}

void UIObject::setSize(const int x, const int y)
{
	this->size = glm::vec2(x, y);
}

glm::vec2 UIObject::getPosition()
{
	if (isParent())
	{
		return parent->getPosition() + this->position;
	}
	return this->position;
}

glm::vec2 UIObject::getLocalPosition()
{
	if (isParent())
	{
		return this->getPosition() - parent->getPosition();
	}
	return this->position;
}

glm::vec2 UIObject::getSize()
{
	return this->size;
}

glm::vec2 UIObject::getCenterPosition() const
{
	return glm::vec2(this->position.x + this->size.x / 2, this->position.y + this->size.y / 2);
}

UIObject UIObject::getParent() const
{
	if (isParent())
		return *parent;
	//no parent
}

void UIObject::setScale(const float scale)
{
	this->scale = scale;
}

void UIObject::setParent(UIObject *uiobject, bool dependParent)
{
	this->dependParent = dependParent;
	this->parent = uiobject;
}

void UIObject::removeParent()
{
	this->parent = nullptr;
}

void UIObject::setVisible(const bool value)
{
	this->visible = value;
}

void UIObject::setEnable(const bool value)
{
	if (enable == value)
		return;
	this->enable = value;
	if (value)
		OnEnable();
	else
		OnDisable();
}

void UIObject::setMouseEvent(const bool value)
{
	this->mouseEvents = value;
}

void UIObject::setDependParent(const bool value)
{
	this->dependParent = value;
}

float UIObject::getScale() const
{
	return this->scale;
}

bool UIObject::isParent() const
{
	return this->parent != nullptr;
}

bool UIObject::isVisible() const
{
	if (this->isParent() && dependParent)
	{
		return parent->isVisible() && this->visible;
	}
	return this->visible;
}

bool UIObject::isEnable() const
{
	if (this->isParent() && dependParent)
	{
		return parent->isEnable() && this->enable;
	}
	return this->enable;
}

bool UIObject::isMouseEvents() const
{
	if (this->isParent() && dependParent)
	{
		return parent->isMouseEvents() && this->mouseEvents;
	}
	return this->mouseEvents;
}

bool UIObject::isDependParent() const
{
	return this->dependParent;
}

int UIObject::getID() const
{
	return this->id;
}

bool UIObject::isRenderable()
{
	if (this->isParent())
	{
		UIObject p = this->getParent();
		if (p.isScrollable())
		{
			if ((getLocalPosition().y + getSize().y <= p.getSize().y) && getLocalPosition().y >= 0)
			{
				return true;
			}
			return false;
		}
		return true;
	}
	return true;
}

bool UIObject::isScrollable() const
{
	return this->scrollable;
}

void UIObject::setID(const int value)
{
	this->id = value;
}

std::string UIObject::GetObjectTypeString()
{
	std::string str;
	switch ((int)this->objType)
	{
	case 0:
		str = "UIObject";
		break;
	case 1:
		str = "Label";
		break;
	case 2:
		str = "TextBox";
		break;
	case 3:
		str = "Button";
		break;
	case 4:
		str = "Panel";
		break;
	default:
		str = "Bilinmeyen";
		break;
	}
	return str;
}

void UIObject::setScrollable(const bool value)
{
	this->scrollable = value;
}