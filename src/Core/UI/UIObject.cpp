#include "UIObject.hpp"

UIObject::UIObject()
    : enable(false),
      visible(false),
      mouseEvents(false),
      scrollable(false),
      dependParent(false) {
    this->objType = UIObjectType::UIOBJECT;

    this->position = Vector2<int>(0);
    this->scale = 1.0F;
    this->size = Vector2<int>(0);
    this->rend = nullptr;
}

UIObject::UIObject(Vector2<int> position, Vector2<int> size, float scale,
                   TextRenderer &renderer)
    : enable(true),
      visible(true),
      mouseEvents(true),
      scrollable(false),
      dependParent(false) {
    this->objType = UIObjectType::UIOBJECT;
    this->position = position;
    this->scale = scale;
    this->size = size;
    this->rend = &renderer;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::UIObject(Vector2<int> position, Vector2<int> size, float scale,
                   TextRenderer &renderer, UIObjectType type)
    : enable(true),
      visible(true),
      mouseEvents(true),
      scrollable(false),
      dependParent(false) {
    this->objType = type;
    this->position = position;
    this->scale = scale;
    this->size = size;
    this->rend = &renderer;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::UIObject(Vector2<int> position, Vector2<int> size, float scale)
    : enable(true),
      visible(true),
      mouseEvents(true),
      scrollable(false),
      dependParent(false) {
    this->objType = UIObjectType::UIOBJECT;
    this->position = position;
    this->scale = scale;
    this->size = size;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::UIObject(Vector2<int> position, Vector2<int> size, float scale,
                   UIObjectType type)
    : enable(true),
      visible(true),
      mouseEvents(true),
      scrollable(false),
      dependParent(false) {
    this->objType = type;
    this->position = position;
    this->scale = scale;
    this->size = size;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::UIObject(Vector2<int> position, float scale, TextRenderer &renderer)
    : enable(true),
      visible(true),
      mouseEvents(true),
      scrollable(false),
      dependParent(false) {
    this->objType = UIObjectType::UIOBJECT;
    this->position = position;
    this->scale = scale;
    this->rend = &renderer;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::UIObject(Vector2<int> position, float scale, TextRenderer &renderer,
                   UIObjectType type)
    : enable(true),
      visible(true),
      mouseEvents(true),
      scrollable(false),
      dependParent(false) {
    this->objType = type;
    this->position = position;
    this->scale = scale;
    this->rend = &renderer;

    this->setID(Utils::GenerateID());
    this->childs.clear();
}

UIObject::UIObject(Vector2<int> position, float scale, UIObjectType type)
    : enable(true),
      visible(true),
      mouseEvents(true),
      scrollable(false),
      dependParent(false) {
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

void UIObject::OnDisable() {
    this->isPressed = false;
    this->isUp = false;
    this->isDown = false;
}

void UIObject::ProcessInput() {}

void UIObject::Draw() {}

void UIObject::Draw(SpriteRenderer &spriteRenderer,
                    SquareRenderer &squareRenderer) {}

void UIObject::setPosition(const Vector2<int> position) {
    this->position = position;
}

void UIObject::setPosition(const int x, const int y) {
    this->position.x = x;
    this->position.y = y;
}

void UIObject::setParentCenterPos() {
    if (isParent())
        setPosition(parent->getSize().x / 2 - this->getSize().x / 2,
                    parent->getSize().y / 2 - this->getSize().y / 2);
}

void UIObject::setSize(const Vector2<int> size) { this->size = size; }

void UIObject::setSize(const int x, const int y) {
    this->size = Vector2<int>(x, y);
}

Vector2<int> UIObject::getPosition() {
    if (isParent()) {
        return parent->getPosition() + this->position;
    }
    return this->position;
}

Vector2<int> UIObject::getLocalPosition() {
    if (isParent()) {
        return this->getPosition() - parent->getPosition();
    }
    return this->position;
}

Vector2<int> UIObject::getSize() { return this->size; }

Vector2<int> UIObject::getCenterPosition() const {
    return Vector2<int>(this->position.x + this->size.x / 2,
                        this->position.y + this->size.y / 2);
}

UIObject *UIObject::getParent() const {
    if (isParent()) return parent;
    return nullptr;
}

void UIObject::setScale(const float scale) { this->scale = scale; }

void UIObject::setParent(UIObject *uiobject, bool dependParent) {
    if (isParent()) {
        for (std::vector<int>::size_type i = 0; i != parent->childs.size();
             i++) {
            if (parent->childs[i]->getID() == this->getID()) {
                parent->childs.erase(parent->childs.begin() + i);
                break;
            }
        }
    } else {
        uiobject->childs.push_back(this);
        this->parent = uiobject;
    }
    this->dependParent = dependParent;
}

void UIObject::removeParent() {
    if (isParent()) {
        for (std::vector<int>::size_type i = 0; i != parent->childs.size();
             i++) {
            if (parent->childs[i]->getID() == this->getID()) {
                parent->childs.erase(parent->childs.begin() + i);
                break;
            }
        }
        this->parent = nullptr;
    }
}

void UIObject::setVisible(const bool value) { this->visible = value; }

void UIObject::setEnable(const bool value) {
    if (!childs.empty()) {
        for (std::vector<int>::size_type i = 0; i != childs.size(); i++) {
            childs[i]->setEnable(value);
        }
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

bool UIObject::isVisible() const {
    if (this->isParent() && dependParent) {
        return parent->isVisible() && this->visible;
    }
    return this->visible;
}

bool UIObject::isEnable() const {
    if (this->isParent() && dependParent) {
        return parent->isEnable() && this->enable;
    }
    return this->enable;
}

bool UIObject::isMouseEvents() const {
    if (this->isParent() && dependParent) {
        return parent->isMouseEvents() && this->mouseEvents;
    }
    return this->mouseEvents;
}

bool UIObject::isDependParent() const { return this->dependParent; }

int UIObject::getID() const { return this->id; }

bool UIObject::isRenderable() {
    if (this->isParent()) {
        UIObject *p = this->getParent();
        if (p->isScrollable()) {
            if ((getLocalPosition().y + getSize().y <= p->getSize().y) &&
                getLocalPosition().y >= 0) {
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

std::string UIObject::GetObjectTypeString() {
    std::string str;
    switch ((int)this->objType) {
        case 0:
            str = "UIObject";
            break;
        case 1:
            str = "Label";
            break;
        case 2:
            str = "TextBox";
            break;
        case 3:
            str = "Button";
            break;
        case 4:
            str = "Panel";
            break;
        case 5:
            str = "RadioButton";
            break;
        default:
            str = "Bilinmeyen";
            break;
    }
    return str;
}

void UIObject::setScrollable(const bool value) { this->scrollable = value; }