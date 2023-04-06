#ifndef EDITOR_H
#define EDITOR_H

#include <memory>

#include "../../../Core/Model/Camera.hpp"
#include "../../../Core/UI/RadioButton.hpp"
#include "../../Model/Scene.hpp"
#include "../../Model/Tile.hpp"
#include "../../Renderer/EditorMapRenderer.hpp"
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

    std::shared_ptr<TextRenderer> textRenderer;
    std::shared_ptr<Panel> controlPanel;
    std::shared_ptr<Panel> buildPanel;
    std::shared_ptr<Panel> tilePanel, objectPanel;

    std::vector<std::shared_ptr<Env_Item>> env_items;
    std::shared_ptr<Env_Item_Manager> envItemManager;

    std::string currentTileSet;

    Vector2<int> mapLimit;

    std::shared_ptr<Camera> camera;

    SelectedMode selectedMode;

    std::unique_ptr<NewMapResult> tils;

    Vector2<int> texture;
    int tileCount;
    int maxCellInColumn;
    int maxCellInRow;
    Vector2<int> position;

   private:
    void SelectedRbChanged(RadioButtonElement *old, RadioButtonElement *n);

    std::shared_ptr<SpriteRenderer> menuRenderer = nullptr;
    std::shared_ptr<SquareRenderer> squareRenderer = nullptr;
    std::shared_ptr<SpriteRenderer> worldRenderer = nullptr;

    std::shared_ptr<ListItem> objects_ui = nullptr;

    std::shared_ptr<NewMapSystem> NewMap = nullptr;
    std::shared_ptr<SaveLoadSystem> SaveLoad = nullptr;


    std::shared_ptr<Tile> selectedTile = nullptr;
    std::shared_ptr<Env_Item> selectedItem = nullptr;

    std::shared_ptr<SpriteButton> b_save, b_new, b_load, b_objects, b_tiles;

    std::shared_ptr<Panel> tilePropertiesPanel = nullptr;
    std::shared_ptr<TextButton> b_tileProperties = nullptr;
    std::shared_ptr<RadioButton> rb_tileProperties = nullptr;

    std::string currentName;

    Vector3<float> cell_yellow;
    Vector3<float> mouse_yellow;

    std::shared_ptr<EditorMapRenderer> editorMapRenderer = nullptr;

    bool firstLoad = true;
};
#endif
