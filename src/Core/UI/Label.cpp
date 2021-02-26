#include "Label.hpp"

Label::Label() : UIObject() {}

Label::Label(const std::string &text, Vector2<int> position,
             TextRenderer &renderer, float scale, const Vector3<float> &color,
             UIObjectType type, LabelType ltype)
    : UIObject(position, renderer.CalculateSize(text, scale), scale, renderer, type)
{
    this->textColor = color;
    this->text = text;
    this->textHoverColor = Vector3<float>(0.78F);
    this->textClickColor = Vector3<float>(1.0F);
    this->textCurrentColor = color;
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
    this->textColor = color;
    this->text = text;
    this->textHoverColor = Vector3<float>(0.78F);
    this->textClickColor = Vector3<float>(1.0F);
    this->textCurrentColor = color;
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
    this->textColor = color;
    this->textHoverColor = Vector3<float>(0.78F);
    this->textClickColor = Vector3<float>(1.0F);
    this->textCurrentColor = color;
}

Label::Label(Vector2<int> position, const Vector2<int> &size, TextRenderer &renderer, Object *par, float scale,
             const Vector3<float> &color, UIObjectType type)
    : UIObject(position, size, scale, renderer, type, par)
{
    this->textColor = color;
    this->textHoverColor = Vector3<float>(0.78F);
    this->textClickColor = Vector3<float>(1.0F);
    this->textCurrentColor = color;
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
        this->rend->RenderText(text, position, scale, textCurrentColor);
}

void Label::Update()
{
    if (IsEnable() && mouseEvents)
    {
        if (!isPressed && !text.empty())
        {
            if (isMouseHover())
            {
                textCurrentColor = textHoverColor;
            }
            else
            {
                textCurrentColor = textColor;
            }
        }
    }
}

void Label::ProcessInput()
{
}

void Label::setText(const std::string &text)
{
    this->text = text;
    this->labelSize = rend->CalculateSize(text, scale);
}

bool Label::isMouseHover()
{
    if (InputManager::mousePos.x >= position.x &&
        InputManager::mousePos.x <= position.x + labelSize.x &&
        InputManager::mousePos.y >= position.y &&
        InputManager::mousePos.y <= position.y + labelSize.y)
    {
        return true;
    }
    return false;
}

std::string Label::getText() const { return text; }

void Label::setTextColor(const Vector3<float> &color)
{
    this->textColor = color;
}

void Label::setTextHoverColor(const Vector3<float> &color)
{
    this->textHoverColor = color;
}

void Label::setTextClickColor(const Vector3<float> &color)
{
    this->textClickColor = color;
}

void Label::SetMouseState(bool &variable, bool value) { variable = value; }

void Label::onMouseDown()
{
    if (IsEnable() && isMouseHover())
    {
        textCurrentColor = textClickColor;
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
            textCurrentColor = textColor;
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
