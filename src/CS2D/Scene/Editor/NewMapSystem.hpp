#ifndef NEWMAPSYSTEM_H
#define NEWMAPSYSTEM_H

#include <memory>

#include "../../../Core/UI/Panel.hpp"
#include "ButtonTile.hpp"


struct NewMapResult
{
    std::shared_ptr<std::shared_ptr<TileButtonScreen>[]> tilesUI;
    std::shared_ptr<std::shared_ptr<ButtonTile>[]> tiles;

    int tilesUILength = 0;
    int tilesLength = 0;
};

class NewMapSystem
{
   public:
    NewMapSystem() = default;
    ~NewMapSystem() = default;

    void Load();
    void ProcessInput();
    void Update();
    void Render(SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer);

    bool isPressedOrHover();
    bool isEditMode();
    bool isMouseHover();

    std::unique_ptr<NewMapResult> NewMap(const std::string &tileSet, const Vector2<int> &mapSize);
    std::unique_ptr<NewMapResult> B_NewMap();

    std::shared_ptr<Panel> newPanel;
    std::shared_ptr<Label> l_tile, l_mapSize, l_x;
    std::shared_ptr<TextBox> t_tile, t_mapSizeX, t_mapSizeY;
    std::shared_ptr<TextButton> b_okey;
};

#endif