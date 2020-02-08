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

bool Label::isMouseHover()
{
	return isMouseHoverM();
	//return isHover;
}

bool Label::isMouseDown(const int key)
{
	return isMouseDownM(key);
	//return isDown;
}

bool Label::isMouseUp(const int key) //refactor: neden beraber degiller
{
	return isMouseUpM(key);
	//return isUp;
}

bool Label::isMousePress(const int key)
{
	return isMousePressM(key);
	//return isPress;
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

bool Label::isMouseHoverM()
{
	const int posX = static_cast<int>(this->getPosition().x);
	const int posY = static_cast<int>(this->getPosition().y);

	const int labelSizeX = static_cast<int>(this->labelSize.x);
	const int labelSizeY = static_cast<int>(this->labelSize.y);

	if (InputManager::mouseX >= posX && InputManager::mouseX <= posX + labelSizeX && InputManager::mouseY >= posY && InputManager::mouseY <= posY + labelSizeY)
	{
		//SetMouseState(isHover, true);
		//isHover = true;
		//labelCurrentColor = labelMouseHoverColor;
		return true;
	}
	//SetMouseState(isHover, false);
	//isHover = false;
	//labelCurrentColor = labelColor;
	return false;
}

bool Label::isMouseDownM(const int key)
{
	if (!isDown)
	{
		if (InputManager::isButtonDown(key))
		{
			if (isMouseHover())
			{
				isDown = true;
				isDownForClick = true;
				//isUp = false;
				//SetMouseState(isDown, true);
				//SetMouseState(isUp, false);
				//InputManager::mouseDownTrigger[key] = GL_TRUE;
				return true;
			}

			isDown = true;
			isDownForClick = false;
			InputManager::mouseDownTrigger[key] = GL_TRUE;
		}
	}
	//InputManager::mouseDownTrigger[key] = GL_TRUE;
	return false;
}

bool Label::isMouseUpM(const int key)
{
	if (isDown && isDownForClick)
	{
		if (InputManager::isButtonUp(key))
		{
			isDown = false;
			isDownForClick = false;
			//isUp = true;
			//isPress = false;
			//SetMouseState(isDown, false);
			//SetMouseState(isUp, true);
			//SetMouseState(isPress, false);
			//labelCurrentColor = labelColor;
			return true;
		}
	}

	else if (InputManager::isButtonUp(key))
	{
		if (isDown && !isDownForClick)
		{
			isDown = false;
			//isUp = true;
			//isPress = false;
			//SetMouseState(isDown, false);
			//SetMouseState(isUp, true);
			//SetMouseState(isPress, false);
			//labelCurrentColor = labelColor;
		}
		InputManager::mouseUpTrigger[key] = GL_TRUE;
	}
	//InputManager::mouseUpTrigger[key] = GL_TRUE;
	return false;
}

bool Label::isMousePressM(const int key)
{
	if (isMouseHover() && InputManager::isButton(key))
	{
		//isPress = true;
		//SetMouseState(isPress, true);
		//labelCurrentColor = labelClickColor;
		return true;
	}
	return false;
}

void Label::SetMouseState(bool &variable, bool value)
{
	variable = value;
}