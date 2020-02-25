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
	void Button_NewMap(std::string tileSet, glm::vec2 mapSize);

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

	std::vector<Button> tilesUI;
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

	Button save_button, new_button, load_button;

	glm::vec3 cell_yellow;
	glm::vec3 mouse_yellow;
};
#endif

