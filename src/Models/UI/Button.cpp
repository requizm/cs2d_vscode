#include "Button.h"

Button::Button() = default;

/*Button::Button(Sprite sprite, std::string text, glm::vec2 position, float scale, glm::vec3 textColor) : Label(text, position, scale, textColor)
{
	this->sprite = sprite;
}*/

Button::Button(const std::string &text, glm::vec2 position, glm::vec2 size, TextRenderer &renderer, glm::vec3 buttonColor, glm::vec3 textColor, float scale) : Label(text, position, renderer, scale, textColor, UIObjectType::BUTTON)
{
	this->buttonColor = buttonColor;
	this->haveOutline = false;
	this->setSize(size);
	this->type = ButtonType::DEFAULT;
	this->difColor = false;
	/*this->haveTile = false;
	this->difColor = false;
	this->haveSprite = false;*/
}

Button::Button(const Sprite &sprite, glm::vec2 position, glm::vec2 size, bool difColor, float scale) : Label(position, size, scale, UIObjectType::BUTTON)
{
	this->sprite = sprite;
	this->haveOutline = false;
	this->difColor = difColor;
	this->type = ButtonType::SPRITE;
	/*this->haveTile = false;
	this->haveSprite = true;*/
}

Button::Button(Tile &tile, float scale) : Label(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::BUTTON)
{
	this->tile = tile;
	this->haveOutline = false;
	this->difColor = false;
	this->type = ButtonType::TILE;
	/*this->haveTile = true;
	this->haveSprite = false;*/
}

Button::~Button() = default;

void Button::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
	if (isVisible() && isEnable() && isRenderable())
	{
		switch (type)
		{
		case ButtonType::DEFAULT:
			if (haveOutline)
			{
				squareRenderer.ui_RenderFilledSquare(this->getPosition(), this->getSize(), currentColor, outlineColor, 1.0F, 1.0F, 0.0F);
			}
			else
			{
				squareRenderer.ui_RenderFilledSquare(this->getPosition(), this->getSize(), currentColor, outlineColor, 0.0F, 1.0F, 0.0F);
			}
			Label::DrawForButton(center);
			break;

		case ButtonType::SPRITE:
			if (difColor)
			{
				spriteRenderer.DrawSprite(this->sprite, this->getPosition(), this->getSize(), currentColor);
			}
			else if (!difColor)
			{
				if (haveOutline)
				{
					squareRenderer.ui_RenderFilledSquare(this->getPosition(), glm::vec2(this->getSize().x + margin.x, this->getSize().y + margin.y), this->currentColor);
					squareRenderer.ui_RenderEmptySquare(this->getPosition(), glm::vec2(this->getSize().x + margin.x, this->getSize().y + margin.y), this->outlineColor);
					spriteRenderer.DrawSprite(this->sprite, glm::vec2(this->getPosition().x + margin.x / 2, this->getPosition().y + margin.y / 2), this->getSize());
				}
				else
				{
					squareRenderer.ui_RenderFilledSquare(this->getPosition(), glm::vec2(this->getSize().x + margin.x, this->getSize().y + margin.y), this->currentColor);
					spriteRenderer.DrawSprite(this->sprite, glm::vec2(this->getPosition().x + margin.x / 2, this->getPosition().y + margin.y / 2), this->getSize());
				}
			}
			break;
		case ButtonType::TILE:
			spriteRenderer.DrawSprite(this->tile.sprite, this->getPosition(), this->getSize());
			break;
		}
	}
}

void Button::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer, float shine, float dt, bool selected)
{
	if (isVisible() && isEnable() && isRenderable())
	{
		switch (type)
		{
		case ButtonType::TILE:
			spriteRenderer.DrawSprite(this->tile.sprite, this->getPosition(), this->getSize(), 0.0F, false, shine, selected, dt);
		}
	}
}

void Button::Draw()
{
	if (isVisible() && isEnable())
	{
		Label::Draw();
	}
}

void Button::Update(const float dt)
{

	if (isEnable() && isMouseEvents())
	{
		if (type == ButtonType::DEFAULT && !text.empty())
		{
			if (isMousePress())
			{
				currentColor = mouseclickColor;
				labelCurrentColor = labelClickColor;
			}
			else if (isMouseHover())
			{
				currentColor = mouseHoverColor;
				labelCurrentColor = labelMouseHoverColor;
			}
			else
			{
				currentColor = buttonColor;
				labelCurrentColor = labelColor;
			}
		}
		else if (type == ButtonType::SPRITE)
		{
			if (isMousePress())
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

void Button::ProcessInput()
{
	if (isMouseEvents())
	{
		isMouseDownM(GLFW_MOUSE_BUTTON_LEFT);
		isMouseUpM(GLFW_MOUSE_BUTTON_LEFT);
	}
}

glm::vec2 Button::getPosition()
{
	if (type == ButtonType::TILE)
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
	if (type == ButtonType::TILE)
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
	if (type == ButtonType::TILE)
	{
		return tile.GetSize();
	}
	return this->size;
}

bool Button::isMouseHover()
{
	if (isEnable() && isMouseEvents())
		return isMouseHoverM();
	return false;
}

bool Button::isMouseDown()
{
	return this->isDown;
}

bool Button::isMouseUp()
{
	return this->isUp;
}

bool Button::isMousePress()
{
	if (isEnable())
		return isMousePressM(GLFW_MOUSE_BUTTON_LEFT);
	return false;
}

bool Button::isMouseHoverM()
{
	const int posX = static_cast<int>(this->getPosition().x);
	const int posY = static_cast<int>(this->getPosition().y);

	int sizeX = static_cast<int>(this->getSize().x);
	int sizeY = static_cast<int>(this->getSize().y);

	if (haveOutline)
	{
		sizeX += margin.x;
		sizeY += margin.y;
	}

	if (InputManager::mousePos.x >= posX && InputManager::mousePos.x <= posX + sizeX && InputManager::mousePos.y >= posY && InputManager::mousePos.y <= posY + sizeY)
	{
		return true;
	}
	return false;
}

bool Button::isMouseDownM(const int key)
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

bool Button::isMouseUpM(const int key)
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

bool Button::isMousePressM(const int key)
{
	if (isMouseHover() && InputManager::isButton(key))
	{
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

void Button::setOutlineColor(const glm::vec3 color)
{
	this->outlineColor = color;
}

void Button::setOutline(const bool value)
{
	this->haveOutline = value;
}

void Button::setMargin(const glm::vec2 value)
{
	if (haveOutline)
		this->margin = value;
}

void Button::setPosition(const glm::vec2 position)
{
	if (type == ButtonType::TILE)
	{
		this->tile.SetPosition(position);
	}
	else
		this->position = position;
}

void Button::setPosition(const int x, const int y)
{
	if (type == ButtonType::TILE)
	{
		this->tile.SetPosition(x, y);
	}
	else
	{
		this->position.x = x;
		this->position.y = y;
	}
}

Tile *Button::getTile()
{
	return &this->tile;
}