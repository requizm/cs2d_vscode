#include "Panel.hpp"

Panel::Panel(Vector2<int> position, const std::string &title, Vector2<int> size,
             TextRenderer &renderer, bool isBackGround, bool opttitles,
             float scale, const Vector3<float> &color, float transp)
    : UIObject(position, size, scale, renderer, UIObjectType::PANEL)
{
    this->panelColor = color;
    this->backGround = isBackGround;
    this->dragSize = Vector2<int>(size.x, 23.0F);
    this->opttitles = opttitles;
    this->trans = transp;
    this->enable = false;
    this->movable = false;
    this->scrollable = false;
    this->outline = false;
    escapeButton = new SpriteButton(
        Sprite(ResourceManager::GetTexture("gui_icons"), 0, 0, 16, 16),
        position, Vector2<int>(20, 20), this, true, 1.0F, UIObjectType::PANEL);
    escapeButton->independent = true;
    escapeButton->SetLocalPosition(Vector2<int>(size.x - 20, 3));
    escapeButton->setButtonColor(color);
    escapeButton->setButtonHoverColor(Vector3<float>(0.64F));
    escapeButton->setButtonClickColor(Vector3<float>(1.0F));
    escapeButton->setHaveOutline(false);
    escapeButton->addListenerUp(std::bind(&Panel::escapeButtonClicked, this));
    this->title = new Label(title, position, renderer, this, scale, Vector3<float>(1.0F),
                            UIObjectType::PANEL, LabelType::NOT_CLICKABLE);
    this->title->SetMouseEvent(false);
    this->title->SetLocalPosition(Vector2<int>(lineOffset, 4));
    this->title->independent = true;
}

Panel::Panel(Vector2<int> position, const std::string &title, Vector2<int> size,
             TextRenderer &renderer, Object *par, bool isBackGround, bool opttitles,
             float scale, const Vector3<float> &color, float transp)
    : UIObject(position, size, scale, renderer, UIObjectType::PANEL, par)
{
    this->panelColor = color;
    this->backGround = isBackGround;
    this->dragSize = Vector2<int>(size.x, 23.0F);
    this->opttitles = opttitles;
    this->trans = transp;
    this->enable = false;
    this->movable = false;
    this->scrollable = false;
    this->outline = false;
    escapeButton = new SpriteButton(
        Sprite(ResourceManager::GetTexture("gui_icons"), 0, 0, 16, 16),
        position, Vector2<int>(20, 20), this, true, 1.0F, UIObjectType::PANEL);
    escapeButton->independent = true;
    escapeButton->SetLocalPosition(Vector2<int>(size.x - 20, 3));
    escapeButton->setButtonColor(color);
    escapeButton->setButtonHoverColor(Vector3<float>(0.64F));
    escapeButton->setButtonClickColor(Vector3<float>(1.0F));
    escapeButton->setHaveOutline(false);
    escapeButton->addListenerUp(std::bind(&Panel::escapeButtonClicked, this));
    this->title = new Label(title, position, renderer, this, scale, Vector3<float>(1.0F),
                            UIObjectType::PANEL, LabelType::NOT_CLICKABLE);
    this->title->SetMouseEvent(false);
    this->title->SetLocalPosition(Vector2<int>(lineOffset, 4));
    this->title->independent = true;
}

Panel::Panel() : UIObject() {}

Panel::~Panel()
{
    InputManager::removeListenerUp(GLFW_MOUSE_BUTTON_LEFT, escapeDown, id);
    delete escapeButton;
    delete title;
    RemoveParent();
}

void Panel::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    if (IsEnable())
    {
        if (this->backGround)
        {
            if (!isOutline())
            {
                squareRenderer.ui_RenderFilledSquare(
                    this->GetPosition(), this->GetSize(), this->getPanelColor(),
                    this->trans);
            }
            else
            {
                squareRenderer.ui_RenderFilledSquare(
                    this->GetPosition(), this->GetSize(), getPanelColor(), true,
                    getOutlineColor(), 2.0F, this->trans, 0.0F);
            }
        }
        if (opttitles)
        {
            squareRenderer.ui_RenderLine(
                Vector2<int>(GetPosition().x + lineOffset,
                             GetPosition().y + 23.0F),
                Vector2<int>(GetPosition().x + size.x - lineOffset,
                             GetPosition().y + 23.0F),
                Vector3<float>(0.39F), 1.0F, this->trans);
            escapeButton->Draw(spriteRenderer, squareRenderer);
            title->Draw();
        }
    }
    for (std::vector<int>::size_type i = 0; i != childs.size(); i++)
    {
        UIObject *ch = reinterpret_cast<UIObject *>(childs[i]);
        if (!ch->independent)
        {
            std::string type_str = ch->GetObjectTypeString();
            if (type_str == "Label")
                ch->Draw();
            else if (type_str == "TextButton")
                ch->Draw(squareRenderer);
            else
                ch->Draw(spriteRenderer, squareRenderer);
        }
    }
}

int deltaX;
int deltaY;
bool click = false;
void Panel::Update()
{
    if (IsEnable())
    {
        if (mouseEvents && isMovable())
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
                this->SetPosition(
                    Vector2<int>(mousePos.x - deltaX, mousePos.y - deltaY));
            }
            if (!isPressed) click = false;
        }
        if (opttitles)
        {
            escapeButton->Update();
        }
    }
    for (std::vector<int>::size_type i = 0; i != childs.size(); i++)
    {
        UIObject *ch = reinterpret_cast<UIObject *>(childs[i]);
        if (!(ch->independent))
        {
            ch->Update();
        }
    }
}

void Panel::ProcessInput()
{
    if (IsEnable())
    {
        escapeButton->ProcessInput();
        if (mouseEvents)
        {
            isMouseUpM(MOUSE_BUTTON_LEFT);
            if (isMovable())
            {
                isMouseDownForDrag(MOUSE_BUTTON_LEFT);
            }
            else
            {
                isMouseDownForMouse(MOUSE_BUTTON_LEFT);
            }
        }
        for (std::vector<int>::size_type i = 0; i != childs.size(); i++)
        {
            UIObject *ch = reinterpret_cast<UIObject *>(childs[i]);
            if (!ch->independent) ch->ProcessInput();
        }
    }
}

void Panel::OnEnable()
{
    if (opttitles)
    {
        escapeButton->SetEnable(true);
        title->SetEnable(true);
    }
}

void Panel::OnDisable()
{
    if (opttitles)
    {
        escapeButton->SetEnable(false);
        title->SetEnable(false);
        this->isPressed = false;
        this->isDown = false;
        this->isUp = false;
    }
}

bool Panel::isMouseHover(bool drag)
{
    if (!this->IsEnable())
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
    if (!this->IsEnable())
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
    if (!this->IsEnable())
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
    const int posX = static_cast<int>(this->GetPosition().x);
    const int posY = static_cast<int>(this->GetPosition().y);

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
    const int posX = static_cast<int>(this->GetPosition().x);
    const int posY = static_cast<int>(this->GetPosition().y);

    const int sizeX = static_cast<int>(this->GetSize().x);
    const int sizeY = static_cast<int>(this->GetSize().y);

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

void Panel::escapeButtonClicked()
{
    if (opttitles && IsEnable() && mouseEvents)
    {
        SetEnable(false);
    }
}
