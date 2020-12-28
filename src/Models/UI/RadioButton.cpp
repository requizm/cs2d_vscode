#include "RadioButton.hpp"

RadioButtonElement::RadioButtonElement() = default;

RadioButtonElement::RadioButtonElement(const std::string &text, Vector2<float> position, TextRenderer &textRenderer, int index, Vector3<float> buttonColor, Vector3<float> textColor, float scale)
    : Label(text, position, textRenderer, scale, textColor, UIObjectType::RADIOBUTTON), selected(false)
{
    this->setButtonColor(buttonColor);
    this->index = index;
}

RadioButtonElement::~RadioButtonElement() = default;

void RadioButtonElement::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    if (!text.empty())
        this->rend->RenderText(text, Vector2<float>(getPosition().x + labelSize.y / 2 + 2.0F, getPosition().y), scale, labelCurrentColor);
    squareRenderer.ui_RenderFilledCircle(Vector2<float>(getPosition().x, getPosition().y + labelSize.y / 2), Vector2<float>(labelSize.y / 2), Vector3<float>(0.21F));
    squareRenderer.ui_RenderEmptyCircle(Vector2<float>(getPosition().x, getPosition().y + labelSize.y / 2), Vector2<float>(labelSize.y / 2), currentOutlineColor);
    if (selected)
    {
        squareRenderer.ui_RenderFilledCircle(Vector2<float>(getPosition().x, getPosition().y + labelSize.y / 2), Vector2<float>(labelSize.y / 2 - labelSize.y / 4), currentColor);
    }
}

void RadioButtonElement::Update()
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

Vector2<float> RadioButtonElement::getPosition()
{
    if (isParent())
        return this->position + parent->getPosition();
    return this->position;
}
Vector2<float> RadioButtonElement::getLocalPosition()
{
    if (isParent())
        return this->position - parent->getPosition();
    return Vector2<float>(0.0F);
}
Vector2<float> RadioButtonElement::getSize()
{
    Vector2<float> ps;
    ps.x = (getPosition().x + labelSize.y / 2 + 2.0F + labelSize.x) - (getPosition().x - labelSize.y / 2);
    ps.y = labelSize.y;
    return ps;
}

int RadioButtonElement::getIndex()
{
    return this->index;
}

void RadioButtonElement::setMouseHoverColor(const Vector3<float> color)
{
    this->mouseHoverColor = color;
}

void RadioButtonElement::setButtonColor(const Vector3<float> color)
{
    this->buttonColor = color;
}

void RadioButtonElement::setMouseHoverOutlineColor(const Vector3<float> color)
{
    this->mouseHoverOutlineColor = color;
}
void RadioButtonElement::setOutlineColor(const Vector3<float> color)
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

void RadioButtonElement::setPosition(const Vector2<float> position)
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

RadioButton::RadioButton(TextRenderer &renderer, Vector2<float> position, int y_sep) : UIObject(position, 1.0F, renderer)
{
    this->y_sep = y_sep;
}

RadioButton::~RadioButton()
{
    for (auto &element : elements)
    {
        delete element;
    }
}

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

void RadioButton::AddListener(std::function<void(RadioButtonElement *, RadioButtonElement *)> func)
{
    listeners.push_back(std::move(func));
}

void RadioButton::Clear()
{
    this->elements.clear();
    i = 0;
}

void RadioButton::AddElement(const std::string &text, Vector3<float> buttonColor, Vector3<float> textColor, float scale)
{
    RadioButtonElement *r = new RadioButtonElement(text, Vector2<float>(position.x, position.y + y_sep * i), *rend, i++, buttonColor, textColor, scale);
    r->setSize(300, 300);
    r->setMouseHoverColor(Vector3<float>(0.9F));
    r->setOutlineColor(Vector3<float>(0.58F));
    r->setMouseHoverOutlineColor(Vector3<float>(0.9F));
    r->setParent(this, true);
    this->elements.push_back(r);
}

void RadioButton::Update()
{
    if (isEnable() && isMouseEvents())
    {
        for (std::vector<int>::size_type i = 0; i != elements.size(); i++)
        {
            elements[i]->Update();
        }
    }
}

void RadioButton::ProcessInput()
{
    if (isMouseEvents() && isEnable())
    {
        for (std::vector<int>::size_type i = 0; i != elements.size(); i++)
        {
            elements[i]->ProcessInput();
            if (elements[i]->isMouseDown() && selectedIndex != i)
            {
                int old = selectedIndex;
                if (selectedIndex != -1)
                {
                    elements[selectedIndex]->selected = false;
                }

                elements[i]->selected = true;
                selectedIndex = i;

                for (auto &f : listeners)
                {
                    try
                    {
                        f(elements[old], elements[selectedIndex]);
                    }
                    catch (const std::exception &e)
                    {
                        f(nullptr, elements[selectedIndex]);
                    }
                }
                break;
            }
        }
    }
}

void RadioButton::Select(int index)
{
    if (selectedIndex != index)
    {
        int old = selectedIndex;
        if (selectedIndex != -1)
        {
            elements[selectedIndex]->selected = false;
        }

        elements.at(index)->selected = true;
        selectedIndex = index;
    }
}

RadioButtonElement *RadioButton::GetSelectedElement()
{
    if (selectedIndex != -1)
    {
        return elements.at(selectedIndex);
    }
}
