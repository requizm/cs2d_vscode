#ifndef TILEBUTTON_H
#define TILEBUTTON_H

#include "../../Core/UI/UIObject.hpp"
#include "Tile.hpp"


class TileButtonWorld : public UIObject
{
   public:
    TileButtonWorld();
    TileButtonWorld(Tile &tile, float scale = 1.0F);
    TileButtonWorld(Tile &tile, Object *par, float scale = 1.0F);
    ~TileButtonWorld();

    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) final;

    Vector2<int> GetPosition() final;
    void SetPosition(const Vector2<int> &value) final;

    Vector2<int> GetSize() final;
    void SetSize(const Vector2<int> &value) final;

    void SetLocalPosition(const Vector2<int> &value) final;

    bool IsRenderable() final;

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
    TileButtonScreen(Tile &tile, float scale = 1.0F);
    TileButtonScreen(Tile &tile, Object *par, float scale = 1.0F);
    ~TileButtonScreen() final;

    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) final;
    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer, float shine, bool selected,
              float time);

    Vector2<int> GetPosition() final;
    void SetPosition(const Vector2<int> &value) final;

    Vector2<int> GetSize() final;
    void SetSize(const Vector2<int> &value) final;

    Vector2<int> GetLocalPosition() final;
    void SetLocalPosition(const Vector2<int> &value) final;

    bool IsRenderable() final;

    Tile &getTile();

    bool IsMouseDown();
    bool IsMousePress();
    bool IsMouseHover();

   private:
    Tile tile;
};


#endif  // TILEBUTTON_H