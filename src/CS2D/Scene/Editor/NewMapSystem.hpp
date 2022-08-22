#ifndef NEWMAPSYSTEM_H
#define NEWMAPSYSTEM_H

#include <memory>

#include "../../../Core/UI/Panel.hpp"
#include "ButtonTile.hpp"


struct NewMapResult
{
    std::unique_ptr<TileButtonScreen[]> tilesUI;
    std::unique_ptr<ButtonTile[]> tiles;

    int tilesUILength = 0;
    int tilesLength = 0;
};

class NewMapSystem
{
   public:
    NewMapSystem() = default;
    ~NewMapSystem();

    void Load();
    void ProcessInput();
    void Update();
    void Render(SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer);

    bool isPressedOrHover();
    bool isEditMode();
    bool isMouseHover();

    NewMapResult *NewMap(const std::string &tileSet, const Vector2<int> &mapSize);
    std::unique_ptr<NewMapResult> B_NewMap();

    Panel *newPanel;
    Label *l_tile, *l_mapSize, *l_x;
    TextBox *t_tile, *t_mapSizeX, *t_mapSizeY;
    TextButton *b_okey;
};

#endif