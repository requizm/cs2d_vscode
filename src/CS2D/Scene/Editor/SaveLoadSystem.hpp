#ifndef SAVELOADSYSTEM_H
#define SAVELOADSYSTEM_H

#include "../../../Core/UI/ListItem.hpp"
#include "ButtonTile.hpp"


class SaveLoadSystem
{
   public:
    SaveLoadSystem() = default;
    ~SaveLoadSystem();

    void Load();
    void ProcessInput();
    void Update();
    void Render(SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer);

    // save
    void SaveMap();
    void B_SaveMap();
    void SaveListChanged(TextButton *old, TextButton *n);
    Panel *savePanel, *save_mapsPanel;
    TextButton *b_map_save;
    TextBox *t_save;
    ListItem *save_listMaps;

    // load
    NewMapResult *LoadMap(const std::string &mapName);
    void B_LoadMap();
    void LoadListChanged(TextButton *old, TextButton *n);
    Panel *loadPanel, *load_mapsPanel;
    TextButton *b_map_load;
    TextBox *t_load;
    ListItem *load_listMaps;

    // both
    bool isPressedOrHover();
    bool isEditMode();
    bool isMouseHover();
};

#endif