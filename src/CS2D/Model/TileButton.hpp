#ifndef TILEBUTTON_H
#define TILEBUTTON_H

#include "../../Core/UI/UIObject.hpp"
#include "Tile.hpp"


class TileButtonWorld : public UIObject
{
   public:
    TileButtonWorld();
    explicit TileButtonWorld(Tile &tile, float scale = 1.0F);
    ~TileButtonWorld() final;

    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) final;

    Vector2<int> getPosition() final;
    void setPosition(const Vector2<int> &value) final;

    Vector2<int> getSize() final;
    void setSize(const Vector2<int> value) final;

    void setLocalPosition(const Vector2<int> value) final;

    bool isRenderable() final;

    Tile &getTile();

    bool IsMouseDown();
    bool IsMousePress();
    bool IsMouseHover();

   private:
    Tile tile;
};

class TileButtonScreen : public UIObject
{
   public:
   TileButtonScreen() = default;
    explicit TileButtonScreen(Tile &tile, float scale = 1.0F);
    ~TileButtonScreen() final;

    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) final;
    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer, float shine, bool selected,
              float time);

    Vector2<int> getPosition() final;
    void setPosition(const Vector2<int> &value) final;

    Vector2<int> getSize() final;
    void setSize(const Vector2<int> value) final;

    Vector2<int> getLocalPosition() final;
    void setLocalPosition(const Vector2<int> value) final;

    void setParent(UIObject *uiobject, bool dependParent = true) final;

    bool isRenderable() final;

    Tile &getTile();

    bool IsMouseDown();
    bool IsMousePress();
    bool IsMouseHover();

   private:
    Tile tile;
};


#endif  // TILEBUTTON_H