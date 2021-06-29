#ifndef NEWMAPSYSTEM_H
#define NEWMAPSYSTEM_H

#include <memory>

#include "../../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../../Core/Manager/ObjectManager.hpp"
#include "../../../Core/Manager/Utils.hpp"
#include "../../../Core/UI/Panel.hpp"
#include "../../../Core/UI/TextBox.hpp"


#include "ButtonTile.hpp"
#include "../../Model/TileButton.hpp"


struct NewMapResult
{
    std::vector<TileButtonScreen *> tilesUI;
    std::vector<ButtonTile *> tiles;
};

class NewMapSystem
{
   public:
    NewMapSystem(/* args */);
    ~NewMapSystem();

    void Start();
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