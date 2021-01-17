#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include "../../Models/UI/Panel.hpp"
#include "../../Models/UI/TextBox.hpp"
#include "../../Models/UI/RadioButton.hpp"
#include "../../Models/Camera.hpp"
#include "../../Models/Tile.hpp"
#include "SaveLoadSystem.hpp"
#include "NewMapSystem.hpp"
#include "Entities/Env_Item.hpp"

enum SelectedMode
{
	TILE_MOD,
	OBJECT_MOD
};

class Editor
{
public:
	Editor();
	Editor(const SpriteRenderer &menuRenderer, const SpriteRenderer &worldRenderer);
	~Editor();

	void Initialize(const SpriteRenderer &menuRenderer, const SpriteRenderer &worldRenderer);

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

	std::shared_ptr<TextRenderer> textRenderer;
	Panel *controlPanel;
	Panel *buildPanel;
	Panel *tilePanel, *objectPanel;

	std::vector<Env_Item *> env_items;

	std::string currentTileSet;

	Vector2<int> mapLimit;
	std::vector<ButtonTile*> tiles;

	std::shared_ptr<Camera> camera;

	SelectedMode selectedMode;

private:
	void SelectedRbChanged(RadioButtonElement *old, RadioButtonElement *n);

	SpriteRenderer menuRenderer;
	SquareRenderer squareRenderer;

	SpriteRenderer worldRenderer;

	Vector2<int> position;

	ListItem* objects_ui;

	NewMapSystem *NewMap;

	SaveLoadSystem *SaveLoad;

	std::vector<Button *> tilesUI;
	Vector2<int> texture;
	int tileCount;
	int maxCellInColumn;
	int maxCellInRow;

	Tile *selectedTile = nullptr;
	bool firstSelect;

	bool enable = false;
	float time = 0;

	std::shared_ptr<Button> b_save, b_new, b_load, b_objects, b_tiles;

	Panel *tilePropertiesPanel;
	Button *b_tileProperties;
	RadioButton *rb_tileProperties;

	Button *b_cancel;

	std::string currentName;

	Vector3<float> cell_yellow;
	Vector3<float> mouse_yellow;
};
#endif
