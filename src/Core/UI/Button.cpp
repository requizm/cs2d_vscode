#include "Button.hpp"


Button::Button() : Label() {}

Button::Button(const std::string &text, Vector2<int> position,
               Vector2<int> size, TextRenderer &renderer,
               const Vector3<float> &buttonColor,
               const Vector3<float> &textColor, float scale, UIObjectType type)
    : Label(text, position, renderer, scale, textColor, type),
      difColor(false),
      haveOutline(false)
{
    this->buttonColor = buttonColor;
    Vector2<int> nSize = renderer.CalculateSize(text, 1.0F);
    this->SetSize(
        Vector2<int>(static_cast<int>(static_cast<float>(nSize.x) * 1.5F),
                     static_cast<int>(static_cast<float>(nSize.y) * 1.5F)));
    this->btn_type = ButtonType::DEFAULT;

    if (type == UIObjectType::TEXTBUTTON || type == UIObjectType::RADIOBUTTON)
    {
        mDown = std::bind(&Button::onMouseDown, this);
        InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);

        mUp = std::bind(&Button::onMouseUp, this);
        InputManager::addListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);

        ObjectManager::listenerObjCount++;
    }
}

Button::Button(const Sprite &sprite, Vector2<int> position, Vector2<int> size,
               bool difColor, float scale, UIObjectType type)
    : Label(position, size, scale, type), haveOutline(false)
{
    this->sprite = sprite;
    this->difColor = difColor;
    this->btn_type = ButtonType::SPRITE;

    if (type == UIObjectType::TEXTBUTTON || type == UIObjectType::RADIOBUTTON)
    {
        mDown = std::bind(&Button::onMouseDown, this);
        InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);

        mUp = std::bind(&Button::onMouseUp, this);
        InputManager::addListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
        ObjectManager::listenerObjCount++;
    }
}

Button::Button(Tile &tile, float scale, UIObjectType type)
    : Label(tile.GetPosition(), tile.GetSize(), scale, type,
            LabelType::NOT_CLICKABLE),
      difColor(false),
      haveOutline(false)
{
    this->tile = tile;
    this->btn_type = ButtonType::TILE;

    if (type == UIObjectType::TEXTBUTTON || type == UIObjectType::RADIOBUTTON)
    {
        mDown = std::bind(&Button::onMouseDown, this);
        InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);

        mUp = std::bind(&Button::onMouseUp, this);
        InputManager::addListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
        ObjectManager::listenerObjCount++;
    }
}

Button::~Button()
{
    if (objType == UIObjectType::TEXTBUTTON || objType == UIObjectType::RADIOBUTTON)
    {
        InputManager::removeListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
        InputManager::removeListenerUp(GLFW_MOUSE_BUTTON_LEFT, mUp, id);
        ObjectManager::listenerObjCount--;
    }
    RemoveParent();
}

void Button::Draw(SpriteRenderer &spriteRenderer,
                  SquareRenderer &squareRenderer)
{
    if (IsEnable() && IsRenderable())
    {
        switch (btn_type)
        {
            case ButtonType::DEFAULT:
                squareRenderer.ui_RenderFilledSquare(
                    this->GetPosition(), this->GetSize(), currentColor,
                    haveOutline, outlineColor, 1.0F, 1.0F, 0.0F);
                Label::DrawForButton(center);
                break;
            case ButtonType::SPRITE:
                if (difColor)
                {
                    spriteRenderer.DrawSprite(this->sprite, this->GetPosition(),
                                              this->GetSize(), currentColor);
                }
                else
                {
                    if (haveOutline)
                    {
                        squareRenderer.ui_RenderFilledSquare(
                            this->GetPosition(),
                            Vector2<int>(this->GetSize().x + margin.x,
                                         this->GetSize().y + margin.y),
                            this->currentColor);
                        squareRenderer.ui_RenderEmptySquare(
                            this->GetPosition(),
                            Vector2<int>(this->GetSize().x + margin.x,
                                         this->GetSize().y + margin.y),
                            this->outlineColor);
                        spriteRenderer.DrawSprite(
                            this->sprite,
                            Vector2<int>(this->GetPosition().x + margin.x / 2,
                                         this->GetPosition().y + margin.y / 2),
                            this->GetSize());
                    }
                    else
                    {
                        squareRenderer.ui_RenderFilledSquare(
                            this->GetPosition(),
                            Vector2<int>(this->GetSize().x + margin.x,
                                         this->GetSize().y + margin.y),
                            this->currentColor);
                        spriteRenderer.DrawSprite(
                            this->sprite,
                            Vector2<int>(this->GetPosition().x + margin.x / 2,
                                         this->GetPosition().y + margin.y / 2),
                            this->GetSize());
                    }
                }
                break;
            case ButtonType::TILE:
                spriteRenderer.DrawSprite(this->tile.sprite,
                                          this->GetPosition(), this->GetSize());
                break;
            case ButtonType::ENV_OBJ:
                spriteRenderer.DrawSprite(
                    this->tile.sprite,
                    this->GetPosition() + GameParameters::SIZE_TILE / 4,
                    this->GetSize() / Vector2<int>(2));
                break;
        }
    }
}

void Button::Draw(SpriteRenderer &spriteRenderer,
                  SquareRenderer &squareRenderer, float shine, bool selected,
                  float time)
{
    if (IsEnable() && IsRenderable())
    {
        switch (btn_type)
        {
            case ButtonType::TILE:
                spriteRenderer.DrawSprite(this->tile.sprite,
                                          this->GetPosition(), this->GetSize(),
                                          0.0F, false, shine, selected, time);
        }
    }
}

void Button::Draw()
{
    if (IsEnable())
    {
        Label::Draw();
    }
}

void Button::Update()
{
    if (IsEnable() && mouseEvents)
    {
        if (btn_type == ButtonType::DEFAULT || btn_type == ButtonType::SPRITE ||
            ButtonType::TILE)
        {
            if (!isPressed && isMouseHover())
            {
                currentColor = mouseHoverColor;
                labelCurrentColor = labelMouseHoverColor;
            }
            else if (!isPressed)
            {
                currentColor = buttonColor;
                labelCurrentColor = labelColor;
            }
        }
    }
}

void Button::ProcessInput()
{
    if (mouseEvents)
    {
        // isMouseDownM(GLFW_MOUSE_BUTTON_LEFT);
        // isMouseUpM(GLFW_MOUSE_BUTTON_LEFT);
    }
}

Vector2<int> Button::GetPosition()
{
    if (btn_type == ButtonType::TILE || btn_type == ButtonType::ENV_OBJ)
    {
        if (IsParent())
        {
            return parent->GetPosition() + this->tile.GetPosition();
        }
        return this->tile.GetPosition();
    }
    if (IsParent())
    {
        return parent->GetPosition() + this->position;
    }
    return this->position;
}

Vector2<int> Button::GetLocalPosition()
{
    if (btn_type == ButtonType::TILE)
    {
        if (IsParent())
        {
            return this->GetPosition() - parent->GetPosition();
        }
        return this->tile.GetPosition();
    }
    if (IsParent())
    {
        return this->GetPosition() - parent->GetPosition();
    }
    return this->position;
}

Vector2<int> Button::GetSize()
{
    if (btn_type == ButtonType::TILE || btn_type == ButtonType::ENV_OBJ)
    {
        return tile.GetSize();
    }
    return this->size;
}

bool Button::isMouseHover()
{
    if (IsEnable() && mouseEvents) return isMouseHoverM();
    return false;
}

bool Button::isMouseDown()
{
    // return isDown;
    if (downTrigger && isPressed)
    {
        downTrigger = false;
        return true;
    }
    return false;
}

bool Button::isMouseUp()
{
    if (upTrigger && !isPressed)
    {
        upTrigger = false;
        return true;
    }
    return false;
}

bool Button::isMousePress()
{
    if (IsEnable()) return isMousePressM(MOUSE_BUTTON_LEFT);
    return false;
}

bool Button::isMouseHoverM()
{
    const int posX = static_cast<int>(this->GetPosition().x);
    const int posY = static_cast<int>(this->GetPosition().y);

    int sizeX = static_cast<int>(this->GetSize().x);
    int sizeY = static_cast<int>(this->GetSize().y);

    if (haveOutline)
    {
        sizeX += margin.x;
        sizeY += margin.y;
    }

    if (InputManager::mousePos.x >= posX &&
        InputManager::mousePos.x <= posX + sizeX &&
        InputManager::mousePos.y >= posY &&
        InputManager::mousePos.y <= posY + sizeY)
    {
        return true;
    }
    return false;
}

bool Button::isMouseDownM(MouseKeys key)
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

bool Button::isMouseUpM(MouseKeys key)
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

bool Button::isMousePressM(MouseKeys key)
{
    if (isMouseHover() && InputManager::isButton(key))
    {
        return true;
    }
    return false;
}

void Button::onMouseDown()
{
    if (IsEnable() && isMouseHover())
    {
        if (btn_type == ButtonType::DEFAULT || btn_type == ButtonType::SPRITE ||
            btn_type == ButtonType::TILE)
        {
            labelCurrentColor = labelClickColor;
            currentColor = mouseclickColor;
        }
        upTrigger = false;
        downTrigger = true;
        isPressed = true;
        for (auto &f : listenersDown)
        {
            f();
        }
    }
}

void Button::onMouseUp()
{
    if (isPressed)
    {
        if (IsEnable() && isMouseHover())
        {
            if (btn_type == ButtonType::DEFAULT ||
                btn_type == ButtonType::SPRITE || btn_type == ButtonType::TILE)
            {
                labelCurrentColor = labelColor;
                currentColor = buttonColor;
            }
            for (auto &f : listenersUp)
            {
                f();
            }
        }
        upTrigger = true;
        downTrigger = false;
        isPressed = false;
    }
}

void Button::setType(ButtonType type) { this->btn_type = type; }

void Button::setTile(Tile tile) { this->tile = tile; }

void Button::setMouseHoverColor(const Vector3<float> &color)
{
    this->mouseHoverColor = color;
}

void Button::setButtonColor(const Vector3<float> &color)
{
    this->buttonColor = color;
}

void Button::setMouseClickColor(const Vector3<float> &color)
{
    this->mouseclickColor = color;
}

void Button::setOutlineColor(const Vector3<float> &color)
{
    this->outlineColor = color;
}

void Button::setOutline(const bool value) { this->haveOutline = value; }

void Button::setMargin(const Vector2<int> value)
{
    if (haveOutline) this->margin = value;
}

void Button::SetPosition(const Vector2<int> &position)
{
    if (btn_type == ButtonType::TILE)
    {
        this->tile.SetPosition(position);
    }
    else
        this->position = position;
}

Tile *Button::getTile() { return &this->tile; }