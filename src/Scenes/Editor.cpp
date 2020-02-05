#include "Editor.h"
#include <iostream>

Editor::Editor()
{
}

Editor::Editor(const SpriteRenderer &menuRenderer)
{
	this->menuRenderer = menuRenderer;
}

Editor::~Editor() = default;

void Editor::Init()
{
	textRenderer = TextRenderer(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	textRenderer.Load("../resources/fonts/liberationsans.ttf", 16);
	squareRenderer = SquareRenderer(true);
	this->camera = std::make_shared<Camera>(static_cast<int>(Game_Parameters::SCREEN_WIDTH), static_cast<int>(Game_Parameters::SCREEN_HEIGHT));
}

void Editor::Start()
{
	this->buildPanel = std::make_shared<Panel>(glm::vec2(0.0F), "Build Panel", glm::vec2(32 * 5 + 2, Game_Parameters::SCREEN_HEIGHT), textRenderer, true, false, 1.0F, glm::vec3(0.21F));
	this->buildPanel->setMovable(false);
	this->buildPanel->setEnable(true);
	this->buildPanel->setID(1);

	this->controlPanel = std::make_shared<Panel>(glm::vec2(0.0F), "Control Panel", glm::vec2(32 * 5 + 2, Game_Parameters::SCREEN_HEIGHT), textRenderer, true, false, 1.0F, glm::vec3(0.21F));
	this->controlPanel->setMovable(false);
	this->controlPanel->setEnable(false);

	this->tilePanel = std::make_shared<Panel>(glm::vec2(0.0F, 75.0F), "", glm::vec2(32 * 5 + 2, 32 * 19 + 2), textRenderer, true, false, 1.0F, glm::vec3(0.21F));
	this->tilePanel->setEnable(true);
	this->tilePanel->setMovable(false);
	this->tilePanel->setID(2);
	this->tilePanel->setScrollable(true);
	this->tilePanel->setScrollOffset(0);
	this->tilePanel->setOutline(true);
	this->tilePanel->setOutlineColor(glm::vec3(0.5F));
	//this->buildPanel->setParent(controlPanel->get(), true);

	cellWidth = ResourceManager::GetTexture("cs2dnorm").Width / 32;
	cellHeight = ResourceManager::GetTexture("cs2dnorm").Height / 32;
	tileCount = cellWidth * cellHeight;
	if (tileCount % maxCellInRow != 0)
		maxCellInRow = this->tilePanel->getSize().y / 32 + 1;
	else
		maxCellInRow = this->tilePanel->getSize().y / 32;
	//Logger::DebugLog(std::to_string(maxCellInRow));

	int curIndex = 0;
	for (int i = 0; i < cellWidth; i++)
	{
		for (int j = 0; j < cellHeight; j++)
		{
			const int xPos = 32 * (curIndex % maxCellInColumn);
			const int yPos = 32 * (curIndex / maxCellInColumn);
			const glm::vec2 pos(xPos, yPos);
			const glm::vec2 size(glm::vec2(32, 32));
			const int xoffset = curIndex % (ResourceManager::GetTexture("cs2dnorm").Width / 32);
			const int yoffset = curIndex++ / (ResourceManager::GetTexture("cs2dnorm").Width / 32);
			const Sprite sprite = Sprite(ResourceManager::GetTexture("cs2dnorm"), (xoffset)*32, yoffset * 32, 32, 32);
			const Tile tile(pos, sprite, size);
			Button button = Button(tile);
			button.setParent(tilePanel.get(), true);
			tiles.push_back(button);
		}
	}

	start = false;
}

void Editor::Update(const float dt)
{
	this->dt += dt;
	if (this->dt < 0.5f)
		return;
	if (start)
		Start();

	this->controlPanel->Update(dt);
	this->buildPanel->Update(dt);
	this->tilePanel->Update(dt);

	if (this->tilePanel->isScrollable() && InputManager::scrollYPressed)
	{
		if (!tiles.empty())
		{
			bool check_1 = tiles.at(0).getLocalPosition().y == 0 && InputManager::scrollY > 0;
			bool check_2 = tiles.at(tileCount - 1).getLocalPosition().y == maxCellInRow * 32 && InputManager::scrollY < 0;

			if (!check_1 && !check_2)
			{
				for (auto &tile : tiles)
				{
					tile.setPosition(tile.getLocalPosition().x, tile.getLocalPosition().y + InputManager::scrollY * 32);
				}
			}
		}
		InputManager::scrollYPressed = false;
	}
	if (!tiles.empty())
	{
		for (auto &tile : tiles)
		{
			if (tile.isMouseDown(GLFW_MOUSE_BUTTON_LEFT))
			{
				Logger::DebugLog("down");
			}
			if (tile.isMouseUp(GLFW_MOUSE_BUTTON_LEFT))
			{
				Logger::DebugLog("up");
			}
		}
	}
}

void Editor::ProcessInput(const float dt)
{
	if (this->dt < 0.5f)
		return;
	if (InputManager::isKey(GLFW_KEY_W))
	{
		this->position = glm::vec2(this->position.x, this->position.y - 1.0F);
	}
	if (InputManager::isKey(GLFW_KEY_S))
	{
		this->position = glm::vec2(this->position.x, this->position.y + 1.0F);
	}
	if (InputManager::isKey(GLFW_KEY_A))
	{
		this->position = glm::vec2(this->position.x - 1.0F, this->position.y);
	}
	if (InputManager::isKey(GLFW_KEY_D))
	{
		this->position = glm::vec2(this->position.x + 1.0F, this->position.y);
	}
}

void Editor::Render(const float dt)
{
	if (this->dt < 0.5f)
		return;
	//	camera->setPosition(position);
	//	camera->update();
	//ResourceManager::GetShader("sprite").Use();
	//	ResourceManager::GetShader("sprite").SetMatrix4("projection", camera->cameraMatrix);

	this->controlPanel->Draw(squareRenderer, menuRenderer);
	this->buildPanel->Draw(squareRenderer, menuRenderer);
	this->tilePanel->Draw(squareRenderer, menuRenderer);
	if (!tiles.empty())
	{
		for (auto &tile : tiles)
		{
			tile.Draw(menuRenderer);
		}
	}
}
