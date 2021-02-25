#include "Label.hpp"

Label::Label() : UIObject() {}

Label::Label(const std::string &text, Vector2<int> position,
             TextRenderer &renderer, float scale, const Vector3<float> &color,
             UIObjectType type, LabelType ltype)
    : UIObject(position, renderer.CalculateSize(text, scale), scale, renderer, type)
{
    this->labelColor = color;
    this->text = text;
    this->labelMouseHoverColor = Vector3<float>(0.78F);
    this->labelClickColor = Vector3<float>(1.0F);
    this->labelCurrentColor = color;
    this->labelSize = this->rend->CalculateSize(text, scale);
    this->labelType = ltype;

    if ((objType == UIObjectType::LABEL && labelType == LabelType::CLICKABLE) ||
        objType == UIObjectType::RADIOBUTTON)
    {
        mDown = std::bind(&Label::onMouseDown, this);
        InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);

        mUp = std::bind(&Label::onMouseUp, this);
        InputManager::addListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
        ObjectManager::listenerObjCount++;
    }
}

Label::Label(const std::string &text, Vector2<int> position,
             TextRenderer &renderer, Object *par, float scale,
             const Vector3<float> &color,
             UIObjectType type,
             LabelType ltype) : UIObject(position, renderer.CalculateSize(text, scale), scale, renderer, type, par)
{
    this->labelColor = color;
    this->text = text;
    this->labelMouseHoverColor = Vector3<float>(0.78F);
    this->labelClickColor = Vector3<float>(1.0F);
    this->labelCurrentColor = color;
    this->labelSize = this->rend->CalculateSize(text, scale);
    this->labelType = ltype;

    if ((objType == UIObjectType::LABEL && labelType == LabelType::CLICKABLE) ||
        objType == UIObjectType::RADIOBUTTON)
    {
        mDown = std::bind(&Label::onMouseDown, this);
        InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);

        mUp = std::bind(&Label::onMouseUp, this);
        InputManager::addListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
        ObjectManager::listenerObjCount++;
    }
}

Label::Label(Vector2<int> position, const Vector2<int> &size, TextRenderer &renderer, float scale,
             const Vector3<float> &color, UIObjectType type)
    : UIObject(position, size, scale, renderer, type)
{
    this->labelColor = color;
    this->labelMouseHoverColor = Vector3<float>(0.78F);
    this->labelClickColor = Vector3<float>(1.0F);
    this->labelCurrentColor = color;
}

Label::Label(Vector2<int> position, const Vector2<int> &size, TextRenderer &renderer, Object *par,float scale,
             const Vector3<float> &color, UIObjectType type)
    : UIObject(position, size, scale, renderer, type, par)
{
    this->labelColor = color;
    this->labelMouseHoverColor = Vector3<float>(0.78F);
    this->labelClickColor = Vector3<float>(1.0F);
    this->labelCurrentColor = color;
}

Label::Label(Vector2<int> position, Vector2<int> size, float scale,
             UIObjectType type, LabelType ltype)
    : UIObject(position, size, scale, type)
{
    this->labelType = ltype;
    if ((objType == UIObjectType::LABEL && labelType == LabelType::CLICKABLE) ||
        objType == UIObjectType::RADIOBUTTON)
    {
        mDown = std::bind(&Label::onMouseDown, this);
        InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);

        mUp = std::bind(&Label::onMouseUp, this);
        InputManager::addListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
        ObjectManager::listenerObjCount++;
    }
}

Label::~Label()
{
    if ((objType == UIObjectType::LABEL && labelType == LabelType::CLICKABLE) ||
        objType == UIObjectType::RADIOBUTTON)
    {
        InputManager::removeListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
        InputManager::removeListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
        ObjectManager::listenerObjCount--;
    }
    RemoveParent();
}

void Label::Draw()
{
    if (IsEnable() && !text.empty())
        this->rend->RenderText(text, position, scale, labelCurrentColor);
}

void Label::DrawForButton(const bool center)
{
    if (IsEnable() && !text.empty())
        this->rend->RenderText(text, getPositionForButton(center), scale,
                               labelCurrentColor);
}

void Label::Update()
{
    if (IsEnable() && mouseEvents)
    {
        if (!isPressed && !text.empty())
        {
            if (isMouseHover())
            {
                labelCurrentColor = labelMouseHoverColor;
            }
            else
            {
                labelCurrentColor = labelColor;
            }
        }
    }
}

void Label::ProcessInput()
{
    if (mouseEvents)
    {
        isMouseDownM(MOUSE_BUTTON_LEFT);
        isMouseUpM(MOUSE_BUTTON_LEFT);
    }
}

std::string Label::getText() const { return this->text; }

Vector2<int> Label::getLabelSize() const { return this->labelSize; }

void Label::setText(const std::string &text)
{
    this->text = text;
    this->labelSize = rend->CalculateSize(text, scale);
}

bool Label::isMouseHover()
{
    return isMouseHoverM();
}

bool Label::isMouseDown()
{
    if (downTrigger && isPressed)
    {
        downTrigger = false;
        return true;
    }
    return false;
}

bool Label::isMouseUp()
{
    return isUp;
}

bool Label::isMousePress()
{
    return isMousePressM(MOUSE_BUTTON_LEFT);
}

Vector2<int> Label::getPositionForButton(const bool center)  //FIXME: silinecek
{
    if (IsParent())
    {
        if (objType == UIObjectType::TEXTBUTTON)
        {
            Vector2<int> dif = GetSize() - getLabelSize();
            dif.y /= 2;
            if (center)
            {
                dif.x /= 2;
                return parent->GetPosition() + this->position + dif;
            }
            return parent->GetPosition() + this->position +
                   Vector2<int>(0, dif.y);
        }
        return parent->GetPosition() + this->position;
    }
    if (objType == UIObjectType::TEXTBUTTON)
    {
        Vector2<int> dif = GetSize() - getLabelSize();
        dif.y /= 2;
        if (center)
        {
            dif.x /= 2;
        }
        return this->position + dif;
    }
    return this->position;
}

Vector3<float> Label::getLabelColor() const { return this->labelColor; }

Vector3<float> Label::getLabelMouseHoverColor() const
{
    return this->labelMouseHoverColor;
}

Vector3<float> Label::getLabelClickColor() const
{
    return this->labelClickColor;
}

void Label::setLabelColor(const Vector3<float> &color)
{
    this->labelColor = color;
}

void Label::setLabelMouseHoverColor(const Vector3<float> &color)
{
    this->labelMouseHoverColor = color;
}

void Label::setLabelClickColor(const Vector3<float> &color)
{
    this->labelClickColor = color;
}

bool Label::isMouseHoverM()
{
    const int posX = static_cast<int>(this->GetPosition().x);  //FIXME: gereksiz castler
    const int posY = static_cast<int>(this->GetPosition().y);

    const int labelSizeX = static_cast<int>(this->labelSize.x);
    const int labelSizeY = static_cast<int>(this->labelSize.y);

    if (InputManager::mousePos.x >= posX &&
        InputManager::mousePos.x <= posX + labelSizeX &&
        InputManager::mousePos.y >= posY &&
        InputManager::mousePos.y <= posY + labelSizeY)
    {
        return true;
    }
    return false;
}

bool Label::isMouseDownM(MouseKeys key)
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

bool Label::isMouseUpM(MouseKeys key)
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

bool Label::isMousePressM(MouseKeys key)
{
    if (isMouseHover() && InputManager::isButton(key))
    {
        return true;
    }
    return false;
}

void Label::SetMouseState(bool &variable, bool value) { variable = value; }

void Label::onMouseDown()
{
    if (IsEnable() && isMouseHover())
    {
        downTrigger = true;
        labelCurrentColor = labelClickColor;
        isPressed = true;
        for (auto &f : listenersDown)
        {
            f();
        }
    }
}

void Label::onMouseUp()
{
    if (isPressed)
    {
        if (IsEnable() && isMouseHover())
        {
            labelCurrentColor = labelColor;
            for (auto &f : listenersUp)
            {
                f();
            }
        }
        isPressed = false;
    }
}

void Label::addListenerDown(std::function<void()> func)
{
    listenersDown.push_back(std::move(func));
}

void Label::addListenerUp(std::function<void()> func)
{
    listenersUp.push_back(std::move(func));
}
