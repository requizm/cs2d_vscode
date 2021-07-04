#ifndef EDITOR_H
#define EDITOR_H

#include "../../../Core/Model/Camera.hpp"
#include "../../../Core/UI/RadioButton.hpp"
#include "../../Model/Scene.hpp"
#include "../../Model/Tile.hpp"
#include "Entities/Env_Item.hpp"
#include "NewMapSystem.hpp"
#include "SaveLoadSystem.hpp"


enum SelectedMode
{
    TILE_MOD,
    OBJECT_MOD
};

class Editor : public Scene
{
   public:
    Editor();
    ~Editor() = default;

    void Initialize();

    void Load() final;
    void Unload() final;
    void Update() final;
    void ProcessInput() final;
    void Render() final;

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

    NewMapResult *tils = nullptr;

    float time = 0;
    Vector2<int> texture;
    int tileCount;
    int maxCellInColumn;
    int maxCellInRow;
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

    SpriteButton *b_save, *b_new, *b_load, *b_objects, *b_tiles;

    Panel *tilePropertiesPanel;
    TextButton *b_tileProperties;
    RadioButton *rb_tileProperties;

    std::string currentName;

    Vector3<float> cell_yellow;
    Vector3<float> mouse_yellow;
};
#endif
