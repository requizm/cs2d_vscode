#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include "../Models/UI/Panel.h"
#include "../Models/UI/TextBox.h"
#include "../Models/Camera.h"
#include "../Models/Tile.h"

struct ButtonTile
{
	Button button;
	bool exist;
	glm::ivec2 cell;
	ButtonTile(glm::ivec2 cell)
	{
		this->cell = cell;
		this->exist = false;
	}

	ButtonTile(Button button, glm::ivec2 cell)
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

	void NewMap(std::string tileSet, glm::vec2 mapSize);
	bool B_NewMap();

	void LoadMap(std::string mapPath);
	void B_LoadMap();

	std::shared_ptr<TextRenderer> textRenderer;
	SpriteRenderer menuRenderer;
	SquareRenderer squareRenderer;

	SpriteRenderer worldRenderer;
	std::shared_ptr<Camera> camera;
	glm::vec2 position;

	std::shared_ptr<Panel> controlPanel;
	std::shared_ptr<Panel> buildPanel;
	std::shared_ptr<Panel> tilePanel;

	std::shared_ptr<Panel> newPanel;

	std::shared_ptr<Panel> loadPanel, mapsPanel;
	std::shared_ptr<Button> b_map_load;
	std::vector<std::shared_ptr<Button>> mapsUI;
	std::shared_ptr<TextBox> t_load;
	int selectedMap = -1;

	std::vector<std::shared_ptr<Button>> tilesUI;
	glm::ivec2 texture;
	int tileCount;
	int maxCellInColumn;
	int maxCellInRow;

	Tile selectedTile;
	bool firstSelect;

	glm::ivec2 mapLimit;
	std::vector<ButtonTile> tiles;

	bool enable = false;
	float dt = 0;

	Button b_save, b_new, b_load;

	std::shared_ptr<Label> l_tile, l_mapSize, l_x;
	std::shared_ptr<TextBox> t_tile, t_mapSizeX, t_mapSizeY;
	std::shared_ptr<Button> b_okey, b_cancel;
	std::vector<std::string> maps;
	std::string currentTileSet;
	std::string currentName;

	glm::vec3 cell_yellow;
	glm::vec3 mouse_yellow;
};
#endif
