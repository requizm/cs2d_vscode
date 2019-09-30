#include "Button.h"

Button::Button() = default;

/*Button::Button(Sprite sprite, std::string text, glm::vec2 position, float scale, glm::vec3 textColor) : Label(text, position, scale, textColor)
{
	this->sprite = sprite;
}*/

Button::Button(const std::string &text, glm::vec2 position, TextRenderer &renderer, glm::vec3 buttonColor, glm::vec3 textColor, float scale) : Label(text, position, renderer, scale, textColor, UIObjectType::BUTTON)
{
	this->buttonColor = buttonColor;
}

Button::Button(const Sprite &sprite, glm::vec2 position, glm::vec2 size, float scale) : Label(position, size, scale, UIObjectType::BUTTON)
{
	this->sprite = sprite;
}

Button::Button(Tile tile, float scale) : Label(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::BUTTON)
{
	this->tile = tile;
	this->haveTile = true;
}

Button::~Button() = default;

void Button::Draw(SpriteRenderer &spriteRenderer) const
{
	if (isVisible() && isEnable())
	{
		if (!haveTile)
			spriteRenderer.DrawSprite(this->sprite, this->getPosition(), this->getSize(), currentColor);
		else
			spriteRenderer.DrawSprite(this->tile.sprite, this->getPosition(), this->getSize());
	}
	//buttonRenderer.RenderButton(&textRenderer, this);
	//Label::Draw();
}

void Button::Draw(/*SquareRenderer &squareRenderer*/ /*ButtonRenderer &buttonRenderer,*/) const
{
	//buttonRenderer.CalculateSize(&textRenderer, this);
	//squareRenderer.RenderSquare(square, this->position, glm::vec2(this->labelSize.x + 20.0F, this->labelSize.y + 10.0F), this->buttonColor);
	Label::Draw();
}

void Button::Update(const float dt) //refactor: sürekli atama yapılamaz, state change callback lazim
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

glm::vec2 Button::getPosition() const
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

glm::vec2 Button::getSize() const
{
	if (haveTile)
	{
		return tile.GetSize();
	}
	return this->size;
}

bool Button::isMouseHover() const
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
				return true;
			}
		}
	}
	return false;
}

bool Button::isMouseDown(int key) //refactor: bu ne allah askina
{
	if (!isDown)
	{
		if (InputManager::isButtonDown(key) && isMouseHover())
		{
			isDown = true;
			return true;
		}
	}

	return false;
}

bool Button::isMouseUp(int key) //refactor: bunlar neden bir arada degil? 
{
	if (InputManager::isButtonUp(key))
	{
		if (isDown)
		{
			isDown = false;
			return true;
		}
	}
	return false;
}

bool Button::isMousePress(int key) const
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
