#ifndef EDITOR_H
#define EDITOR_H

#include <vector>
#include "../Models/UI/Panel.h"
#include "../Models/UI/TextBox.h"
#include "../Models/Camera.h"
#include "../Models/Tile.h"

class Editor
{
public:
	Editor();
	Editor(const SpriteRenderer &menuRenderer);
	virtual ~Editor();

	void Init();
	void Start();
	void Update(const float dt);
	void ProcessInput(const float dt);
	void Render(const float dt);

private:
	TextRenderer textRenderer;
	SpriteRenderer menuRenderer;
	SquareRenderer squareRenderer;
	std::shared_ptr<Camera> camera;
	glm::vec2 position;

	std::shared_ptr<Panel> controlPanel;
	std::shared_ptr<Panel> buildPanel;
	std::shared_ptr<Panel> tilePanel;

	std::vector<Button> tiles;
	int cellWidth, cellHeight, tileCount;
	int maxCellInColumn = 5;
	int maxCellInRow;

	bool start;
	float dt;
};
#endif

