#include "SpriteButton.hpp"

SpriteButton::SpriteButton(const Sprite &sprite, const Vector2<int> &position, const Vector2<int> &size,
                           bool difColor, float scale) : UIObject(position, size, scale, UIObjectType::SPRITEBUTTON)
{
    this->sprite = sprite;

    mDown = std::bind(&SpriteButton::onMouseDown, this);
    InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);

    mUp = std::bind(&SpriteButton::onMouseUp, this);
    InputManager::addListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
}

SpriteButton::SpriteButton(const Sprite &sprite, const Vector2<int> &position, const Vector2<int> &size, Object *par,
                           bool difColor, float scale) : UIObject(position, size, scale, UIObjectType::SPRITEBUTTON, par)
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
    RemoveParent();
}

void SpriteButton::Update()
{
    if (IsEnable() && mouseEvents)
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
    if (IsEnable())
    {
        squareRenderer.ui_RenderFilledSquare(
            position,
            GetSize(),
            buttonCurrentColor);
        if (haveOutline)
        {
            squareRenderer.ui_RenderEmptySquare(
                position,
                GetSize(),
                outlineColor);
        }
        spriteRenderer.DrawSprite(
            sprite,
            spritePos,
            size);
    }
}

Vector2<int> SpriteButton::GetSize()
{
    return size + margin;
}

void SpriteButton::SetPosition(const Vector2<int> &position)
{
    Object::SetPosition(position);
}

void SpriteButton::SetTransform(const Matrix4<float> &value)
{
    UIObject::SetTransform(value);
    setMargin(margin);
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
    if (InputManager::mousePos.x >= position.x &&
        InputManager::mousePos.x <= position.x + size.x &&
        InputManager::mousePos.y >= position.y &&
        InputManager::mousePos.y <= position.y + size.y)
    {
        return true;
    }
    return false;
}

void SpriteButton::onMouseDown()
{
    if (IsEnable() && isMouseHover())
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
    if (isPressed && IsEnable() && isMouseHover())
    {
        buttonCurrentColor = buttonColor;

        isPressed = false;

        for (auto &f : listenersUp)
        {
            f();
        }
    }
}
