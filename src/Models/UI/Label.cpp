#include "Label.h"
#include <iostream>

Label::Label() = default;

Label::Label(const std::string &text, Vector2<float> position, float scale, Vector3<float> color, UIObjectType type) : UIObject(position, scale, type), labelSize(Vector2<float>(1.0F))
{
	this->labelColor = color;
	this->text = text;
	this->labelMouseHoverColor = Vector3<float>(0.78F);
	this->labelClickColor = Vector3<float>(1.0F);
	this->labelCurrentColor = color;
	//this->labelSize = this->rend->CalculateSize(text, scale);
} //simdilik kullanilmiyor(muhtemelen hic kullanilmayacak)

Label::Label(const std::string &text, Vector2<float> position, TextRenderer &renderer, float scale, Vector3<float> color, UIObjectType type) : UIObject(position, scale, renderer, type), labelSize(Vector2<float>(1.0F))
{
	this->labelColor = color;
	this->text = text;
	this->labelMouseHoverColor = Vector3<float>(0.78F);
	this->labelClickColor = Vector3<float>(1.0F);
	this->labelCurrentColor = color;
	this->labelSize = this->rend->CalculateSize(text, scale);
}

Label::Label(Vector2<float> position, TextRenderer &renderer, float scale, Vector3<float> color, UIObjectType type) : UIObject(position, scale, renderer, type), labelSize(Vector2<float>(1.0F))
{
	this->labelColor = color;
	this->labelMouseHoverColor = Vector3<float>(0.78F);
	this->labelClickColor = Vector3<float>(1.0F);
	this->labelCurrentColor = color;
}

Label::Label(Vector2<float> position, Vector2<float> size, float scale, UIObjectType type) : UIObject(position, size, scale, type)
{
}

Label::~Label() = default;

void Label::Draw()
{
	if (isVisible() && isEnable() && !text.empty())
		this->rend->RenderText(text, getPosition(), scale, labelCurrentColor);
}

void Label::DrawForButton(const bool center)
{
	if (isVisible() && isEnable() && !text.empty())
		this->rend->RenderText(text, getPositionForButton(center), scale, labelCurrentColor);
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
		isMouseDownM(GLFW_MOUSE_BUTTON_LEFT);
		isMouseUpM(GLFW_MOUSE_BUTTON_LEFT);
	}
}

std::string Label::getText() const
{
	return this->text;
}

Vector2<float> Label::getLabelSize() const
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

Vector2<float> Label::getPositionForButton(const bool center)
{
	if (isParent())
	{
		if (objType == UIObjectType::BUTTON)
		{
			Vector2<float> dif = getSize() - getLabelSize();
			dif.y /= 2;
			if (center)
			{
				dif.x /= 2;
				return parent->getPosition() + this->position + dif;
			}
			return parent->getPosition() + this->position + Vector2<float>(0.0F, dif.y);
		}
		return parent->getPosition() + this->position;
	}
	if (objType == UIObjectType::BUTTON)
	{
		Vector2<float> dif = getSize() - getLabelSize();
		dif.y /= 2;
		if (center)
		{
			dif.x /= 2;
		}
		return this->position + dif;
	}
	return this->position;
}

Vector3<float> Label::getLabelColor() const
{
	return this->labelColor;
}

Vector3<float> Label::getLabelMouseHoverColor() const
{
	return this->labelMouseHoverColor;
}

Vector3<float> Label::getLabelClickColor() const
{
	return this->labelClickColor;
}

void Label::setLabelColor(const Vector3<float> color)
{
	this->labelColor = color;
}

void Label::setLabelMouseHoverColor(const Vector3<float> color)
{
	this->labelMouseHoverColor = color;
}

void Label::setLabelClickColor(const Vector3<float> color)
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