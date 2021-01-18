#ifndef NEWMAPSYSTEM_H
#define NEWMAPSYSTEM_H

#include "../../Models/UI/Panel.hpp"
#include "../../Models/UI/TextBox.hpp"
#include <memory>
#include "ButtonTile.hpp"

struct NewMapResult
{
    std::vector<Button *> tilesUI;
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

    NewMapResult *NewMap(std::string tileSet, Vector2<int> mapSize, float &dt, Vector2<int> &pos, bool &fSelect,
                         Vector2<int> &mLimit, Vector2<int> &texture, int &tCount, Panel *tPanel,
                         Panel *bPanel, int maxCell);
    NewMapResult *B_NewMap(float &dt, Vector2<int> &pos, bool &fSelect, Vector2<int> &mLimit,
                           Vector2<int> &texture, int &tCount, Panel *tPanel,
                           Panel *bPanel, int maxCell);

    Panel *newPanel;
    Label *l_tile, *l_mapSize, *l_x;
    TextBox *t_tile, *t_mapSizeX, *t_mapSizeY;
    Button *b_okey;
};

#endif