#ifndef SAVELOADSYSTEM_H
#define SAVELOADSYSTEM_H

#include <rapidxml-1.13/rapidxml.hpp>
#include <rapidxml-1.13/rapidxml_print.hpp>
#include <dirent/dirent.h>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

#include "../../Models/UI/Panel.hpp"
#include "../../Models/UI/TextBox.hpp"
#include "../../Models/UI/ListItem.hpp"
#include "ButtonTile.hpp"
#include "../../Others/Game_Parameters.hpp"
#include "../../Core/Loader/XMLLoader.hpp"

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
    std::vector<ButtonTile *> LoadMap(std::string &mapName);
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