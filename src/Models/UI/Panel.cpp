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
	escapeButton = Button(Sprite(ResourceManager::GetTexture("gui_icons"), 0, 0, 16, 16), position, glm::vec2(20.0F, 20.0F), true);
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
		if (mouseEvents && isMovable())
		{
			if (!click && (opttitles && !escapeButton.isPressed) || (!opttitles && !click))
			{
				if (isMouseDown(true))
				{
					deltaX = InputManager::mousePos.x - static_cast<int>(position.x);
					deltaY = InputManager::mousePos.y - static_cast<int>(position.y);
					click = true;
				}
			}
			if (isPressed && click)
			{
				glm::vec2 mousePos = InputManager::mousePos;
				this->setPosition(glm::vec2(mousePos.x - static_cast<float>(deltaX), mousePos.y - static_cast<float>(deltaY)));
				//std::cout << "hey" << std::endl;
			}
			if (!isPressed)
				click = false;
		}
		if (opttitles)
		{
			escapeButton.Update(dt);
			if (escapeButton.isMouseUp())
			{
				this->setEnable(false);
			}
		}
	}
}

void Panel::ProcessInput()
{
	escapeButton.ProcessInput();
	if (mouseEvents)
	{
		if (isMovable())
		{
			isMouseDownForDrag(GLFW_MOUSE_BUTTON_LEFT);
		}
		else
		{
			isMouseDownForMouse(GLFW_MOUSE_BUTTON_LEFT);
		}
	}
	isMouseUpM(GLFW_MOUSE_BUTTON_LEFT);
}

void Panel::OnEnable()
{
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

bool Panel::isMouseDown(bool drag)
{
	if (!this->isEnable())
	{
		return false;
	}
	if (drag)
		return isDownForDrag;
	else
		return isDown;
}

bool Panel::isMouseUp()
{
	return isUp;
}

bool Panel::isMousePress(bool drag)
{
	if (!this->isEnable())
	{
		return false;
	}
	if (drag)
		return isMousePressForDrag(GLFW_MOUSE_BUTTON_LEFT);
	else
		return isMousePressForMouse(GLFW_MOUSE_BUTTON_LEFT);
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
	if (isPressed && isDownForDrag)
	{
		isDownForDrag = false;
		return false;
	}
	if (InputManager::isButtonDown(key) && isMouseHover(true))
	{
		isPressed = true;
		isDownForDrag = true;
		return true;
	}
	return false;
}

bool Panel::isMouseDownForMouse(const int key)
{
	if (isPressed && isDown)
	{
		isDown = false;
		return false;
	}
	if (InputManager::isButtonDown(key) && isMouseHover(false))
	{
		isPressed = true;
		isDown = true;
		return true;
	}
	return false;
}

bool Panel::isMouseUpM(const int key)
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

bool Panel::isMousePressForDrag(const int key)
{
	if (isMouseHover(true) && InputManager::isButton(key))
	{
		return true;
	}
	return false;
}

bool Panel::isMousePressForMouse(const int key)
{
	if (isMouseHover(false) && InputManager::isButton(key))
	{
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
