#include "Panel.hpp"

#include "../Manager/InputManager.hpp"
#include "../Manager/MemoryOverride/MemoryOverride.hpp"
#include "../Manager/ResourceManager.hpp"


Panel::Panel(const Vector2<int> &position, const std::string &title, const Vector2<int> &size,
             TextRenderer &renderer, bool isBackGround, bool opttitles,
             float scale, const Vector3<float> &color, float transp)
    : UIObject(position, size, scale, renderer, UIObjectType::PANEL)
{
    this->panelColor = color;
    this->backGround = isBackGround;
    this->dragSize = Vector2<int>(size.x, 23);
    this->opttitles = opttitles;
    this->trans = transp;
    this->enable = false;
    this->movable = false;
    this->scrollable = false;
    this->outline = false;
}

Panel::Panel() : UIObject() {}

Panel::~Panel()
{
    InputManager::removeListenerUp(GLFW_MOUSE_BUTTON_LEFT, escapeDown, id);
    UIObject::removeParent();
}

void Panel::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    if (isEnable() && isVisible())
    {
        if (this->backGround)
        {
            if (!isOutline())
            {
                squareRenderer.ui_RenderFilledSquare(
                    this->getPosition(), this->getSize(), this->getPanelColor(),
                    this->trans);
            }
            else
            {
                squareRenderer.ui_RenderFilledSquare(
                    this->getPosition(), this->getSize(), getPanelColor(), true,
                    getOutlineColor(), 2.0F, this->trans, 0);
            }
        }
        if (opttitles)
        {
            squareRenderer.ui_RenderLine(
                Vector2<int>(getPosition().x + lineOffset,
                             getPosition().y + 23),
                Vector2<int>(getPosition().x + size.x - lineOffset,
                             getPosition().y + 23),
                Vector3<float>(0.39F), 1.0F, this->trans);
            escapeButton->Draw(spriteRenderer, squareRenderer);
            title->Draw();
        }
    }
    auto children = GetChildren();
    for (std::vector<int>::size_type i = 0; i != children.size(); i++)
    {
        if (!children[i]->independent)
        {
            if (children[i]->GetObjectTypeString() == "Label")
                children[i]->Draw();
            else if (children[i]->GetObjectTypeString() == "TextButton")
                children[i]->Draw(squareRenderer);
            else
                children[i]->Draw(spriteRenderer, squareRenderer);
        }
    }
}

int deltaX;
int deltaY;
bool click = false;
void Panel::Update()
{
    if (isEnable())
    {
        if (isMouseEvents() && isMovable())
        {
            if (!click && (opttitles && !escapeButton->isPressed) ||
                (!opttitles && !click))
            {
                if (isMouseDown(true))
                {
                    deltaX =
                        InputManager::mousePos.x - static_cast<int>(position.x);
                    deltaY =
                        InputManager::mousePos.y - static_cast<int>(position.y);
                    click = true;
                }
            }
            if (isPressed && click)
            {
                Vector2<int> mousePos = InputManager::mousePos;
                this->setPosition(
                    Vector2<int>(mousePos.x - deltaX, mousePos.y - deltaY));
            }
            if (!isPressed) click = false;
        }
        if (opttitles)
        {
            escapeButton->Update();
        }
    }
    auto children = GetChildren();
    for (std::vector<int>::size_type i = 0; i != children.size(); i++)
    {
        if (!(children[i]->independent))
        {
            children[i]->Update();
        }
    }
}

void Panel::ProcessInput()
{
    if (isEnable())
    {
        escapeButton->ProcessInput();
        if (isMouseEvents())
        {
            isMouseUpM(MOUSE_BUTTON_LEFT);
            /*if (escapeButton->isMouseUp() && opttitles)
            {
                this->setEnable(false);
            }*/
            if (isMovable())
            {
                isMouseDownForDrag(MOUSE_BUTTON_LEFT);
            }
            else
            {
                isMouseDownForMouse(MOUSE_BUTTON_LEFT);
            }
        }
        auto children = GetChildren();
        for (std::vector<int>::size_type i = 0; i != children.size(); i++)
        {
            if (!children[i]->independent) children[i]->ProcessInput();
        }
    }
}

void Panel::OnEnable()
{
    if (opttitles)
    {
        escapeButton->setEnable(true);
        title->setEnable(true);
        escapeButton->setVisible(true);
        title->setVisible(true);
    }
}

void Panel::OnDisable()
{
    if (opttitles)
    {
        escapeButton->setEnable(false);
        title->setEnable(false);
        escapeButton->setVisible(false);
        title->setVisible(false);
        this->isPressed = false;
        this->isDown = false;
        this->isUp = false;
    }
}

bool Panel::isMouseHover(bool drag)
{
    if (!this->isEnable())
    {
        return false;
    }
    if (drag)
        return isMouseHoverForDrag();
    else
        return isMouseHoverForMouse();
}

bool Panel::isMouseDown(bool drag)
{
    if (!this->isEnable())
    {
        return false;
    }
    if (drag)
        return isDownForDrag;
    else
        return isDown;
}

bool Panel::isMouseUp() { return isUp; }

bool Panel::isMousePress(bool drag)
{
    if (!this->isEnable())
    {
        return false;
    }
    if (drag)
        return isMousePressForDrag(MOUSE_BUTTON_LEFT);
    else
        return isMousePressForMouse(MOUSE_BUTTON_LEFT);
}

bool Panel::isMouseHoverForDrag()
{
    const int posX = static_cast<int>(this->getPosition().x);
    const int posY = static_cast<int>(this->getPosition().y);

    const int sizeX = static_cast<int>(this->dragSize.x);
    const int sizeY = static_cast<int>(this->dragSize.y);

    if (InputManager::mousePos.x >= posX &&
        InputManager::mousePos.x <= posX + sizeX &&
        InputManager::mousePos.y >= posY &&
        InputManager::mousePos.y <= posY + sizeY)
    {
        return true;
    }
    return false;
}

bool Panel::isMouseHoverForMouse()
{
    const int posX = static_cast<int>(this->getPosition().x);
    const int posY = static_cast<int>(this->getPosition().y);

    const int sizeX = static_cast<int>(this->getSize().x);
    const int sizeY = static_cast<int>(this->getSize().y);

    if (InputManager::mousePos.x >= posX &&
        InputManager::mousePos.x <= posX + sizeX &&
        InputManager::mousePos.y >= posY &&
        InputManager::mousePos.y <= posY + sizeY)
    {
        return true;
    }
    return false;
}

bool Panel::isMouseDownForDrag(MouseKeys key)
{
    if (isPressed && isDownForDrag)
    {
        isDownForDrag = false;
        return false;
    }
    if (InputManager::isButtonDown(key) && isMouseHover(true))
    {
        isPressed = true;
        isDownForDrag = true;
        return true;
    }
    return false;
}

bool Panel::isMouseDownForMouse(MouseKeys key)
{
    if (isPressed && isDown)
    {
        isDown = false;
        return false;
    }
    if (InputManager::isButtonDown(key) && isMouseHover(false))
    {
        isPressed = true;
        isDown = true;
        return true;
    }
    return false;
}

bool Panel::isMouseUpM(MouseKeys key)
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

bool Panel::isMousePressForDrag(MouseKeys key)
{
    if (isMouseHover(true) && InputManager::isButton(key))
    {
        return true;
    }
    return false;
}

bool Panel::isMousePressForMouse(MouseKeys key)
{
    if (isMouseHover(false) && InputManager::isButton(key))
    {
        return true;
    }
    return false;
}

Vector3<float> Panel::getPanelColor() const { return this->panelColor; }

Vector3<float> Panel::getOutlineColor() const { return this->outlineColor; }

bool Panel::isBackGround() const { return this->backGround; }

bool Panel::isMovable() const { return this->movable; }

bool Panel::isOutline() const { return this->outline; }

std::string Panel::getTitle() const { return title->getText(); }

void Panel::setPanelColor(const Vector3<float> &color)
{
    this->panelColor = color;
}

void Panel::setBackGround(const bool value) { this->backGround = value; }

void Panel::setMovable(const bool value) { this->movable = value; }

void Panel::setTitle(const std::string &text) { this->title->setText(text); }

void Panel::setOutlineColor(const Vector3<float> &color)
{
    this->outlineColor = color;
}

void Panel::setOutline(const bool value) { this->outline = value; }

void Panel::InitTitleAndEscapeButton(TextRenderer &renderer, const std::string &title)
{
    escapeButton = std::make_shared<SpriteButton>(
        Sprite(ResourceManager::GetTexture("gui_icons"), 0, 0, 16, 16),
        Vector2<int>(this->size.x - 20, 3), Vector2<int>(20, 20), true);
    escapeButton->setParent(std::move(shared_from_this()));
    escapeButton->independent = true;
    escapeButton->setButtonColor(this->panelColor);
    escapeButton->setButtonHoverColor(Vector3<float>(0.64F));
    escapeButton->setButtonClickColor(Vector3<float>(1.0F));
    escapeButton->setHaveOutline(false);
    escapeButton->addListenerUp(std::bind(&Panel::escapeButtonClicked, this));
    this->title = std::make_shared<Label>(title, Vector2<int>(lineOffset, 4), renderer, scale, Vector3<float>(1.0F),
                                          UIObjectType::PANEL, LabelType::NOT_CLICKABLE);
    this->title->setMouseEvent(false);
    this->title->setParent(std::move(shared_from_this()));
    this->title->independent = true;
}

void Panel::escapeButtonClicked()
{
    if (opttitles && isEnable() && isMouseEvents())
    {
        setEnable(false);
    }
}
