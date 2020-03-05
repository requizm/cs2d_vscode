#include "RadioButton.h"

RadioButton::RadioButton() = default;

RadioButton::~RadioButton() = default;

RadioButton::RadioButton(const std::string &text, glm::vec2 position, glm::vec2 size, TextRenderer &renderer, glm::vec3 buttonColor, glm::vec3 textColor, float scale)
    : Label(text, position, renderer, scale, textColor, UIObjectType::RADIOBUTTON), selected(false)
{
    this->setButtonColor(buttonColor);
    this->setSize(size);
}

void RadioButton::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    if (isVisible() && isEnable())
    {
        if (!text.empty())
            this->rend->RenderText(text, glm::vec2(getPosition().x + labelSize.y / 2 + 2.0F, getPosition().y), scale, labelCurrentColor);
        squareRenderer.ui_RenderEmptyCircle(getPosition(), glm::vec2(labelSize.y), currentColor);
    }
}

void RadioButton::Update(const float dt)
{
    if (isEnable() && isMouseEvents())
    {
        if (isMouseHover())
        {
            labelCurrentColor = mouseHoverColor;
            currentColor = mouseHoverColor;
        }
        else
        {
            labelCurrentColor = labelColor;
            currentColor = buttonColor;
        }
    }
}

void RadioButton::ProcessInput()
{
    if (isMouseEvents() && isEnable())
    {
        isMouseDownM(GLFW_MOUSE_BUTTON_LEFT);
        isMouseUpM(GLFW_MOUSE_BUTTON_LEFT);
    }
}

glm::vec2 RadioButton::getPosition()
{
    if (isParent())
        return this->position + parent->getPosition();
    return this->position;
}
glm::vec2 RadioButton::getLocalPosition()
{
    if (isParent())
        return this->position - parent->getPosition();
    return glm::vec2(0.0F);
}
glm::vec2 RadioButton::getSize()
{
    glm::vec2 ps;
    ps.x = (getPosition().x + labelSize.y / 2 + 2.0F + labelSize.x) - (getPosition().x - labelSize.y / 2);
    ps.y = labelSize.y;
    return ps;
}

void RadioButton::setMouseHoverColor(const glm::vec3 color)
{
    this->mouseHoverColor = color;
}
void RadioButton::setButtonColor(const glm::vec3 color)
{
    this->buttonColor = color;
}
void RadioButton::setMouseClickColor(const glm::vec3 color)
{
    this->mouseclickColor = color;
}

void RadioButton::OnEnable()
{
}
void RadioButton::OnDisable()
{
    this->selected = false;
}

void RadioButton::setPosition(const glm::vec2 position)
{
    this->position = position;
}
void RadioButton::setPosition(const int x, const int y)
{
    this->position.x = x;
    this->position.y = y;
}

bool RadioButton::isMouseHover()
{
    if (isEnable() && isMouseEvents())
        return isMouseHoverM();
    return false;
}
bool RadioButton::isMouseDown()
{
    return this->isDown;
}
bool RadioButton::isMouseUp()
{
    return this->isUp;
}
bool RadioButton::isMousePress()
{
    if (isEnable())
        return isMousePressM(GLFW_MOUSE_BUTTON_LEFT);
    return false;
}

bool RadioButton::isMouseHoverM()
{
    const int posX = static_cast<int>(this->getPosition().x - labelSize.y / 2);
    const int posY = static_cast<int>(this->getPosition().y);

    int sizeX = static_cast<int>(this->getSize().x);
    int sizeY = static_cast<int>(this->getSize().y);

    if (InputManager::mousePos.x >= posX && InputManager::mousePos.x <= posX + sizeX && InputManager::mousePos.y >= posY && InputManager::mousePos.y <= posY + sizeY)
    {
        return true;
    }
    return false;
}
bool RadioButton::isMouseDownM(const int key)
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
bool RadioButton::isMouseUpM(const int key)
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
bool RadioButton::isMousePressM(const int key)
{
    if (isMouseHover() && InputManager::isButton(key))
    {
        return true;
    }
    return false;
}