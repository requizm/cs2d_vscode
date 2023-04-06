#include "RadioButton.hpp"

#include "../Manager/InputManager.hpp"
#include "../Manager/Logger.hpp"
#include "../Manager/MemoryOverride/MemoryOverride.hpp"

#if defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

RadioButtonElement::RadioButtonElement(const std::string &text,
                                       const Vector2<int> &position,
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

RadioButtonElement::~RadioButtonElement()
{
    UIObject::removeParent();
}

void RadioButtonElement::Draw(SpriteRenderer &spriteRenderer,
                              SquareRenderer &squareRenderer)
{
    if (!text.empty())
    {
        Vector2<int> pos = Vector2<int>(getPosition().x + labelSize.y / 2 + 2.0F, getPosition().y);
        this->rend->RenderText(text, pos, scale, labelCurrentColor);
    }

    squareRenderer.ui_RenderFilledCircle(
        Vector2<int>(getPosition().x, getPosition().y + labelSize.y / 2),
        Vector2<int>(labelSize.y / 2), Vector3<float>(0.21F));
    squareRenderer.ui_RenderEmptyCircle(
        Vector2<int>(getPosition().x, getPosition().y + labelSize.y / 2),
        Vector2<int>(labelSize.y / 2), currentOutlineColor);
    if (selected)
    {
        squareRenderer.ui_RenderFilledCircle(
            Vector2<int>(getPosition().x, getPosition().y + labelSize.y / 2),
            Vector2<int>(labelSize.y / 2 - labelSize.y / 4), currentColor);
    }
}

void RadioButtonElement::Update()
{
    if (isMouseHover())
    {
        labelCurrentColor = mouseHoverColor;
        currentColor = mouseHoverColor;  // gereksiz
        currentOutlineColor = mouseHoverOutlineColor;
    }
    else
    {
        labelCurrentColor = labelColor;
        currentColor = mouseHoverColor;  // gereksiz
        currentOutlineColor = outlineColor;
    }
}

void RadioButtonElement::ProcessInput()
{
    isMouseDownM(MOUSE_BUTTON_LEFT);
    isMouseUpM(MOUSE_BUTTON_LEFT);
}

Vector2<int> RadioButtonElement::getSize()
{
    Vector2<int> ps;
    ps.x = (getPosition().x + labelSize.y / 2 + 2 + labelSize.x) -
           (getPosition().x - labelSize.y / 2);
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

bool RadioButtonElement::isMouseHover()
{
    if (isEnable() && isMouseEvents()) return isMouseHoverM();
    return false;
}
bool RadioButtonElement::isMouseDown() { return this->isDown; }
bool RadioButtonElement::isMouseUp() { return this->isUp; }
bool RadioButtonElement::isMousePress()
{
    if (isEnable()) return isMousePressM(MOUSE_BUTTON_LEFT);
    return false;
}

bool RadioButtonElement::isMouseHoverM()
{
    const int posX = static_cast<int>(this->getPosition().x - labelSize.y / 2);
    const int posY = static_cast<int>(this->getPosition().y);

    int sizeX = static_cast<int>(this->getSize().x);
    int sizeY = static_cast<int>(this->getSize().y);

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

RadioButton::RadioButton(TextRenderer &renderer, const Vector2<int> &position,
                         int y_sep)
    : UIObject(position, 1.0F, renderer)
{
    this->y_sep = y_sep;
}

RadioButton::~RadioButton()
{
    UIObject::removeParent();
}

void RadioButton::Draw(SpriteRenderer &spriteRenderer,
                       SquareRenderer &squareRenderer)
{
    if (isVisible() && isEnable())
    {
        for (auto &element : elements)
        {
            element->Draw(spriteRenderer, squareRenderer);
        }
    }
}

void RadioButton::AddListener(
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
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    auto r = std::make_shared<RadioButtonElement>(
        text, Vector2<int>(0, y_sep * i), *rend, i,
        buttonColor, textColor, scale);
    r->setSize(300, 300);
    r->setMouseHoverColor(Vector3<float>(0.9F));
    r->setOutlineColor(Vector3<float>(0.58F));
    r->setMouseHoverOutlineColor(Vector3<float>(0.9F));
    r->setParent(shared_from_this());
    this->elements.push_back(r);
    i += 1;
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
                        f(elements[old].get(), elements[selectedIndex].get());
                    }
                    catch (const std::exception &e)
                    {
                        f(nullptr, elements[selectedIndex].get());
                    }
                }
                break;
            }
        }
    }
}

void RadioButton::Select(int index)
{
    ASSERTM_ERROR(i >= 0 && i < elements.size(), "boyle bir item indexi yok");

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
        return elements.at(selectedIndex).get();
    }
    return nullptr;
}
