#include "SpriteButton.hpp"

SpriteButton::SpriteButton(const Sprite &sprite, const Vector2<int> &position, const Vector2<int> &size,
                           bool difColor, float scale) : UIObject(position, scale, UIObjectType::SPRITEBUTTON)
{
    this->sprite = sprite;
    this->size = size;

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
                buttonCurrentColor = buttonHoverColor;
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
                outlineColor);
        }
        spriteRenderer.DrawSprite(
            sprite,
            spritePos,
            size);
    }
}

Vector2<int> SpriteButton::getSize()
{
    return size + margin;
}

void SpriteButton::setPosition(const Vector2<int> &position)
{
    Vector2<int> newPos = position;
    if (isParent())
    {
        newPos = newPos + getParent()->getPosition();
    }
    this->position = newPos;
    spritePos = Vector2<int>(newPos.x + margin.x / 2, newPos.y + margin.y / 2);
}

void SpriteButton::setButtonCurrentColor(const Vector3<float> &value) { buttonCurrentColor = value; }

void SpriteButton::setButtonHoverColor(const Vector3<float> &value) { buttonHoverColor = value; }

void SpriteButton::setButtonClickColor(const Vector3<float> &value) { buttonClickColor = value; }

void SpriteButton::setOutlineColor(const Vector3<float> &value) { outlineColor = value; }

void SpriteButton::setButtonColor(const Vector3<float> &value) { buttonColor = value; }

void SpriteButton::setMargin(const Vector2<int> &value)
{
    margin = value;
    spritePos = Vector2<int>(position.x + margin.x / 2, position.y + margin.y / 2);
}

void SpriteButton::setSprite(const Sprite &value) { sprite = value; }

void SpriteButton::setHaveOutline(bool value) { haveOutline = value; }

void SpriteButton::addListenerDown(std::function<void()> func)
{
    listenersDown.push_back(func);
}

void SpriteButton::addListenerUp(std::function<void()> func)
{
    listenersUp.push_back(func);
}

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
