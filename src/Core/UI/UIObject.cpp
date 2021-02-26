#include "UIObject.hpp"

UIObject::UIObject() : Object()
{
    this->objType = UIObjectType::UIOBJECT;
}

UIObject::UIObject(UIObjectType type) : Object()
{
    this->objType = type;
}

UIObject::UIObject(UIObjectType type, Object *par) : Object(Vector2<int>(0, 0), Vector2<int>(0, 0), 0, par)
{
    this->objType = type;
}

UIObject::UIObject(Vector2<int> position, Vector2<int> size, float scale,
                   TextRenderer &renderer) : Object(position, size, 0)
{
    this->objType = UIObjectType::UIOBJECT;
    this->scale = scale;
    this->rend = &renderer;
}

UIObject::UIObject(Vector2<int> position, Vector2<int> size, float scale,
                   TextRenderer &renderer, Object *par) : Object(position, size, 0, par)
{
    this->objType = UIObjectType::UIOBJECT;
    this->scale = scale;
    this->rend = &renderer;
}

UIObject::UIObject(Vector2<int> position, Vector2<int> size, float scale,
                   TextRenderer &renderer, UIObjectType type) : Object(position, size, 0)
{
    this->objType = type;
    this->scale = scale;
    this->rend = &renderer;
}

UIObject::UIObject(Vector2<int> position, Vector2<int> size, float scale,
                   TextRenderer &renderer, UIObjectType type, Object *par) : Object(position, size, 0, par)
{
    this->objType = type;
    this->scale = scale;
    this->rend = &renderer;
}

UIObject::UIObject(Vector2<int> position, Vector2<int> size, float scale) : Object(position, size, 0)
{
    this->objType = UIObjectType::UIOBJECT;
    this->scale = scale;
}

UIObject::UIObject(Vector2<int> position, Vector2<int> size, float scale, Object *par) : Object(position, size, 0, par)
{
    this->objType = UIObjectType::UIOBJECT;
    this->scale = scale;
}

UIObject::UIObject(Vector2<int> position, Vector2<int> size, float scale,
                   UIObjectType type) : Object(position, size, 0)
{
    this->objType = type;
    this->scale = scale;
}

UIObject::UIObject(Vector2<int> position, Vector2<int> size, float scale,
                   UIObjectType type, Object *par) : Object(position, size, 0, par)
{
    this->objType = type;
    this->scale = scale;
}

UIObject::~UIObject() = default;

bool onenabletrigger = false;
void UIObject::Update() {}

void UIObject::OnEnable() {}

void UIObject::OnDisable()
{
    isPressed = false;
    isUp = false;
    isDown = false;
}

void UIObject::ProcessInput() {}

void UIObject::Draw() {}

void UIObject::Draw(SquareRenderer &squareRenderer)
{
}

void UIObject::Draw(SpriteRenderer &spriteRenderer,
                    SquareRenderer &squareRenderer)
{
}

void UIObject::SetPosition(const Vector2<int> &value)
{
    Object::SetPosition(value);
}

void UIObject::SetSize(const Vector2<int> &value) {
    Object::SetSize(value);
}

void UIObject::SetLocalPosition(const Vector2<int> &value)
{
    if (IsParent())
        SetPosition(parent->GetPosition() + value);
    else
        LOG_WARNING("parenti olmayan objeye local pos atamaya calsiiyon");
}

void UIObject::SetParent(Object *value)
{
    if (IsParent())
    {
        WRITE_WARNING("parent'i olan objeye parent atamaya calisiyon");
        return;
    }
    Object::SetParent(value);
    localPosition = parent->GetPosition() - GetPosition();
}

void UIObject::SetTransform(const Matrix4<float> &value)
{
    Object::SetTransform(value);
}

void UIObject::SetParentCenterPos()
{
    if (IsParent())
        SetLocalPosition(Vector2<int>(parent->GetSize().x / 2 - size.x / 2,
                                 parent->GetSize().y / 2 - size.y / 2));
}

void UIObject::SetScale(const float scale) { this->scale = scale; }


void UIObject::SetEnable(const bool value)
{
    if (!childs.empty())
    {
        for (std::vector<int>::size_type i = 0; i != childs.size(); i++)
        {
            reinterpret_cast<UIObject *>(childs[i])->SetEnable(value);
        }
    }

    if (enable == value) return;
    this->enable = value;
    if (value)
        OnEnable();
    else
        OnDisable();
}

void UIObject::SetMouseEvent(const bool value) { this->mouseEvents = value; }

float UIObject::GetScale() const { return this->scale; }

bool UIObject::IsEnable() const
{
    if (this->IsParent())
    {
        UIObject *par = reinterpret_cast<UIObject *>(parent);
        return par->IsEnable() && this->enable;
    }
    return this->enable;
}

bool UIObject::IsMouseEvents() const
{
    return mouseEvents;
}

bool UIObject::IsRenderable()
{
    if (IsParent())
    {
        UIObject *p = reinterpret_cast<UIObject *>(parent);
        if (p->IsScrollable())
        {
            if ((GetLocalPosition().y + GetSize().y <= p->GetSize().y) &&
                GetLocalPosition().y >= 0)
            {
                return true;
            }
            return false;
        }
        return true;
    }
    return true;
}

bool UIObject::IsScrollable() const { return scrollable; }

std::string UIObject::GetObjectTypeString()
{
    std::string str;
    switch (this->objType)
    {
        case UIObjectType::UIOBJECT:
            str = "UIObject";
            break;
        case UIObjectType::LABEL:
            str = "Label";
            break;
        case UIObjectType::TEXTBOX:
            str = "TextBox";
            break;
        case UIObjectType::TEXTBUTTON:
            str = "TextButton";
            break;
        case UIObjectType::SPRITEBUTTON:
            str = "SpriteButton";
            break;
        case UIObjectType::PANEL:
            str = "Panel";
            break;
        case UIObjectType::RADIOBUTTON:
            str = "RadioButton";
            break;
        case UIObjectType::LISTITEM:
            str = "ListItem";
            break;
        case UIObjectType::LISTITEMELEMENT:
            str = "ListItemElement";
            break;
        case UIObjectType::ENV_ITEM:
            str = "Env_Item";
            break;
        default:
            str = "Bilinmeyen";
            break;
    }
    return str;
}

void UIObject::SetScrollable(const bool value) { scrollable = value; }
