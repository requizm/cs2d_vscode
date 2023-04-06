#include "UIObject.hpp"

#include "../Manager/Logger.hpp"
#include "../Manager/Utils.hpp"

UIObject::UIObject(UIObjectType type)
{
    this->objType = type;
}

UIObject::UIObject(const Vector2<int> &position, const Vector2<int> &size, float scale,
                   TextRenderer &renderer) : std::enable_shared_from_this<UIObject>()
{
    this->objType = UIObjectType::UIOBJECT;
    this->position = position;
    this->scale = scale;
    this->size = size;
    this->rend = &renderer;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::UIObject(const Vector2<int> &position, const Vector2<int> &size, float scale,
                   TextRenderer &renderer, UIObjectType type) : std::enable_shared_from_this<UIObject>()
{
    this->objType = type;
    this->position = position;
    this->scale = scale;
    this->size = size;
    this->rend = &renderer;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::UIObject(const Vector2<int> &position, const Vector2<int> &size, float scale) : std::enable_shared_from_this<UIObject>()
{
    this->objType = UIObjectType::UIOBJECT;
    this->position = position;
    this->scale = scale;
    this->size = size;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::UIObject(const Vector2<int> &position, const Vector2<int> &size, float scale,
                   UIObjectType type) : std::enable_shared_from_this<UIObject>()
{
    this->objType = type;
    this->position = position;
    this->scale = scale;
    this->size = size;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::UIObject(const Vector2<int> &position, float scale, TextRenderer &renderer) : std::enable_shared_from_this<UIObject>()
{
    this->objType = UIObjectType::UIOBJECT;
    this->position = position;
    this->scale = scale;
    this->rend = &renderer;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::UIObject(const Vector2<int> &position, float scale, TextRenderer &renderer,
                   UIObjectType type) : std::enable_shared_from_this<UIObject>()
{
    this->objType = type;
    this->position = position;
    this->scale = scale;
    this->rend = &renderer;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::UIObject(const Vector2<int> &position, float scale, UIObjectType type) : std::enable_shared_from_this<UIObject>()
{
    this->objType = type;
    this->position = position;
    this->scale = scale;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::~UIObject() = default;

bool onenabletrigger = false;
void UIObject::Update() {}

void UIObject::OnEnable() {}

void UIObject::OnDisable()
{
    this->isPressed = false;
    this->isUp = false;
    this->isDown = false;
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

void UIObject::setPosition(const Vector2<int> &position)
{
    Vector2<int> newPos = position;
    if (objType == UIObjectType::PANEL)
    {
        Vector2<int> oldPos = this->position;

        auto children = GetChildren();
        for (std::vector<int>::size_type i = 0; i != children.size(); i++)
        {
            Vector2<int> delta = newPos - oldPos;
            children[i]->setLocalPosition(children[i]->getLocalPosition() + delta);
        }
    }

    this->position = newPos;
}

void UIObject::setParentCenterPos()
{
    if (isParent())
        setLocalPosition(Vector2<int>(parent->getSize().x / 2 - this->getSize().x / 2,
                                      parent->getSize().y / 2 - this->getSize().y / 2));
}

void UIObject::setLocalPosition(const Vector2<int> &value)
{
    if (isParent())
    {
        Vector2<int> newLocalPos = value;
        Vector2<int> newPos = newLocalPos + getParent()->getPosition();
        if (objType == UIObjectType::PANEL)
        {
            Vector2<int> oldPos = this->position;

            auto children = GetChildren();
            for (std::vector<int>::size_type i = 0; i != children.size(); i++)
            {
                Vector2<int> delta = newPos - oldPos;
                children[i]->setLocalPosition(children[i]->getLocalPosition() + delta);
            }
        }

        position = newPos;
    }
}

void UIObject::setSize(const Vector2<int> &size) { this->size = size; }

void UIObject::setSize(const int x, const int y)
{
    this->size = Vector2<int>(x, y);
}

Vector2<int> UIObject::getPosition()
{
    return this->position;
}

Vector2<int> UIObject::getLocalPosition()
{
    if (isParent())
    {
        return this->position - parent->getPosition();
    }
}

Vector2<int> UIObject::getSize() { return this->size; }

Vector2<int> UIObject::getCenterPosition() const
{
    return Vector2<int>(this->position.x + this->size.x / 2,
                        this->position.y + this->size.y / 2);
}

UIObject *UIObject::getParent() const
{
    return isParent() ? parent.get() : nullptr;
}

std::vector<std::shared_ptr<UIObject>> UIObject::GetChildren() const
{
    std::vector<std::shared_ptr<UIObject>> children = std::vector<std::shared_ptr<UIObject>>();
    for (const auto &child : childs)
    {
        if (auto sp = child.lock())
        {
            children.push_back(sp);
        }
    }
    return children;
}

void UIObject::setScale(const float scale) { this->scale = scale; }

void UIObject::setParent(std::shared_ptr<UIObject> uiobject, bool dependParent)
{
    if (isParent())
    {
        if (uiobject->getID() != getParent()->getID())
        {
            auto children = parent->GetChildren();
            for (std::vector<int>::size_type i = 0; i != children.size(); i++)
            {
                if (children[i]->getID() == this->getID())
                {
                    parent->RemoveChild(children[i]);
                    break;
                }
            }
        }
    }

    this->parent = uiobject;
    uiobject->AddChild(shared_from_this());
    this->setLocalPosition(getPosition());
    this->dependParent = dependParent;
}

void UIObject::removeParent()
{
    /*if (isParent())
    {
        auto children = parent->GetChildren();
        for (std::vector<int>::size_type i = 0; i != children.size(); i++)
        {
            if (children[i]->getID() == this->getID())
            {
                children.erase(children.begin() + i);
                i--;
            }
        }
        // this->parent = nullptr;
    }

    if (!childs.empty())
    {
        auto children = GetChildren();
        for (std::vector<int>::size_type i = 0; i != children.size(); i++)
        {
            children[i]->removeParent();
        }
    }*/
}

void UIObject::setVisible(const bool value) { this->visible = value; }

void UIObject::setEnable(const bool value)
{
    auto children = GetChildren();
    for (std::vector<int>::size_type i = 0; i != children.size(); i++)
    {
        children[i]->setEnable(value);
    }

    if (enable == value) return;
    this->enable = value;
    if (value)
        OnEnable();
    else
        OnDisable();
}

void UIObject::setMouseEvent(const bool value) { this->mouseEvents = value; }

void UIObject::setDependParent(const bool value) { this->dependParent = value; }

float UIObject::getScale() const { return this->scale; }

bool UIObject::isParent() const { return this->parent != nullptr; }

bool UIObject::isVisible() const
{
    if (this->isParent() && dependParent)
    {
        return parent->isVisible() && this->visible;
    }
    return this->visible;
}

bool UIObject::isEnable() const
{
    if (this->isParent() && dependParent)
    {
        return parent->isEnable() && this->enable;
    }
    return this->enable;
}

bool UIObject::isMouseEvents() const
{
    if (this->isParent() && dependParent)
    {
        return parent->isMouseEvents() && this->mouseEvents;
    }
    return this->mouseEvents;
}

bool UIObject::isDependParent() const { return this->dependParent; }

int UIObject::getID() const { return this->id; }

bool UIObject::isRenderable()
{
    if (this->isParent())
    {
        UIObject *p = this->getParent();
        if (p->isScrollable())
        {
            if ((getLocalPosition().y + getSize().y <= p->getSize().y) &&
                getLocalPosition().y >= 0)
            {
                p = nullptr;
                return true;
            }
            p = nullptr;
            return false;
        }
        p = nullptr;
        return true;
    }
    return true;
}

bool UIObject::isScrollable() const { return this->scrollable; }

void UIObject::setID(const int value) { this->id = value; }

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

void UIObject::RemoveChild(std::shared_ptr<UIObject> child)
{
    childs.erase(
        std::remove_if(
            childs.begin(),
            childs.end(),
            [child](const std::weak_ptr<UIObject> &wp)
            {
                return wp.expired() || wp.lock() == child;
            }),
        childs.end());
}

void UIObject::AddChild(std::shared_ptr<UIObject> child)
{
    childs.push_back(std::weak_ptr<UIObject>(child));
}

void UIObject::setScrollable(const bool value) { this->scrollable = value; }