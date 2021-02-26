#include "TileButton.hpp"

TileButtonWorld::TileButtonWorld()
{
    mDown = std::bind(&TileButtonWorld::onMouseDown, this);
    InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
}

TileButtonWorld::TileButtonWorld(Tile &tile, Vector2<int> &cameraView, float scale) : UIObject(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::TILEBUTTON)
{
    this->tile = tile;
    this->cameraView = &cameraView;

    mDown = std::bind(&TileButtonWorld::onMouseDown, this);
    InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
}

TileButtonWorld::TileButtonWorld(Tile &tile, Vector2<int> &cameraView, Object *par, float scale) : UIObject(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::TILEBUTTON, par)
{
    this->tile = tile;
    this->cameraView = &cameraView;

    mDown = std::bind(&TileButtonWorld::onMouseDown, this);
    InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
}

TileButtonWorld::~TileButtonWorld()
{
    InputManager::removeListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
    RemoveParent();
}

void TileButtonWorld::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    if (IsEnable())
    {
        tile.DrawModel(spriteRenderer);
    }
}

Vector2<int> TileButtonWorld::GetPosition() { return tile.GetPosition(); }

void TileButtonWorld::SetPosition(const Vector2<int> &value)
{
    tile.SetPosition(value);
}

Vector2<int> TileButtonWorld::GetSize() { return tile.GetSize(); }

void TileButtonWorld::SetSize(const Vector2<int> &value)
{
    tile.SetSize(value);
}

Vector2<int> TileButtonWorld::GetLocalPosition() { return tile.GetLocalPosition(); }

void TileButtonWorld::SetLocalPosition(const Vector2<int> &value)
{
    tile.SetLocalPosition(value);
}

Tile &TileButtonWorld::getTile()
{
    return tile;
}

void TileButtonWorld::addListener(std::function<void(TileButtonWorld *)> func)
{
    listenersDown.push_back(std::move(func));
}

bool TileButtonWorld::isMouseHover()
{
    Vector2<int> MouseWorldPos = Utils::ScreenToWorld(*cameraView, InputManager::mousePos);
    if (MouseWorldPos.x >= position.x &&
        MouseWorldPos.x <= position.x + size.x &&
        MouseWorldPos.y >= position.y &&
        MouseWorldPos.y <= position.y + size.y)
    {
        return true;
    }
    return false;
}

void TileButtonWorld::onMouseDown()
{
    if (IsEnable() && isMouseHover())
    {
        for (auto &f : listenersDown)
        {
            f(this);
        }
    }
}

/* ------------------------ */

TileButtonScreen::TileButtonScreen(Tile &tile, float scale) : UIObject(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::TILEBUTTON)
{
    this->tile = tile;

    mDown = std::bind(&TileButtonScreen::onMouseDown, this);
    InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
}

TileButtonScreen::TileButtonScreen(Tile &tile, Object *par, float scale) : UIObject(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::TILEBUTTON, par)
{
    this->tile = tile;

    mDown = std::bind(&TileButtonScreen::onMouseDown, this);
    InputManager::addListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
}

TileButtonScreen::~TileButtonScreen()
{
    InputManager::removeListenerDown(GLFW_MOUSE_BUTTON_LEFT, mDown, id);
    RemoveParent();
}

void TileButtonScreen::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    if (IsEnable())
    {
        tile.DrawModel(spriteRenderer);
    }
}

void TileButtonScreen::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer, float shine, bool selected,
                            float time)
{
    if (IsEnable())
    {
        spriteRenderer.DrawSprite(this->tile.sprite,
                                  this->GetPosition(), this->GetSize(),
                                  0.0F, false, shine, selected, time);
    }
}

Vector2<int> TileButtonScreen::GetPosition() { return tile.GetPosition(); }

void TileButtonScreen::SetPosition(const Vector2<int> &value)
{
    tile.SetPosition(value);
}

Vector2<int> TileButtonScreen::GetSize() { return tile.GetSize(); }

void TileButtonScreen::SetSize(const Vector2<int> &value)
{
    tile.SetSize(value);
}

Vector2<int> TileButtonScreen::GetLocalPosition() { return tile.GetLocalPosition(); }

void TileButtonScreen::SetLocalPosition(const Vector2<int> &value)
{
    tile.SetLocalPosition(value);
}

Tile &TileButtonScreen::getTile()
{
    return tile;
}

void TileButtonScreen::addListener(std::function<void(TileButtonScreen *)> func)
{
    listenersDown.push_back(std::move(func));
}

bool TileButtonScreen::isMouseHover()
{
    if (InputManager::mousePos.x >= position.x &&
        InputManager::mousePos.x <= position.x + size.x &&
        InputManager::mousePos.y >= position.y &&
        InputManager::mousePos.y <= position.y + size.y)
    {
        return true;
    }
    return false;
}

void TileButtonScreen::onMouseDown()
{
    if (IsEnable() && isMouseHover())
    {
        for (auto &f : listenersDown)
        {
            f(this);
        }
    }
}
