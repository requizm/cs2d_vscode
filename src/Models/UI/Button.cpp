#include "Button.h"

Button::Button() = default;

/*Button::Button(Sprite sprite, std::string text, glm::vec2 position, float scale, glm::vec3 textColor) : Label(text, position, scale, textColor)
{
	this->sprite = sprite;
}*/

Button::Button(const std::string &text, glm::vec2 position, TextRenderer &renderer, glm::vec3 buttonColor, glm::vec3 textColor, float scale) : Label(text, position, renderer, scale, textColor, UIObjectType::BUTTON)
{
	this->buttonColor = buttonColor;
	square = Square(true);
}

Button::Button(const Sprite &sprite, glm::vec2 position, glm::vec2 size, float scale) : Label(position, size, scale, UIObjectType::BUTTON)
{
	this->sprite = sprite;
	square = Square(true);
}

Button::Button(Tile tile, float scale) : Label(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::BUTTON)
{
	this->tile = tile;
	this->haveTile = true;
	square = Square(true);
}

Button::~Button() = default;

void Button::Draw(SpriteRenderer &spriteRenderer)
{
	if (isVisible() && isEnable() && isRenderable())
	{
		if (!haveTile)
			spriteRenderer.DrawSprite(this->sprite, this->getPosition(), this->getSize(), currentColor);
		else
			spriteRenderer.DrawSprite(this->tile.sprite, this->getPosition(), this->getSize());
	}
	//buttonRenderer.RenderButton(&textRenderer, this);
	//Label::Draw();
}

void Button::Draw(/*SquareRenderer &squareRenderer*/ /*ButtonRenderer &buttonRenderer,*/)
{
	//buttonRenderer.CalculateSize(&textRenderer, this);
	//squareRenderer.RenderSquare(square, this->position, glm::vec2(this->labelSize.x + 20.0F, this->labelSize.y + 10.0F), this->buttonColor);
	Label::Draw();
}

void Button::Update(const float dt)
{
	if (isEnable())
	{
		if (!haveTile)
		{
			if (isMousePress(GLFW_MOUSE_BUTTON_LEFT))
			{
				currentColor = mouseclickColor;
			}
			else if (isMouseHover())
			{
				currentColor = mouseHoverColor;
			}
			else
			{
				currentColor = buttonColor;
			}
		}
	}
}

glm::vec2 Button::getPosition()
{
	if (haveTile)
	{
		if (isParent())
		{
			return parent->getPosition() + this->tile.GetPosition();
		}
		return this->tile.GetPosition();
	}
	if (isParent())
	{
		return parent->getPosition() + this->position;
	}
	return this->position;
}

glm::vec2 Button::getLocalPosition()
{
	if (haveTile)
	{
		if (isParent())
		{
			return this->getPosition() - parent->getPosition();
		}
		return this->tile.GetPosition();
	}
	if (isParent())
	{
		return this->getPosition() - parent->getPosition();
	}
	return this->position;
}

glm::vec2 Button::getSize()
{
	if (haveTile)
	{
		return tile.GetSize();
	}
	return this->size;
}

bool Button::isMouseHover()
{
	return isMouseHoverM();
	//return isHover;
}

bool Button::isMouseDown(const int key)
{
	return isMouseDownM(key);
	//return isDown;
}

bool Button::isMouseUp(const int key) //refactor: neden beraber degiller
{
	return isMouseUpM(key);
	//return isUp;
}

bool Button::isMousePress(const int key)
{
	return isMousePressM(key);
	//return isPress;
}

bool Button::isMouseHoverM()
{
	const int posX = static_cast<int>(this->getPosition().x);
	const int posY = static_cast<int>(this->getPosition().y);

	const int sizeX = static_cast<int>(this->getSize().x);
	const int sizeY = static_cast<int>(this->getSize().y);

	for (int i = posX; i <= posX + sizeX; i++)
	{
		for (int j = posY; j <= posY + sizeY; j++)
		{
			if (InputManager::mouseX == i && InputManager::mouseY == j)
			{
				//SetMouseState(isHover, true);
				//isHover = true;
				//labelCurrentColor = labelMouseHoverColor;
				//currentColor = mouseHoverColor;
				return true;
			}
		}
	}
	//SetMouseState(isHover, false);
	//isHover = false;
	return false;
}

bool Button::isMouseDownM(const int key)
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

bool Button::isMouseUpM(const int key) //refactor: neden beraber degiller
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

bool Button::isMousePressM(const int key)
{
	if (isMouseHover() && InputManager::isButton(key))
	{
		//isPress = true;
		//SetMouseState(isPress, true);
		return true;
	}
	return false;
}

void Button::setMouseHoverColor(const glm::vec3 color)
{
	this->mouseHoverColor = color;
}

void Button::setButtonColor(const glm::vec3 color)
{
	this->buttonColor = color;
}

void Button::setMouseClickColor(const glm::vec3 color)
{
	this->mouseclickColor = color;
}

void Button::setPosition(const glm::vec2 position)
{
	if (haveTile)
	{
		this->tile.SetPosition(position);
	}
	else
		this->position = position;
}

void Button::setPosition(const int x, const int y)
{
	if (haveTile)
	{
		this->tile.SetPosition(x, y);
	}
	else
	{
		this->position.x = x;
		this->position.y = y;
	}
}
