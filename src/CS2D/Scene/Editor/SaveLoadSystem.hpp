#ifndef SAVELOADSYSTEM_H
#define SAVELOADSYSTEM_H

#include "../../../Core/UI/ListItem.hpp"
#include "ButtonTile.hpp"
#include "NewMapSystem.hpp"


class SaveLoadSystem
{
   public:
    SaveLoadSystem() = default;
    ~SaveLoadSystem() = default;

    void Load();
    void ProcessInput();
    void Update();
    void Render(SpriteRenderer &menuRenderer, SquareRenderer &squareRenderer);

    // save
    void SaveMap();
    void B_SaveMap();
    void SaveListChanged(TextButton *old, TextButton *n);
    std::shared_ptr<Panel> savePanel, save_mapsPanel;
    std::shared_ptr<TextButton> b_map_save;
    std::shared_ptr<TextBox> t_save;
    std::shared_ptr<ListItem> save_listMaps;

    // load
    std::unique_ptr<NewMapResult> LoadMap(const std::string &mapName);
    void B_LoadMap();
    void LoadListChanged(TextButton *old, TextButton *n);
    std::shared_ptr<Panel> loadPanel, load_mapsPanel;
    std::shared_ptr<TextButton> b_map_load;
    std::shared_ptr<TextBox> t_load;
    std::shared_ptr<ListItem> load_listMaps;

    // both
    bool isPressedOrHover();
    bool isEditMode();
    bool isMouseHover();
};

#endif