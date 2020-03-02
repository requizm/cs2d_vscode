#include "Label.h"
#include <iostream>

Label::Label() = default;

Label::Label(const std::string &text, glm::vec2 position, TextRenderer &renderer, float scale, glm::vec3 color, UIObjectType type) : UIObject(position, scale, renderer, type)
{
	this->labelColor = color;
	this->text = text;
	this->labelMouseHoverColor = glm::vec3(0.78F);
	this->labelClickColor = glm::vec3(1.0F);
	this->labelCurrentColor = color;
	GLfloat x = position.x;
	GLfloat y = position.y;
	this->labelSize = this->rend->CalculateSize(text, scale);
}

Label::Label(glm::vec2 position, TextRenderer &renderer, float scale, glm::vec3 color, UIObjectType type) : UIObject(position, scale, renderer, type)
{
	this->labelColor = color;
	this->labelMouseHoverColor = glm::vec3(0.78F);
	this->labelClickColor = glm::vec3(1.0F);
	this->labelCurrentColor = color;
}

Label::Label(glm::vec2 position, glm::vec2 size, float scale, UIObjectType type) : UIObject(position, size, scale, type)
{
}

Label::~Label() = default;

void Label::Draw()
{
	if (isVisible() && isEnable() && !text.empty())
		this->rend->RenderText(text, getPosition(), scale, labelCurrentColor);
}

void Label::DrawForButton()
{
	if (isVisible() && isEnable() && !text.empty())
		this->rend->RenderText(text, getPositionForButton(), scale, labelCurrentColor);
}

void Label::Update(const float dt)
{
	if (isEnable() && isMouseEvents())
	{
		if (!text.empty())
		{
			if (isMousePress())
			{
				labelCurrentColor = labelClickColor;
			}
			else if (isMouseHover())
			{
				labelCurrentColor = labelMouseHoverColor;
			}
			else
			{
				labelCurrentColor = labelColor;
			}
		}
	}
}

void Label::ProcessInput()
{
	if (isMouseEvents())
	{
		if (isEnable())
		{
			isMouseDownM(GLFW_MOUSE_BUTTON_LEFT);
		}
		isMouseUpM(GLFW_MOUSE_BUTTON_LEFT);
	}
}

std::string Label::getText() const
{
	return this->text;
}

glm::vec2 Label::getLabelSize() const
{
	return this->labelSize;
}

void Label::setText(const std::string &text)
{
	this->text = text;
	this->labelSize = rend->CalculateSize(text, scale);
}

bool Label::isMouseHover()
{
	return isMouseHoverM();
	//return isHover;
}

bool Label::isMouseDown()
{
	//return isMouseDownM(key);
	return isDown;
}

bool Label::isMouseUp()
{
	//return isMouseUpM(key);
	return isUp;
}

bool Label::isMousePress()
{
	return isMousePressM(GLFW_MOUSE_BUTTON_LEFT);
	//return isPress;
}

glm::vec2 Label::getPositionForButton()
{
	if (isParent())
	{
		if (objType == UIObjectType::BUTTON)
		{
			glm::vec2 dif = getSize() - getLabelSize(); dif.x /= 2; dif.y /=2;
			return parent->getPosition() + this->position + dif;
		}
		return parent->getPosition() + this->position;
	}
	if (objType == UIObjectType::BUTTON)
	{
		glm::vec2 dif = getSize() - getLabelSize(); dif.x /= 2; dif.y /=2;
		return this->position + dif;
	}
	return this->position;
}

glm::vec3 Label::getLabelColor() const
{
	return this->labelColor;
}

glm::vec3 Label::getLabelMouseHoverColor() const
{
	return this->labelMouseHoverColor;
}

glm::vec3 Label::getLabelClickColor() const
{
	return this->labelClickColor;
}

void Label::setLabelColor(const glm::vec3 color)
{
	this->labelColor = color;
}

void Label::setLabelMouseHoverColor(const glm::vec3 color)
{
	this->labelMouseHoverColor = color;
}

void Label::setLabelClickColor(const glm::vec3 color)
{
	this->labelClickColor = color;
}

void Label::SimulateUp()
{
	this->isDown = false;
}

bool Label::isMouseHoverM()
{
	const int posX = static_cast<int>(this->getPosition().x);
	const int posY = static_cast<int>(this->getPosition().y);

	const int labelSizeX = static_cast<int>(this->labelSize.x);
	const int labelSizeY = static_cast<int>(this->labelSize.y);

	if (InputManager::mousePos.x >= posX && InputManager::mousePos.x <= posX + labelSizeX && InputManager::mousePos.y >= posY && InputManager::mousePos.y <= posY + labelSizeY)
	{
		return true;
	}
	return false;
}

bool Label::isMouseDownM(const int key)
{
	if (isPressed && isDown)
	{
		isDown = false;
		return false;
	}
	if (InputManager::isButtonDown(key) && isMouseHover())
	{
		isPressed = true;
		isDown = true;
		return true;
	}
	return false;
}

bool Label::isMouseUpM(const int key)
{
	if (InputManager::isButtonUp(key) && isPressed)
	{
		isPressed = false;
		isUp = true;
		return true;
	}
	if (isUp)
		isUp = false;
	return false;
}

bool Label::isMousePressM(const int key)
{
	if (isMouseHover() && InputManager::isButton(key))
	{
		return true;
	}
	return false;
}

void Label::SetMouseState(bool &variable, bool value)
{
	variable = value;
}