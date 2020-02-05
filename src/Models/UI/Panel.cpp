#include "Panel.h"
#include <iostream>

Panel::Panel(glm::vec2 position, const std::string &title, glm::vec2 size, TextRenderer &renderer, bool isBackGround, bool opttitles, float scale, glm::vec3 color) : UIObject(position, size, scale, UIObjectType::PANEL)
{
	this->panelColor = color;
	this->backGround = isBackGround;
	this->dragSize = glm::vec2(size.x, 23.0F);
	this->opttitles = opttitles;
	this->enable = false;
	this->movable = true;
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
	if (isEnable())
	{
		if (isVisible() && this->backGround)
		{
			squareRenderer.RenderSquare(this->square, this->getPosition(), this->getSize(), this->getPanelColor());
		}

		if (opttitles)
		{
			squareRenderer.RenderLine(glm::vec2(getPosition().x + lineOffset, getPosition().y + 23.0F), glm::vec2(size.x - 2 * lineOffset, 1.0F), glm::vec3(0.39F));
			escapeButton.Draw(spriteRenderer);
			title.Draw();
		}

		if(isOutline())
		{
			squareRenderer.RenderSquare(this->square, getPosition(), size, getPanelColor(), getOutlineColor());
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
				if (isMouseDown(GLFW_MOUSE_BUTTON_LEFT))
				{

					deltaX = InputManager::mouseX - static_cast<int>(position.x);
					deltaY = InputManager::mouseY - static_cast<int>(position.y);
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
					glm::vec2 mousePos = glm::vec2(InputManager::mouseX, InputManager::mouseY);
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

bool Panel::isMouseHover()
{
	return isMouseHoverM();
}

bool Panel::isMouseDown(const int key)
{
	return isMouseDownM(key);
}

bool Panel::isMouseUp(const int key)
{
	return isMouseUpM(key);
}

bool Panel::isMousePress(const int key)
{
	return isMousePressM(key);
}

bool Panel::isMouseHoverM()
{
	const int posX = static_cast<int>(this->getPosition().x);
	const int posY = static_cast<int>(this->getPosition().y);

	const int sizeX = static_cast<int>(this->dragSize.x);
	const int sizeY = static_cast<int>(this->dragSize.y);

	for (int i = posX; i <= posX + sizeX; i++)
	{
		for (int j = posY; j <= posY + sizeY; j++)
		{
			if (InputManager::mouseX == i && InputManager::mouseY == j)
			{
				return true;
			}
		}
	}
	return false;
}

bool Panel::isMouseDownM(const int key)
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

bool Panel::isMouseUpM(const int key)
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

bool Panel::isMousePressM(const int key)
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

