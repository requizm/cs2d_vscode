#include "TileButton.hpp"

#include "../Scene/Editor/Editor.hpp"


TileButtonWorld::TileButtonWorld() : UIObject(UIObjectType::TILEBUTTON)
{
    this->SetSize(Vector2<int>(GameParameters::SIZE_TILE));
}

TileButtonWorld::TileButtonWorld(Tile &tile, float scale) : UIObject(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::TILEBUTTON)
{
    this->tile = tile;
}

TileButtonWorld::TileButtonWorld(Tile &tile, Object *par, float scale) : UIObject(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::TILEBUTTON, par)
{
    this->tile = tile;
}

TileButtonWorld::~TileButtonWorld()
{
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

bool TileButtonWorld::IsMouseDown()
{
    if (IsEnable() && mouseEvents)
    {
        if (InputManager::isButtonDown(MouseKeys::MOUSE_BUTTON_LEFT) && IsMouseHover())
        {
            return true;
        }
    }
    return false;
}

bool TileButtonWorld::IsMousePress()
{
    if (IsEnable() && mouseEvents)
    {
        if (InputManager::isButton(MouseKeys::MOUSE_BUTTON_LEFT))
        {
            if (IsMouseHover())
                return true;
        }
    }
    return false;
}

bool TileButtonWorld::IsMouseHover()
{
    Vector2<int> MouseWorldPos = Utils::ScreenToWorld(Editor::instance().camera->view, InputManager::mousePos);
    if (MouseWorldPos.x >= GetPosition().x &&
        MouseWorldPos.x <= GetPosition().x + GetSize().x &&
        MouseWorldPos.y >= GetPosition().y &&
        MouseWorldPos.y <= GetPosition().y + GetSize().y)
    {
        return true;
    }
    return false;
}

/* ------------------------ */

TileButtonScreen::TileButtonScreen(Tile &tile, float scale) : UIObject(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::TILEBUTTON)
{
    this->tile = tile;
}

TileButtonScreen::TileButtonScreen(Tile &tile, Object *par, float scale) : UIObject(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::TILEBUTTON, par)
{
    this->tile = tile;
}

TileButtonScreen::~TileButtonScreen()
{
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

bool TileButtonScreen::IsMouseDown()
{
    if (IsEnable() && mouseEvents)
    {
        if (InputManager::isButtonDown(MouseKeys::MOUSE_BUTTON_LEFT) && IsMouseHover())
        {
            return true;
        }
    }
    return false;
}

bool TileButtonScreen::IsMouseHover()
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

bool TileButtonScreen::IsMousePress()
{
    if (IsEnable() && mouseEvents)
    {
        if (InputManager::isButton(MouseKeys::MOUSE_BUTTON_LEFT) && IsMouseHover())
        {
            return true;
        }
    }
    return false;
}
