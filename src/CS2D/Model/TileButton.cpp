#include "TileButton.hpp"

#include "../../Core/Manager/InputManager.hpp"
#include "../../Core/Manager/Utils.hpp"
#include "../Other/GameParameters.hpp"
#include "../Other/SceneManager.hpp"
#include "../Scene/Editor/Editor.hpp"


TileButtonWorld::TileButtonWorld() : UIObject(UIObjectType::TILEBUTTON)
{
    this->setSize(Vector2<int>(GameParameters::SIZE_TILE));
}

TileButtonWorld::TileButtonWorld(Tile &tile, float scale) : UIObject(tile.GetPosition(), tile.GetSize(), scale, UIObjectType::TILEBUTTON)
{
    this->tile = tile;
}

TileButtonWorld::~TileButtonWorld()
{
}

void TileButtonWorld::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    if (isEnable())
    {
        tile.DrawModel(spriteRenderer);
    }
}

Vector2<int> TileButtonWorld::getPosition() { return tile.GetPosition(); }

void TileButtonWorld::setPosition(const Vector2<int> &value)
{
    tile.SetPosition(value);
}

Vector2<int> TileButtonWorld::getSize() { return tile.GetSize(); }

void TileButtonWorld::setSize(const Vector2<int> value)
{
    tile.SetSize(value);
}

void TileButtonWorld::setLocalPosition(const Vector2<int> value)
{
    tile.SetLocalPosition(value);
}

bool TileButtonWorld::isRenderable()
{
    Vector2 pos = Utils::WorldToScreen(SceneManager::instance().GetActiveScene<Editor>()->camera->view, tile.GetCellPos() * Vector2<int>(GameParameters::SIZE_TILE));
    if (pos.x <= GameParameters::SCREEN_WIDTH && pos.x >= 0 &&
        pos.y <= GameParameters::SCREEN_HEIGHT && pos.y >= 0)
    {
        return true;
    }
    return false;
}

Tile &TileButtonWorld::getTile()
{
    return tile;
}

bool TileButtonWorld::IsMouseDown()
{
    if (isEnable() && mouseEvents)
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
    if (isEnable() && mouseEvents)
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
    Vector2<int> MouseWorldPos = Utils::ScreenToWorld(SceneManager::instance().GetActiveScene<Editor>()->camera->view, InputManager::mousePos);
    if (MouseWorldPos.x >= getPosition().x &&
        MouseWorldPos.x <= getPosition().x + getSize().x &&
        MouseWorldPos.y >= getPosition().y &&
        MouseWorldPos.y <= getPosition().y + getSize().y)
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

TileButtonScreen::~TileButtonScreen()
{
}

void TileButtonScreen::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer)
{
    if (isEnable() && isRenderable())
    {
        tile.DrawModel(spriteRenderer);
    }
}

void TileButtonScreen::Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer, float shine, bool selected, float time)
{
    if (isEnable() && isRenderable())
    {
        spriteRenderer.DrawSprite(this->tile.sprite,
                                  this->getPosition(), this->getSize(),
                                  0.0F, false, shine, selected, time);
    }
}

Vector2<int> TileButtonScreen::getPosition() { return tile.GetPosition(); }

void TileButtonScreen::setPosition(const Vector2<int> &value)
{
    tile.SetPosition(value);
    tile.SetLocalPosition(getPosition() - parent->getPosition());
}

Vector2<int> TileButtonScreen::getSize() { return tile.GetSize(); }

void TileButtonScreen::setSize(const Vector2<int> value)
{
    tile.SetSize(value);
}

Vector2<int> TileButtonScreen::getLocalPosition() { return tile.GetLocalPosition(); }

void TileButtonScreen::setLocalPosition(const Vector2<int> value)
{
    Vector2<int> newLocalPos = value;
    tile.SetLocalPosition(newLocalPos);
    tile.SetPosition(newLocalPos + parent->getPosition());
}

bool TileButtonScreen::isRenderable()
{
    Vector2<int> pe = getLocalPosition();
    if ((pe.y + getSize().y <= parent->getSize().y) &&
        pe.y >= 0)
    {
        return true;
    }
    return false;
}

Tile &TileButtonScreen::getTile()
{
    return tile;
}

bool TileButtonScreen::IsMouseDown()
{
    if (isEnable() && mouseEvents)
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
    if (InputManager::mousePos.x >= getPosition().x &&
        InputManager::mousePos.x <= getPosition().x + getSize().x &&
        InputManager::mousePos.y >= getPosition().y &&
        InputManager::mousePos.y <= getPosition().y + getSize().y)
    {
        return true;
    }
    return false;
}

bool TileButtonScreen::IsMousePress()
{
    if (isEnable() && mouseEvents)
    {
        if (InputManager::isButton(MouseKeys::MOUSE_BUTTON_LEFT) && IsMouseHover())
        {
            return true;
        }
    }
    return false;
}
