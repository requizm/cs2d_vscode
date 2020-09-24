#include "RadioButton.h"

RadioButtonElement::RadioButtonElement() = default;

RadioButtonElement::RadioButtonElement(const std::string &text, glm::vec2 position, TextRenderer &textRenderer, glm::vec3 buttonColor, glm::vec3 textColor, float scale)
    : Label(text, position, textRenderer, scale, textColor, UIObjectType::RADIOBUTTON), selected(false)
{
    this->setButtonColor(buttonColor);
}

RadioButtonElement::~RadioButtonElement() = default;

void RadioButtonElement::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    if (!text.empty())
        this->rend->RenderText(text, glm::vec2(getPosition().x + labelSize.y / 2 + 2.0F, getPosition().y), scale, labelCurrentColor);
    squareRenderer.ui_RenderFilledCircle(glm::vec2(getPosition().x, getPosition().y + labelSize.y / 2), glm::vec2(labelSize.y / 2), glm::vec3(0.21F));
    squareRenderer.ui_RenderEmptyCircle(glm::vec2(getPosition().x, getPosition().y + labelSize.y / 2), glm::vec2(labelSize.y / 2), currentOutlineColor);
    if (selected)
    {
        squareRenderer.ui_RenderFilledCircle(glm::vec2(getPosition().x, getPosition().y + labelSize.y / 2), glm::vec2(labelSize.y / 2 - labelSize.y / 4), currentColor);
    }
}

void RadioButtonElement::Update(const float dt)
{
    if (isMouseHover())
    {
        labelCurrentColor = mouseHoverColor;
        currentColor = mouseHoverColor; //gereksiz
        currentOutlineColor = mouseHoverOutlineColor;
    }
    else
    {
        labelCurrentColor = labelColor;
        currentColor = mouseHoverColor; //gereksiz
        currentOutlineColor = outlineColor;
    }
}

void RadioButtonElement::ProcessInput()
{

    isMouseDownM(GLFW_MOUSE_BUTTON_LEFT);
    isMouseUpM(GLFW_MOUSE_BUTTON_LEFT);
}

glm::vec2 RadioButtonElement::getPosition()
{
    if (isParent())
        return this->position + parent->getPosition();
    return this->position;
}
glm::vec2 RadioButtonElement::getLocalPosition()
{
    if (isParent())
        return this->position - parent->getPosition();
    return glm::vec2(0.0F);
}
glm::vec2 RadioButtonElement::getSize()
{
    glm::vec2 ps;
    ps.x = (getPosition().x + labelSize.y / 2 + 2.0F + labelSize.x) - (getPosition().x - labelSize.y / 2);
    ps.y = labelSize.y;
    return ps;
}

void RadioButtonElement::setMouseHoverColor(const glm::vec3 color)
{
    this->mouseHoverColor = color;
}

void RadioButtonElement::setButtonColor(const glm::vec3 color)
{
    this->buttonColor = color;
}

void RadioButtonElement::setMouseHoverOutlineColor(const glm::vec3 color)
{
    this->mouseHoverOutlineColor = color;
}
void RadioButtonElement::setOutlineColor(const glm::vec3 color)
{
    this->outlineColor = color;
}

void RadioButtonElement::OnEnable()
{
}
void RadioButtonElement::OnDisable()
{
    //this->selected = false;
}

void RadioButtonElement::setPosition(const glm::vec2 position)
{
    this->position = position;
}
void RadioButtonElement::setPosition(const int x, const int y)
{
    this->position.x = x;
    this->position.y = y;
}

bool RadioButtonElement::isMouseHover()
{
    if (isEnable() && isMouseEvents())
        return isMouseHoverM();
    return false;
}
bool RadioButtonElement::isMouseDown()
{
    return this->isDown;
}
bool RadioButtonElement::isMouseUp()
{
    return this->isUp;
}
bool RadioButtonElement::isMousePress()
{
    if (isEnable())
        return isMousePressM(GLFW_MOUSE_BUTTON_LEFT);
    return false;
}

bool RadioButtonElement::isMouseHoverM()
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
bool RadioButtonElement::isMouseDownM(const int key)
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
bool RadioButtonElement::isMouseUpM(const int key)
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
bool RadioButtonElement::isMousePressM(const int key)
{
    if (isMouseHover() && InputManager::isButton(key))
    {
        return true;
    }
    return false;
}

RadioButton::RadioButton() = default;

RadioButton::RadioButton(TextRenderer &renderer, glm::vec2 position, int y_sep) : UIObject(position, 1.0F, renderer)
{
    this->y_sep = y_sep;
}

RadioButton::~RadioButton() = default;

void RadioButton::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    if (isVisible() && isEnable())
    {
        for (auto &element : elements)
        {
            element->Draw(spriteRenderer, squareRenderer);
        }
    }
}

void RadioButton::AddListener(std::function<void()> func)
{
    listeners.push_back(std::move(func));
}

void RadioButton::Clear()
{
    this->elements.clear();
    i = 0;
}

void RadioButton::AddElement(const std::string &text, glm::vec3 buttonColor, glm::vec3 textColor, float scale)
{
    RadioButtonElement *r = new RadioButtonElement(text, glm::vec2(position.x, position.y + y_sep * i), *rend, buttonColor, textColor, scale);
    r->setSize(300, 300);
    r->setMouseHoverColor(glm::vec3(0.9F));
    r->setOutlineColor(glm::vec3(0.58F));
    r->setMouseHoverOutlineColor(glm::vec3(0.9F));
    r->setParent(this);
    r->index = i;

    this->elements.push_back(r);

    i = i + 1;
}

void RadioButton::Update(const float dt)
{
    if (isEnable() && isMouseEvents())
    {
        int i = 0;
        for (auto &element : elements)
        {
            element->Update(dt);
            if (element->isMouseDown())
            {
                Select(i);
            }
            i = i + 1;
        }
    }
}

void RadioButton::ProcessInput()
{
    if (isMouseEvents() && isEnable())
    {
        for (auto &element : elements)
        {
            element->ProcessInput();
        }
    }
}

void RadioButton::Select(int index)
{
    if (selectedIndex != elements.at(index)->index)
    {
        for (auto &element : elements)
        {
            element->selected = false;
        }
        elements.at(index)->selected = true;
        selectedIndex = elements.at(index)->index;

        for (auto &a : listeners)
        {
            a();
        }
        return;
    }
    //zaten bu secili
}

RadioButtonElement *RadioButton::GetSelectedElement()
{
    if (selectedIndex != -1)
    {
        return elements.at(selectedIndex);
    }
}
