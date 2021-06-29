#ifndef EDITOR_H
#define EDITOR_H

#ifdef WIN32
#include <dirent/dirent.h>
#endif  // WIN32
#ifdef LINUX
#include <dirent.h>
#endif  // LINUX
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../../Core/Manager/ObjectManager.hpp"
#include "../../../Core/Manager/Timer.hpp"
#include "../../../Core/Model/Camera.hpp"
#include "../../Model/Tile.hpp"
#include "../../../Core/UI/ListItem.hpp"
#include "../../../Core/UI/Panel.hpp"
#include "../../../Core/UI/RadioButton.hpp"
#include "../../../Core/UI/TextBox.hpp"
#include "../../Game.hpp"
#include "../../Other/GameParameters.hpp"
#include "Entities/Env_Item.hpp"
#include "NewMapSystem.hpp"
#include "SaveLoadSystem.hpp"


enum SelectedMode
{
    TILE_MOD,
    OBJECT_MOD
};

class Editor
{
   public:
    Editor();
    ~Editor();

    void Initialize();

    static Editor &instance()
    {
        static Editor INSTANCE;
        return INSTANCE;
    }

    void Start();
    void OnEnable();
    void OnDisable();
    void Update();
    void ProcessInput();
    void Render();

    void SetEnable(const bool value);

    TextRenderer *textRenderer;
    Panel *controlPanel;
    Panel *buildPanel;
    Panel *tilePanel, *objectPanel;

    std::vector<Env_Item *> env_items;
    Env_Item_Manager *envItemManager;

    std::string currentTileSet;

    Vector2<int> mapLimit;

    Camera *camera;

    SelectedMode selectedMode;

    NewMapResult *tils;

    float time = 0;
    Vector2<int> texture;
    int tileCount;
    int maxCellInColumn;
    int maxCellInRow;
    bool firstSelect;
    Vector2<int> position;

   private:
    void SelectedRbChanged(RadioButtonElement *old, RadioButtonElement *n);

    SpriteRenderer *menuRenderer;
    SquareRenderer *squareRenderer;

    SpriteRenderer *worldRenderer;

    ListItem *objects_ui;

    NewMapSystem *NewMap;

    SaveLoadSystem *SaveLoad;

    Tile *selectedTile = nullptr;
    Env_Item *selectedItem = nullptr;

    bool enable = false;

    SpriteButton *b_save, *b_new, *b_load, *b_objects, *b_tiles;

    Panel *tilePropertiesPanel;
    TextButton *b_tileProperties;
    RadioButton *rb_tileProperties;

    TextButton *b_cancel;

    std::string currentName;

    Vector3<float> cell_yellow;
    Vector3<float> mouse_yellow;
};
#endif
