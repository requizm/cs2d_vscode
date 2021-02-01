#include "TextBox.hpp"
#include <iostream>

#include "../../Others/Timer.hpp"

TextBox::TextBox() : Label()
{
}

TextBox::TextBox(Vector2<int> position, TextRenderer &renderer, Vector2<int> size, bool isBackGround, float scale /*= 1.0F*/, const Vector3<float> &color /*= Vector3<float>(1.0F)*/) : Label(position, renderer, scale, color, UIObjectType::TEXTBOX)
{
	this->editable = true;
	this->editMode = false;
	this->isBackGround = isBackGround;
	cursor = Sprite(ResourceManager::GetTexture("textcursor"));
	this->size = size;
	labelClickColor = Vector3<float>(1.0F);
	clickBorderColor = Vector3<float>(1.0F);
	borderColor = Vector3<float>(0.6F);
	hoverBorderColor = Vector3<float>(0.78F);
	currentBorderColor = borderColor;
}

TextBox::~TextBox()
{
	UIObject::removeParent();
}

void TextBox::Update()
{
	InputText();
}

void TextBox::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
	if (isVisible() && isEnable())
	{
		if (isBackGround)
			squareRenderer.ui_RenderFilledSquare(this->getPosition(), this->getSize(), Vector3<float>(0.15F), true, currentBorderColor, 1.0F, 1.0F);
		if (editMode)
		{
			if (time <= 0.5F)
			{
				spriteRenderer.DrawSprite(cursor, Vector2<int>(getPosition().x - 2.0F + labelSize.x, getPosition().y + 2.0F), Vector2<int>(8, 16));
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

void TextBox::InputText()
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
			time += Timer::DeltaTime;
			if (InputManager::isButtonDown(GLFW_MOUSE_BUTTON_LEFT) && !isMouseHover())
			{
				this->labelCurrentColor = labelColor;
				this->currentBorderColor = borderColor; //0.6F
				editMode = false;
			}

			if (InputManager::isKeyDown(KeyboardKeys::KEY_BACKSPACE))
			{
				if (!text.empty())
				{
					text.pop_back();
					this->labelSize = rend->CalculateSize(text, scale);
				}
			}

			if (InputManager::keycode != L'\0')
			{
				if (InputManager::keycode <= 255)
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