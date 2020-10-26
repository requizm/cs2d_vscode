#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include "../Models/UI/Panel.h"
#include "../Models/UI/TextBox.h"
#include "../Models/UI/RadioButton.h"
#include "../Models/Camera.h"
#include "../Models/Tile.h"

struct ButtonTile
{
	Button button;
	bool exist;
	Vector2<int> cell;
	ButtonTile(Vector2<int> cell)
	{
		this->cell = cell;
		this->exist = false;
	}

	ButtonTile(Button &button, Vector2<int> cell)
	{
		this->button = button;
		this->cell = cell;
		this->exist = true;
	}
};

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
	void SaveMap();
	void B_SaveMap();

	void NewMap(std::string tileSet, Vector2<int> mapSize);
	bool B_NewMap();

	void LoadMap(std::string mapPath);
	void B_LoadMap();

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

	std::shared_ptr<Panel> newPanel;

	std::shared_ptr<Panel> loadPanel, load_mapsPanel;
	std::shared_ptr<Button> b_map_load;
	std::shared_ptr<TextBox> t_load;

	std::shared_ptr<Panel> savePanel, save_mapsPanel;
	std::shared_ptr<Button> b_map_save;
	std::shared_ptr<TextBox> t_save;

	std::vector<std::shared_ptr<Button>> mapsUI;
	int selectedMap = -1;

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

	std::shared_ptr<Label> l_tile, l_mapSize, l_x;
	std::shared_ptr<TextBox> t_tile, t_mapSizeX, t_mapSizeY;
	std::shared_ptr<Button> b_okey, b_cancel;
	std::vector<std::string> maps;
	std::string currentTileSet;
	std::string currentName;

	Vector3<float> cell_yellow;
	Vector3<float> mouse_yellow;
};
#endif
