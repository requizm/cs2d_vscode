#ifndef NEWMAPSYSTEM_H
#define NEWMAPSYSTEM_H

#include "../../../Core/UI/Panel.hpp"
#include "ButtonTile.hpp"


struct NewMapResult
{
    TileButtonScreen *tilesUI;
    ButtonTile *tiles;

    int tilesUILength = 0;
    int tilesLength = 0;

    ~NewMapResult()
    {
        for (int i = 0; i < tilesUILength; i++)
        {
            tilesUI[i].~TileButtonScreen();
        }
        for (int i = 0; i < tilesLength; i++)
        {
            tiles[i].~ButtonTile();
        }
        free(tiles);
        free(tilesUI);
#if defined(TRACY_ENABLE)
        TracyFree(tiles);
        TracyFree(tilesUI);
#endif
    }
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
    NewMapResult *B_NewMap();

    Panel *newPanel;
    Label *l_tile, *l_mapSize, *l_x;
    TextBox *t_tile, *t_mapSizeX, *t_mapSizeY;
    TextButton *b_okey;
};

#endif