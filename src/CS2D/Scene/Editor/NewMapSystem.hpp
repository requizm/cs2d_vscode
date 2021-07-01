#ifndef NEWMAPSYSTEM_H
#define NEWMAPSYSTEM_H

#include "../../../Core/UI/Panel.hpp"
#include "ButtonTile.hpp"


struct NewMapResult
{
    std::vector<TileButtonScreen *> tilesUI;
    std::vector<ButtonTile *> tiles;
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

    NewMapResult NewMap(std::string tileSet, Vector2<int> mapSize);
    NewMapResult B_NewMap();

    Panel *newPanel;
    Label *l_tile, *l_mapSize, *l_x;
    TextBox *t_tile, *t_mapSizeX, *t_mapSizeY;
    TextButton *b_okey;
};

#endif