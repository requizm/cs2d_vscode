#ifndef SAVELOADSYSTEM_H
#define SAVELOADSYSTEM_H

#include <memory>
#include <vector>
#include "../../Models/UI/Panel.hpp"
#include "../../Models/UI/TextBox.hpp"
#include "../../Models/UI/ListItem.hpp"
#include "ButtonTile.hpp"

class SaveLoadSystem
{
private:
    /* data */
public:
    SaveLoadSystem();
    ~SaveLoadSystem();

    void Start();
    void ProcessInput();
    void Update();
    void Render(SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer);

    //save
    void SaveMap();
    void B_SaveMap();
    void SaveListChanged(Button *old, Button *n);
    Panel *savePanel, *save_mapsPanel;
    Button *b_map_save;
    TextBox *t_save;
    ListItem *save_listMaps;

    //load
    std::vector<ButtonTile*> LoadMap(std::string mapName);
    void B_LoadMap();
    void LoadListChanged(Button *old, Button *n);
    Panel *loadPanel, *load_mapsPanel;
    Button *b_map_load;
    TextBox *t_load;
    ListItem *load_listMaps;

    //both
    bool isPressedOrHover();
    bool isEditMode();
    bool isMouseHover();

private:
    std::vector<std::string> getMapNames();
};

#endif