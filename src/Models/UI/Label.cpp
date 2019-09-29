#include "Label.h"
#include <iostream>

Label::Label() = default;

Label::Label(const std::string &text, glm::vec2 position, TextRenderer &renderer, float scale, glm::vec3 color) : UIObject(position, scale, renderer, UIObjectType::LABEL)
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

Label::Label(glm::vec2 position, TextRenderer &renderer, float scale, glm::vec3 color) : UIObject(position, scale, renderer, UIObjectType::LABEL)
{
	this->labelColor = color;
	this->labelMouseHoverColor = glm::vec3(0.78F);
	this->labelClickColor = glm::vec3(1.0F);
	this->labelCurrentColor = color;
}

Label::Label(glm::vec2 position, glm::vec2 size, float scale) : UIObject(position, size, scale, UIObjectType::LABEL)
{
}

Label::~Label() = default;

void Label::Draw() const
{
	if (isVisible() && isEnable() && !text.empty())
		this->rend->RenderText(text, getPosition(), scale, labelCurrentColor);
}

void Label::Update(const float dt)
{
	if (isEnable() && isMouseEvents() && !text.empty())
	{
		if (isMousePress(GLFW_MOUSE_BUTTON_LEFT))
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

bool Label::isMouseHover() const
{
	const int posX = static_cast<int>(this->getPosition().x);
	const int posY = static_cast<int>(this->getPosition().y);

	const int labelSizeX = static_cast<int>(this->labelSize.x);
	const int labelSizeY = static_cast<int>(this->labelSize.y);

	bool ret = false;
	for (int i = posX; i <= posX + labelSizeX; i++)
	{
		for (int j = posY; j <= posY + labelSizeY; j++)
		{
			if (InputManager::mouseX == i && InputManager::mouseY == j)
			{
				ret = true;
				break;
			}
		}
	}
	return ret;
}

bool Label::isMouseDown(const int key)
{
	bool ret = false;
	if (isMouseHover() && InputManager::isButtonDown(key))
	{
		isDown = true;
		ret = true;
	}
	return ret;
}

bool Label::isMouseUp(const int key)
{
	bool ret = false;
	if (InputManager::isButtonUp(key))
	{
		if (isDown)
		{
			isDown = false;
			ret = true;
		}
	}
	return ret;
}

bool Label::isMousePress(const int key) const
{
	bool ret = false;
	if (isMouseHover() && InputManager::isButton(key))
	{
		ret = true;
	}
	return ret;
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