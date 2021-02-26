#ifndef TILEBUTTON_H
#define TILEBUTTON_H

#include "../../Core/UI/UIObject.hpp"
#include "Tile.hpp"


class TileButtonWorld : public UIObject
{
   public:
    TileButtonWorld();
    TileButtonWorld(Tile &tile, Vector2<int> &cameraView, float scale = 1.0F);
    TileButtonWorld(Tile &tile, Vector2<int> &cameraView, Object *par, float scale = 1.0F);
    ~TileButtonWorld();

    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) final;

    Vector2<int> GetPosition() final;
    void SetPosition(const Vector2<int> &value) final;

    Vector2<int> GetSize() final;
    void SetSize(const Vector2<int> &value) final;

    Vector2<int> GetLocalPosition() final;
    void SetLocalPosition(const Vector2<int> &value) final;

    Tile &getTile();

    void addListener(std::function<void(TileButtonWorld *)> func);

   private:
    Tile tile;
    Vector2<int> *cameraView;

    std::vector<std::function<void(TileButtonWorld *)>> listenersDown;
    std::function<void()> mDown;

    bool isMouseHover();

    void onMouseDown();
};

class TileButtonScreen : public UIObject
{
   public:
    TileButtonScreen(Tile &tile, float scale = 1.0F);
    TileButtonScreen(Tile &tile, Object *par, float scale = 1.0F);
    ~TileButtonScreen();

    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) final;
    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer, float shine, bool selected,
              float time);

    Vector2<int> GetPosition() final;
    void SetPosition(const Vector2<int> &value) final;

    Vector2<int> GetSize() final;
    void SetSize(const Vector2<int> &value) final;

    Vector2<int> GetLocalPosition() final;
    void SetLocalPosition(const Vector2<int> &value) final;

    Tile &getTile();

    void addListener(std::function<void(TileButtonScreen *)> func);

    bool isMouseHover();

   private:
    Tile tile;

    std::vector<std::function<void(TileButtonScreen *)>> listenersDown;
    std::function<void()> mDown;

    void onMouseDown();
};


#endif  // TILEBUTTON_H