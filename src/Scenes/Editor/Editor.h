#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include "../../Models/UI/Panel.h"
#include "../../Models/UI/TextBox.h"
#include "../../Models/UI/RadioButton.h"
#include "../../Models/Camera.h"
#include "../../Models/Tile.h"
#include "SaveLoadSystem.h"
#include "NewMapSystem.h"


class Editor
{
public:
	Editor();
	Editor(const SpriteRenderer &menuRenderer, const SpriteRenderer &worldRenderer);
	virtual ~Editor();

	void Start();
	void OnEnable();
	void OnDisable();
	void Update(const float dt);
	void ProcessInput(const float dt);
	void Render(const float dt);

	void SetEnable(const bool value);

private:
	void SelectedRbChanged();

	std::shared_ptr<TextRenderer> textRenderer;
	SpriteRenderer menuRenderer;
	SquareRenderer squareRenderer;

	SpriteRenderer worldRenderer;
	std::shared_ptr<Camera> camera;
	Vector2<float> position;

	std::shared_ptr<Panel> controlPanel;
	std::shared_ptr<Panel> buildPanel;
	std::shared_ptr<Panel> tilePanel;

	NewMapSystem NewMap;

	SaveLoadSystem SaveLoad;

	std::shared_ptr<RadioButton> radioButton;

	std::vector<std::shared_ptr<Button>> tilesUI;
	Vector2<int> texture;
	int tileCount;
	int maxCellInColumn;
	int maxCellInRow;

	Tile *selectedTile;
	bool firstSelect;

	Vector2<int> mapLimit;
	std::vector<ButtonTile> tiles;

	bool enable = false;
	float dt = 0;

	Button b_save, b_new, b_load;

	std::shared_ptr<Panel> tilePropertiesPanel;
	std::shared_ptr<Button> b_tileProperties;

	std::shared_ptr<Button> b_cancel;

	std::string currentTileSet;
	std::string currentName;

	Vector3<float> cell_yellow;
	Vector3<float> mouse_yellow;
};
#endif
