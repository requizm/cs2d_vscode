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
    std::shared_ptr<Panel> savePanel, save_mapsPanel;
    std::shared_ptr<Button> b_map_save;
    std::shared_ptr<TextBox> t_save;
    std::shared_ptr<ListItem> save_listMaps;

    //load
    std::vector<ButtonTile> LoadMap(std::string mapName);
    void B_LoadMap();
    std::shared_ptr<Panel> loadPanel, load_mapsPanel;
    std::shared_ptr<Button> b_map_load;
    std::shared_ptr<TextBox> t_load;
    std::shared_ptr<ListItem> load_listMaps;

    //both
    bool isPressedOrHover();
    bool isEditMode();
    bool isMouseHover();

private:
    std::vector<std::string> getMapNames();
};

#endif