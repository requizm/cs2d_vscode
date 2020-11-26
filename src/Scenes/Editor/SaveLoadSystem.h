#ifndef SAVELOADSYSTEM_H
#define SAVELOADSYSTEM_H

#include <memory>
#include <vector>
#include "../../Models/UI/Panel.h"
#include "../../Models/UI/TextBox.h"
#include "ButtonTile.h"

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
    void SaveMap(std::vector<ButtonTile> &tiles, Vector2<int> &mLimit, std::string &tSet);
    void B_SaveMap(TextRenderer &textRenderer);
    std::shared_ptr<Panel> savePanel, save_mapsPanel;
    std::shared_ptr<Button> b_map_save;
    std::shared_ptr<TextBox> t_save;
    std::vector<std::shared_ptr<Button>> save_mapsUI;

    //load
    std::vector<ButtonTile> LoadMap(std::string mapName, Vector2<int> &mLimit, std::string &tSet);
    void B_LoadMap(TextRenderer &textRenderer);
    std::shared_ptr<Panel> loadPanel, load_mapsPanel;
    std::shared_ptr<Button> b_map_load;
    std::shared_ptr<TextBox> t_load;
    std::vector<std::shared_ptr<Button>> load_mapsUI;

    //both
    bool isPressedOrHover();
    bool isEditMode();
    bool isMouseHover();

private:
    std::vector<std::string> getMapNames();

public:
    std::vector<std::shared_ptr<Button>> mapsUI;
    int selectedMap = -1;
};

#endif