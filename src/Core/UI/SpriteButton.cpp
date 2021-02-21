#include "SpriteButton.hpp"

SpriteButton::SpriteButton(const Sprite &sprite, const Vector2<int> &position, const Vector2<int> &size,
                           bool difColor, float scale) : UIObject(position, scale, UIObjectType::SPRITEBUTTON)
{
    this->sprite = sprite;

    mDown = std::bind(&SpriteButton::onMouseDown, this);
    InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);

    mUp = std::bind(&SpriteButton::onMouseUp, this);
    InputManager::addListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
}

SpriteButton::~SpriteButton()
{
    InputManager::removeListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
    InputManager::removeListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
    removeParent();
}

void SpriteButton::Update()
{
    if (isEnable() && isMouseEvents())
    {
        if (!isPressed)
        {
            if (isMouseHover())
            {
                buttonCurrentColor = buttonMouseHoverColor;
            }
            else
            {
                buttonCurrentColor = buttonColor;
            }
        }
    }
}

void SpriteButton::ProcessInput()
{
}

void SpriteButton::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    if (isEnable() && isVisible())
    {
        squareRenderer.ui_RenderFilledSquare(
            position,
            getSize(),
            buttonCurrentColor);
        if (haveOutline)
        {
            squareRenderer.ui_RenderEmptySquare(
                position,
                getSize(),
                this->outlineColor);
        }
        spriteRenderer.DrawSprite(
            this->sprite,
            Vector2<int>(position.x + margin.x / 2,
                         position.y + margin.y / 2),
            this->size);
    }
}

Vector2<int> SpriteButton::getSize()
{
    return size + margin;
}

void SpriteButton::setButtonCurrentColor(const Vector3<float> &value) { buttonCurrentColor = value; }

void SpriteButton::setButtonMouseHoverColor(const Vector3<float> &value) { buttonMouseHoverColor = value; }

void SpriteButton::setButtonClickColor(const Vector3<float> &value) { buttonClickColor = value; }

void SpriteButton::setOutlineColor(const Vector3<float> &value) { outlineColor = value; }

void SpriteButton::setButtonColor(const Vector3<float> &value) { buttonColor = value; }

void SpriteButton::setMargin(const Vector2<int> &value) { margin = value; }

void SpriteButton::setSprite(const Sprite &value) { sprite = value; }

bool SpriteButton::isMouseHover()
{
    Vector2<int> pos = position;
    Vector2<int> size = size;

    if (InputManager::mousePos.x >= pos.x &&
        InputManager::mousePos.x <= pos.x + size.x &&
        InputManager::mousePos.y >= pos.y &&
        InputManager::mousePos.y <= pos.y + size.y)
    {
        return true;
    }
    return false;
}

void SpriteButton::onMouseDown()
{
    if (isEnable() && isMouseHover())
    {
        buttonCurrentColor = buttonClickColor;

        isPressed = true;

        for (auto &f : listenersDown)
        {
            f();
        }
    }
}

void SpriteButton::onMouseUp()
{
    if (isPressed && isEnable() && isMouseHover())
    {
        buttonCurrentColor = buttonColor;

        isPressed = false;

        for (auto &f : listenersUp)
        {
            f();
        }
    }
}
