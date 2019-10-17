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
	Editor(SpriteRenderer* menuRenderer);
	virtual ~Editor();

	void Init();
	void Update(const float dt);
	void ProcessInput(const float dt);
	void Render(const float dt);

private:
	std::shared_ptr<TextRenderer> textRenderer;
	std::shared_ptr<SpriteRenderer> menuRenderer;
	std::shared_ptr<SquareRenderer> squareRenderer;
	std::shared_ptr<Camera> camera;
	glm::vec2 position;

	std::shared_ptr<Panel> controlPanel;
	std::shared_ptr<Panel> buildPanel;

	std::vector<Button> tiles;
	int cellWidth, cellHeight, tileCount;
	int maxCellInColumn = 5;
};
#endif

