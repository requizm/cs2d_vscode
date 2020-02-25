#include "Panel.h"
#include <iostream>

Panel::Panel(glm::vec2 position, const std::string &title, glm::vec2 size, TextRenderer &renderer, bool isBackGround, bool opttitles, float scale, glm::vec3 color, float transp) : UIObject(position, size, scale, UIObjectType::PANEL)
{
	this->panelColor = color;
	this->backGround = isBackGround;
	this->dragSize = glm::vec2(size.x, 23.0F);
	this->opttitles = opttitles;
	this->trans = transp;
	this->enable = false;
	this->movable = false;
	this->scrollable = false;
	this->outline = false;
	escapeButton = Button(Sprite(ResourceManager::GetTexture("gui_icons"), 0, 0, 16, 16), position, glm::vec2(20.0F, 20.0F), scale);
	escapeButton.setParent(this);
	escapeButton.setPosition(this->size.x - 20.0F, 3.0F);
	escapeButton.setButtonColor(color);
	escapeButton.setMouseHoverColor(glm::vec3(0.64F));
	escapeButton.setMouseClickColor(glm::vec3(1.0F));
	this->title = Label(title, position, renderer, scale, glm::vec3(1.0F));
	this->title.setParent(this);
	this->title.setPosition(static_cast<int>(lineOffset), 4.0F);
}

Panel::Panel() = default;

Panel::~Panel() = default;

void Panel::Draw(SquareRenderer &squareRenderer, SpriteRenderer &spriteRenderer)
{
	if (isEnable() && isVisible())
	{
		if (this->backGround)
		{
			if (!isOutline())
			{
				squareRenderer.ui_RenderFilledSquare(this->getPosition(), this->getSize(), this->getPanelColor(), this->trans);
			}
			else
			{
				squareRenderer.ui_RenderFilledSquare(this->getPosition(), this->getSize(), getPanelColor(), getOutlineColor(), 2.0F, this->trans, 0.0F);
			}
		}
		if (opttitles)
		{
			squareRenderer.RenderLine(glm::vec2(getPosition().x + lineOffset, getPosition().y + 23.0F), glm::vec2(size.x - 2 * lineOffset, 1.0F), glm::vec3(0.39F), this->trans);
			escapeButton.Draw(spriteRenderer, squareRenderer);
			title.Draw();
		}
	}
}

int deltaX;
int deltaY;
bool click = false;
void Panel::Update(const float dt)
{
	if (isEnable())
	{
		if (isMovable())
		{
			if (!click && (opttitles && !escapeButton.isMousePress(GLFW_MOUSE_BUTTON_LEFT)) || (!opttitles && !click))
			{
				if (isMouseDown(GLFW_MOUSE_BUTTON_LEFT, true))
				{
					deltaX = InputManager::mousePos.x - static_cast<int>(position.x);
					deltaY = InputManager::mousePos.y - static_cast<int>(position.y);
					click = true;
				}
			}
			if (click)
			{
				if (isMouseUp(GLFW_MOUSE_BUTTON_LEFT))
				{
					click = false;
				}

				if (!isMouseUp(GLFW_MOUSE_BUTTON_LEFT))
				{
					glm::vec2 mousePos = glm::vec2(InputManager::mousePos.x, InputManager::mousePos.y);
					this->setPosition(glm::vec2(mousePos.x - static_cast<float>(deltaX), mousePos.y - static_cast<float>(deltaY)));
					//std::cout << "hey" << std::endl;
				}
			}
		}
		if (opttitles)
		{
			escapeButton.Update(dt);
			if (escapeButton.isMouseDown(GLFW_MOUSE_BUTTON_LEFT))
			{
			}
			if (escapeButton.isMouseUp(GLFW_MOUSE_BUTTON_LEFT))
			{
				this->setEnable(false);
			}
		}
		if (!click)
		{
			isMouseUp(GLFW_MOUSE_BUTTON_LEFT);
		}
	}
}

void Panel::OnEnable()
{
	//setPosition(glm::vec2(Game_Parameters::SCREEN_WIDTH / 2 - 210.0F, Game_Parameters::SCREEN_HEIGHT / 2 - 225.0F));
	if (opttitles)
	{
		escapeButton.setEnable(true);
		title.setEnable(true);
		escapeButton.setVisible(true);
		title.setVisible(true);
	}
}

void Panel::OnDisable()
{
	if (opttitles)
	{
		escapeButton.setEnable(false);
		title.setEnable(false);
		escapeButton.setVisible(false);
		title.setVisible(false);
	}
}

bool Panel::isMouseHover(bool drag)
{
	if (!this->isEnable())
	{
		return false;
	}
	if (drag)
		return isMouseHoverForDrag();
	else
		return isMouseHoverForMouse();
}

bool Panel::isMouseDown(const int key, bool drag)
{
	if (!this->isEnable())
	{
		return false;
	}
	if (drag)
		return isMouseDownForDrag(key);
	else
		return isMouseDownForMouse(key);
}

bool Panel::isMouseUp(const int key, bool drag)
{
	return isMouseUp(key);
}

bool Panel::isMousePress(const int key, bool drag)
{
	if (!this->isEnable())
	{
		return false;
	}
	if (drag)
		return isMousePressForDrag(key);
	else
		return isMousePressForMouse(key);
}

bool Panel::isMouseHoverForDrag()
{
	const int posX = static_cast<int>(this->getPosition().x);
	const int posY = static_cast<int>(this->getPosition().y);

	const int sizeX = static_cast<int>(this->dragSize.x);
	const int sizeY = static_cast<int>(this->dragSize.y);

	if (InputManager::mousePos.x >= posX && InputManager::mousePos.x <= posX + sizeX && InputManager::mousePos.y >= posY && InputManager::mousePos.y <= posY + sizeY)
	{
		return true;
	}
	return false;
}

bool Panel::isMouseHoverForMouse()
{
	const int posX = static_cast<int>(this->getPosition().x);
	const int posY = static_cast<int>(this->getPosition().y);

	const int sizeX = static_cast<int>(this->getSize().x);
	const int sizeY = static_cast<int>(this->getSize().y);

	if (InputManager::mousePos.x >= posX && InputManager::mousePos.x <= posX + sizeX && InputManager::mousePos.y >= posY && InputManager::mousePos.y <= posY + sizeY)
	{
		return true;
	}
	return false;
}

bool Panel::isMouseDownForDrag(const int key)
{
	if (!isDown)
	{
		if (isMouseHover(true))
		{
			if (InputManager::isButtonDown(key))
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

bool Panel::isMouseDownForMouse(const int key)
{
	if (!isDown)
	{
		if (isMouseHover(false))
		{
			if (InputManager::isButtonDown(key))
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

bool Panel::isMouseUp(const int key)
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

bool Panel::isMousePressForDrag(const int key)
{
	if (isMouseHover(true) && InputManager::isButton(key))
	{
		//isPress = true;
		//SetMouseState(isPress, true);
		//labelCurrentColor = labelClickColor;
		return true;
	}
	return false;
}

bool Panel::isMousePressForMouse(const int key)
{
	if (isMouseHover(false) && InputManager::isButton(key))
	{
		//isPress = true;
		//SetMouseState(isPress, true);
		//labelCurrentColor = labelClickColor;
		return true;
	}
	return false;
}

glm::vec3 Panel::getPanelColor() const
{
	return this->panelColor;
}

glm::vec3 Panel::getOutlineColor() const
{
	return this->outlineColor;
}

bool Panel::isBackGround() const
{
	return this->backGround;
}

bool Panel::isMovable() const
{
	return this->movable;
}

bool Panel::isOutline() const
{
	return this->outline;
}

std::string Panel::getTitle() const
{
	return title.getText();
}

void Panel::setPanelColor(const glm::vec3 color)
{
	this->panelColor = color;
}

void Panel::setBackGround(const bool value)
{
	this->backGround = value;
}

void Panel::setMovable(const bool value)
{
	this->movable = value;
}

void Panel::setTitle(const std::string &text)
{
	this->title.setText(text);
}

void Panel::setOutlineColor(const glm::vec3 color)
{
	this->outlineColor = color;
}

void Panel::setOutline(const bool value)
{
	this->outline = value;
}
