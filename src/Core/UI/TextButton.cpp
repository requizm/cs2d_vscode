#include "TextButton.hpp"

TextButton::TextButton(const std::string &text, const Vector2<int> &position, const Vector2<int> &size,
                       TextRenderer &renderer,
                       const Vector3<float> &buttonColor,
                       const Vector3<float> &textColor,
                       float scale, UIObjectType type) : UIObject(position, size, 1.0F, renderer, type)
{
    this->buttonColor = buttonColor;
    this->textColor = textColor;
    this->text = text;
    textSize = rend->CalculateSize(text, scale);
    setTextAlign(textAlign);

    mDown = std::bind(&TextButton::onMouseDown, this);
    InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);

    mUp = std::bind(&TextButton::onMouseUp, this);
    InputManager::addListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
}

TextButton::TextButton(const std::string &text, const Vector2<int> &position, const Vector2<int> &size,
                       TextRenderer &renderer, Object *par,
                       const Vector3<float> &buttonColor,
                       const Vector3<float> &textColor,
                       float scale, UIObjectType type) : UIObject(position, size, 1.0F, renderer, type, par)
{
    this->buttonColor = buttonColor;
    this->textColor = textColor;
    this->text = text;
    textSize = rend->CalculateSize(text, scale);
    setTextAlign(textAlign);

    mDown = std::bind(&TextButton::onMouseDown, this);
    InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);

    mUp = std::bind(&TextButton::onMouseUp, this);
    InputManager::addListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
}

TextButton::~TextButton()
{
    InputManager::removeListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
    InputManager::removeListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
    RemoveParent();
}


void TextButton::Update()
{
    if (IsEnable() && mouseEvents)
    {
        if (!isPressed)
        {
            if (isMouseHover())
            {
                buttonCurrentColor = buttonHoverColor;
                textCurrentColor = textHoverColor;
            }
            else
            {
                buttonCurrentColor = buttonColor;
                textCurrentColor = textColor;
            }
        }
    }
}

void TextButton::ProcessInput()
{
}

void TextButton::Draw(SquareRenderer &squareRenderer)
{
    if (IsEnable())
    {
        squareRenderer.ui_RenderFilledSquare(
            position, size, buttonCurrentColor,
            haveOutline, outlineColor, 1.0F, 1.0F, 0.0F);
        this->rend->RenderText(text, textPos, scale,
                               textCurrentColor);
    }
}

void TextButton::SetPosition(const Vector2<int> &position)
{
    UIObject::SetPosition(position);
    setTextAlign(textAlign);
}

void TextButton::SetTransform(const Matrix4<float> &value)
{
    UIObject::SetTransform(value);
    setTextAlign(textAlign);
}

void TextButton::setButtonColor(const Vector3<float> &value) { buttonColor = value; }

void TextButton::setButtonHoverColor(const Vector3<float> &value) { buttonHoverColor = value; }

void TextButton::setOutlineColor(const Vector3<float> &value) { outlineColor = value; }

void TextButton::setTextHoverColor(const Vector3<float> &value) { textHoverColor = value; }

void TextButton::setTextClickColor(const Vector3<float> &value) { textClickColor = value; }

void TextButton::setButtonClickColor(const Vector3<float> &value) { buttonClickColor = value; }

void TextButton::setTextColor(const Vector3<float> &value) { textColor = value; }

void TextButton::setHaveOutline(bool value) { haveOutline = value; }

void TextButton::setTextAlign(TextAlign value)
{
    textAlign = value;

    Vector2<int> dif;
    switch (textAlign)
    {
        case TextAlign::T_LEFT:
            textPos = position;
            break;
        case TextAlign::T_CENTER:
            dif = size - textSize;
            dif.y /= 2;
            dif.x /= 2;
            textPos = position + dif;
            break;
        case TextAlign::T_RIGHT:
            dif = size - textSize;
            textPos = position + dif;
            break;
    }
}

std::string TextButton::getText() const { return text; }

void TextButton::setText(const std::string &value)
{
    text = value;
    textSize = rend->CalculateSize(text, scale);
}

Vector2<int> TextButton::getTextSize() const { return textSize; }

Vector2<int> TextButton::getTextPos() const { return textPos; }

void TextButton::addListenerDown(std::function<void()> func)
{
    listenersDown.push_back(func);
}

void TextButton::addListenerUp(std::function<void()> func)
{
    listenersUp.push_back(func);
}

bool TextButton::isMouseHover()
{
    if (InputManager::mousePos.x >= position.x &&
        InputManager::mousePos.x <= position.x + size.x &&
        InputManager::mousePos.y >= position.y &&
        InputManager::mousePos.y <= position.y + size.y)
    {
        return true;
    }
    return false;
}

void TextButton::onMouseDown()
{
    if (IsEnable() && isMouseHover())
    {
        textCurrentColor = textClickColor;
        buttonCurrentColor = buttonClickColor;

        isPressed = true;

        for (auto &f : listenersDown)
        {
            f();
        }
    }
}

void TextButton::onMouseUp()
{
    if (isPressed && IsEnable() && isMouseHover())
    {
        textCurrentColor = textColor;
        buttonCurrentColor = buttonColor;

        isPressed = false;

        for (auto &f : listenersUp)
        {
            f();
        }
    }
}
