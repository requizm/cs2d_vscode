#include "RadioButton.hpp"
#if defined(WIN32) && defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

RadioButtonElement::RadioButtonElement() : Label() {}

RadioButtonElement::RadioButtonElement(const std::string &text,
                                       Vector2<int> position,
                                       TextRenderer &textRenderer, int index,
                                       const Vector3<float> &buttonColor,
                                       const Vector3<float> &textColor,
                                       float scale)
    : Label(text, position, textRenderer, scale, textColor,
            UIObjectType::RADIOBUTTON),
      selected(false)
{
    this->setButtonColor(buttonColor);
    this->index = index;
}

RadioButtonElement::RadioButtonElement(const std::string &text,
                                       Vector2<int> position,
                                       TextRenderer &textRenderer, int index, Object *par,
                                       const Vector3<float> &buttonColor,
                                       const Vector3<float> &textColor,
                                       float scale)
    : Label(text, position, textRenderer, par, scale, textColor, UIObjectType::RADIOBUTTON),
      selected(false)
{
    this->setButtonColor(buttonColor);
    this->index = index;
}

RadioButtonElement::~RadioButtonElement() = default;

void RadioButtonElement::Draw(SpriteRenderer &spriteRenderer,
                              SquareRenderer &squareRenderer)
{
    if (!text.empty())
        this->rend->RenderText(
            text,
            Vector2<int>(GetPosition().x + labelSize.y / 2 + 2.0F,
                         GetPosition().y),
            scale, textCurrentColor);
    squareRenderer.ui_RenderFilledCircle(
        Vector2<int>(GetPosition().x, GetPosition().y + labelSize.y / 2),
        Vector2<int>(labelSize.y / 2), Vector3<float>(0.21F));
    squareRenderer.ui_RenderEmptyCircle(
        Vector2<int>(GetPosition().x, GetPosition().y + labelSize.y / 2),
        Vector2<int>(labelSize.y / 2), currentOutlineColor);
    if (selected)
    {
        squareRenderer.ui_RenderFilledCircle(
            Vector2<int>(GetPosition().x, GetPosition().y + labelSize.y / 2),
            Vector2<int>(labelSize.y / 2 - labelSize.y / 4), currentColor);
    }
}

void RadioButtonElement::Update()
{
    if (isMouseHover())
    {
        textCurrentColor = mouseHoverColor;
        currentColor = mouseHoverColor;  // gereksiz
        currentOutlineColor = mouseHoverOutlineColor;
    }
    else
    {
        textCurrentColor = textColor;
        currentColor = mouseHoverColor;  // gereksiz
        currentOutlineColor = outlineColor;
    }
}

void RadioButtonElement::ProcessInput()
{
    isMouseDownM(MOUSE_BUTTON_LEFT);
    isMouseUpM(MOUSE_BUTTON_LEFT);
}

Vector2<int> RadioButtonElement::GetPosition()
{
    if (IsParent()) return this->position + parent->GetPosition();
    return this->position;
}
Vector2<int> RadioButtonElement::GetLocalPosition()
{
    if (IsParent()) return this->position - parent->GetPosition();
    return Vector2<int>(0);
}
Vector2<int> RadioButtonElement::GetSize()
{
    Vector2<int> ps;
    ps.x = (GetPosition().x + labelSize.y / 2 + 2 + labelSize.x) -
           (GetPosition().x - labelSize.y / 2);
    ps.y = labelSize.y;
    return ps;
}

int RadioButtonElement::getIndex() { return this->index; }

void RadioButtonElement::setMouseHoverColor(const Vector3<float> &color)
{
    this->mouseHoverColor = color;
}

void RadioButtonElement::setButtonColor(const Vector3<float> &color)
{
    this->buttonColor = color;
}

void RadioButtonElement::setMouseHoverOutlineColor(const Vector3<float> &color)
{
    this->mouseHoverOutlineColor = color;
}
void RadioButtonElement::setOutlineColor(const Vector3<float> &color)
{
    this->outlineColor = color;
}

void RadioButtonElement::OnEnable() {}
void RadioButtonElement::OnDisable()
{
    // this->selected = false;
}

void RadioButtonElement::SetPosition(const Vector2<int> &position)
{
    this->position = position;
}

bool RadioButtonElement::isMouseHover()
{
    if (IsEnable() && mouseEvents) return isMouseHoverM();
    return false;
}
bool RadioButtonElement::isMouseDown() { return this->isDown; }
bool RadioButtonElement::isMouseUp() { return this->isUp; }
bool RadioButtonElement::isMousePress()
{
    if (IsEnable()) return isMousePressM(MOUSE_BUTTON_LEFT);
    return false;
}

bool RadioButtonElement::isMouseHoverM()
{
    const int posX = static_cast<int>(this->GetPosition().x - labelSize.y / 2);
    const int posY = static_cast<int>(this->GetPosition().y);

    int sizeX = static_cast<int>(this->GetSize().x);
    int sizeY = static_cast<int>(this->GetSize().y);

    if (InputManager::mousePos.x >= posX &&
        InputManager::mousePos.x <= posX + sizeX &&
        InputManager::mousePos.y >= posY &&
        InputManager::mousePos.y <= posY + sizeY)
    {
        return true;
    }
    return false;
}
bool RadioButtonElement::isMouseDownM(MouseKeys key)
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
bool RadioButtonElement::isMouseUpM(MouseKeys key)
{
    if (InputManager::isButtonUp(key) && isPressed)
    {
        isPressed = false;
        isUp = true;
        return true;
    }
    if (isUp) isUp = false;
    return false;
}
bool RadioButtonElement::isMousePressM(MouseKeys key)
{
    if (isMouseHover() && InputManager::isButton(key))
    {
        return true;
    }
    return false;
}

RadioButton::RadioButton() = default;

RadioButton::RadioButton(TextRenderer &renderer, Vector2<int> position,
                         int y_sep)
    : UIObject(position, Vector2<int>(1.1), 1.0F, renderer)
{
    this->y_sep = y_sep;
}

RadioButton::RadioButton(TextRenderer &renderer, Vector2<int> position,
                         int y_sep, Object *par)
    : UIObject(position, Vector2<int>(1.1), 1.0F, renderer, par)
{
    this->y_sep = y_sep;
}

RadioButton::~RadioButton()
{
    for (auto &element : elements)
    {
        delete element;
    }
    RemoveParent();
}

void RadioButton::Draw(SpriteRenderer &spriteRenderer,
                       SquareRenderer &squareRenderer)
{
    if (IsEnable())
    {
        for (auto &element : elements)
        {
            element->Draw(spriteRenderer, squareRenderer);
        }
    }
}

void RadioButton::AddChangeListener(
    std::function<void(RadioButtonElement *, RadioButtonElement *)> func)
{
    listeners.push_back(std::move(func));
}

void RadioButton::Clear()
{
    this->elements.clear();
    i = 0;
}

void RadioButton::AddElement(const std::string &text,
                             const Vector3<float> &buttonColor,
                             const Vector3<float> &textColor, float scale)
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    RadioButtonElement *r = new RadioButtonElement(
        text, Vector2<int>(position.x, position.y + y_sep * i), *rend, i++,
        buttonColor, textColor, scale);
    r->SetSize(Vector2<int>(300, 300));
    r->setMouseHoverColor(Vector3<float>(0.9F));
    r->setOutlineColor(Vector3<float>(0.58F));
    r->setMouseHoverOutlineColor(Vector3<float>(0.9F));
    r->SetParent(this);
    this->elements.push_back(r);
}

void RadioButton::Update()
{
    if (IsEnable() && mouseEvents)
    {
        for (std::vector<int>::size_type i = 0; i != elements.size(); i++)
        {
            elements[i]->Update();
        }
    }
}

void RadioButton::ProcessInput()
{
    if (mouseEvents && IsEnable())
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
    return nullptr;
}
