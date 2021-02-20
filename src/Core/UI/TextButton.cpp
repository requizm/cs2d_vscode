#include "TextButton.hpp"

TextButton::TextButton(const std::string &text, Vector2<int> position,
                       TextRenderer &renderer,
                       const Vector3<float> &buttonColor,
                       const Vector3<float> &textColor,
                       float scale) : UIObject(position, 1.0F, renderer, UIObjectType::TEXTBUTTON)
{
}

void TextButton::Update()
{
    /*if (isEnable() && isMouseEvents())
    {
        if (!isPressed && isMouseHover())
        {
            buttonCurrentColor = mouseHoverColor;
            labelCurrentColor = labelMouseHoverColor;
        }
        else if (!isPressed)
        {
            buttonCurrentColor = buttonColor;
            labelCurrentColor = labelColor;
        }
    }*/
}

void TextButton::ProcessInput()
{
}

void TextButton::Draw(SquareRenderer &squareRenderer)
{
    squareRenderer.ui_RenderFilledSquare(
        position, size, buttonCurrentColor,
        haveOutline, outlineColor, 1.0F, 1.0F, 0.0F);
    this->rend->RenderText(text, textPos, scale,
                           textCurrentColor);
}

void TextButton::setButtonColor(const Vector3<float> &value) { buttonColor = value; }

void TextButton::setButtonMouseHoverColor(const Vector3<float> &value) { buttonMouseHoverColor = value; }

void TextButton::setTextColor(const Vector3<float> &value) { textColor = value; }

void TextButton::setOutlineColor(const Vector3<float> &value) { outlineColor = value; }

void TextButton::setTextMouseHoverColor(const Vector3<float> &value) { textMouseHoverColor = value; }

void TextButton::setTextColor(const Vector3<float> &value) { textColor = value; }

void TextButton::setHaveOutline(bool value) { haveOutline = value; }

std::string TextButton::getText() const { return text; }

void TextButton::setText(const std::string &value)
{
    text = value;

    textSize = rend->CalculateSize(text, scale);

    Vector2<int> dif = getSize() - textSize;
    dif.y /= 2;
    dif.x /= 2;
    textPos = this->position + dif;
}

Vector2<int> TextButton::getTextSize() const { return textSize; }

Vector2<int> TextButton::getTextPos() const { return textPos; }

void TextButton::onMouseDown()
{
}

void TextButton::onMouseUp()
{
}
