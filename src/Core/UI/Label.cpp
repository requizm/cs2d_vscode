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

Label::Label(Vector2<int> position, const Vector2<int> &size, TextRenderer &renderer, Object *par, float scale,
             const Vector3<float> &color, UIObjectType type)
    : UIObject(position, size, scale, renderer, type, par)
{
    this->labelColor = color;
    this->labelMouseHoverColor = Vector3<float>(0.78F);
    this->labelClickColor = Vector3<float>(1.0F);
    this->labelCurrentColor = color;
}

Label::~Label()
{
    if ((objType == UIObjectType::LABEL && labelType == LabelType::CLICKABLE) ||
        objType == UIObjectType::RADIOBUTTON)
    {
        InputManager::removeListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
        InputManager::removeListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
    }
    RemoveParent();
}

void Label::Draw()
{
    if (IsEnable() && !text.empty())
        this->rend->RenderText(text, position, scale, labelCurrentColor);
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
    if (InputManager::mousePos.x >= position.x &&
        InputManager::mousePos.x <= position.x + labelSize.x &&
        InputManager::mousePos.y >= position.y &&
        InputManager::mousePos.y <= position.y + labelSize.y)
    {
        return true;
    }
    return false;
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

void Label::SetMouseState(bool &variable, bool value) { variable = value; }

void Label::onMouseDown()
{
    if (IsEnable() && isMouseHover())
    {
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
