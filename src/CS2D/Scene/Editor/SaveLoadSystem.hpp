#ifndef SAVELOADSYSTEM_H
#define SAVELOADSYSTEM_H

#include <rapidxml-1.13/rapidxml.hpp>
#include <rapidxml-1.13/rapidxml_print.hpp>
#ifdef WIN32
#include <dirent/dirent.h>
#endif  // WIN32
#ifdef LINUX
#include <dirent.h>
#endif  // LINUX
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>

#include "../../../Core/Loader/XMLLoader.hpp"
#include "../../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../../Core/UI/ListItem.hpp"
#include "../../../Core/UI/Panel.hpp"
#include "../../../Core/UI/TextBox.hpp"
#include "../../Other/GameParameters.hpp"
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

    // save
    void SaveMap();
    void B_SaveMap();
    void SaveListChanged(TextButton *old, TextButton *n);
    Panel *savePanel, *save_mapsPanel;
    Button *b_map_save;
    TextBox *t_save;
    ListItem *save_listMaps;

    // load
    std::vector<ButtonTile *> LoadMap(std::string &mapName);
    void B_LoadMap();
    void LoadListChanged(TextButton *old, TextButton *n);
    Panel *loadPanel, *load_mapsPanel;
    Button *b_map_load;
    TextBox *t_load;
    ListItem *load_listMaps;

    // both
    bool isPressedOrHover();
    bool isEditMode();
    bool isMouseHover();

   private:
    std::vector<std::string> getMapNames();
};

#endif