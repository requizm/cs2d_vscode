#ifndef NEWMAPSYSTEM_H
#define NEWMAPSYSTEM_H

#include "../../Models/UI/Panel.hpp"
#include "../../Models/UI/TextBox.hpp"
#include <memory>
#include "ButtonTile.hpp"

struct NewMapResult
{
    std::vector<std::shared_ptr<Button>> tilesUI;
    std::vector<ButtonTile> tiles;
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

    NewMapResult* NewMap(std::string tileSet, Vector2<int> mapSize, float &dt, Vector2<int> &pos, bool &fSelect,
                        Vector2<int> &mLimit, Vector2<int> &texture, int &tCount, std::shared_ptr<Panel> &tPanel,
                        std::shared_ptr<Panel> &bPanel, Tile &sTile, int maxCell);
    NewMapResult* B_NewMap(float &dt, Vector2<int> &pos, bool &fSelect, Vector2<int> &mLimit,
                          Vector2<int> &texture, int &tCount, std::shared_ptr<Panel> &tPanel,
                          std::shared_ptr<Panel> &bPanel, Tile &sTile, int maxCell);

    std::shared_ptr<Panel> newPanel;
    std::shared_ptr<Label> l_tile, l_mapSize, l_x;
    std::shared_ptr<TextBox> t_tile, t_mapSizeX, t_mapSizeY;
    std::shared_ptr<Button> b_okey;
};

#endif