#include "TextBox.h"
#include <iostream>

TextBox::TextBox() = default;

TextBox::TextBox(glm::vec2 position, TextRenderer &renderer, glm::vec2 size, bool isBackGround, float scale /*= 1.0F*/, glm::vec3 color /*= glm::vec3(1.0F)*/) : Label(position, renderer, scale, color, UIObjectType::TEXTBOX)
{
	this->editable = true;
	this->editMode = false;
	this->isBackGround = isBackGround;
	cursor = Sprite(ResourceManager::GetTexture("textcursor"));
	this->size = size;
	labelClickColor = glm::vec3(1.0F);
	clickBorderColor = glm::vec3(1.0F);
	borderColor = glm::vec3(0.6F);
	hoverBorderColor = glm::vec3(0.78F);
	currentBorderColor = borderColor;
	square = Square(true);
}

void TextBox::Update(const float dt)
{
	InputText(dt);
}

void TextBox::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
	if (isVisible() && isEnable())
	{
		if (isBackGround)
			squareRenderer.ui_RenderFilledSquare(this->getPosition(), this->getSize(), glm::vec3(0.15F), currentBorderColor, 1.0F, 1.0F);
		if (editMode)
		{
			if (time <= 0.5F)
			{
				spriteRenderer.DrawSprite(cursor, glm::vec2(getPosition().x - 2.0F + labelSize.x, getPosition().y + 2.0F), glm::vec2(8.0F, 16.0F));
			}
			else if (time >= 1.0F)
			{
				time = 0.0F;
			}
		}
		this->rend->RenderText(getText(), getPosition().x, getPosition().y + 2.0F, scale, labelCurrentColor);
	}
}

void TextBox::OnEnable()
{
	
}

void TextBox::OnDisable()
{
	this->editMode = false;
	this->setText("");
}

void TextBox::setText(const std::string &text)
{
	this->text = text;
	this->labelSize = rend->CalculateSize(text, scale);
}

bool TextBox::isMouseHover()
{
	return isMouseHoverM();
}

bool TextBox::isMouseDown()
{
	return isMouseDownM(GLFW_MOUSE_BUTTON_LEFT);
}

bool TextBox::isMouseUp()
{
	return isMouseUpM(GLFW_MOUSE_BUTTON_LEFT);
}

bool TextBox::isMousePress()
{
	return isMousePressM(GLFW_MOUSE_BUTTON_LEFT);
}

bool TextBox::isMouseHoverM()
{
	const int posX = static_cast<int>(this->getPosition().x);
	const int posY = static_cast<int>(this->getPosition().y);

	const int sizeX = static_cast<int>(this->size.x);
	const int sizeY = static_cast<int>(this->size.y);

	if (InputManager::mousePos.x >= posX && InputManager::mousePos.x <= posX + sizeX && InputManager::mousePos.y >= posY && InputManager::mousePos.y <= posY + sizeY)
	{
		if (editable && !editMode)
			currentBorderColor = hoverBorderColor; //0.78F
		return true;
	}
	if (editable && !editMode)
		currentBorderColor = borderColor; //0.6F
	return false;
}

bool TextBox::isMouseDownM(const int key)
{
	if (InputManager::isButtonDown(key) && isMouseHover())
	{
		isDown = true;
		return true;
	}
	return false;
}

bool TextBox::isMouseUpM(const int key)
{
	if (InputManager::isButtonUp(key) && isDown)
	{
		isDown = false;
		return true;
	}
	return false;
}

bool TextBox::isMousePressM(const int key)
{
	if (isMouseHover() && InputManager::isButton(key))
	{
		return true;
	}
	return false;
}

void TextBox::InputText(const float dt)
{
	if (editable && isEnable())
	{
		if (isMouseDown())
		{
			editMode = true;
			time = 0.0F;
			labelCurrentColor = labelClickColor;
			currentBorderColor = clickBorderColor; //1.0F
		}

		if (editMode)
		{
			time += dt;
			if (InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT) && !isMouseHover())
			{
				this->labelCurrentColor = labelColor;
				this->currentBorderColor = borderColor; //0.6F
				editMode = false;
			}

			if (InputManager::isKeyDown(GLFW_KEY_BACKSPACE))
			{
				if (!text.empty())
				{
					text.pop_back();
					this->labelSize = rend->CalculateSize(text, scale);
				}
			}

			if (InputManager::keycode != L'\0')
			{
				if (InputManager::keycode >= 0 && InputManager::keycode <= 255)
				{
					const wchar_t keycode = InputManager::keycode;
					const wchar_t *c = &keycode;
					std::wstring tempString = &c[0];
					std::string afsaf;
					afsaf = tempString[0];
					this->text += afsaf;
					if (rend->CalculateSize(text, scale).x >= size.x)
					{
						text.pop_back();
					}
					else
					{
						this->labelSize = rend->CalculateSize(text, scale);
					}
				}
				InputManager::keycode = L'\0';
			}
		}
		else if (isMouseHover())
		{
			currentBorderColor = hoverBorderColor; //0.78F
		}

		else
		{
			currentBorderColor = borderColor; //0.6F
		}
	}

	isMouseUp();
}