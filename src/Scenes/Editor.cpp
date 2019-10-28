#include "Editor.h"
#include <iostream>

Editor::Editor()
{
}

Editor::Editor(SpriteRenderer *menuRenderer)
{
	this->menuRenderer = std::make_shared<SpriteRenderer>(*menuRenderer);
}

Editor::~Editor() = default;

void Editor::Init()
{
	textRenderer = std::make_shared<TextRenderer>(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	textRenderer->Load("../resources/fonts/liberationsans.ttf", 16);
	squareRenderer = std::make_shared<SquareRenderer>(true);
	this->camera = std::make_shared<Camera>(static_cast<int>(Game_Parameters::SCREEN_WIDTH), static_cast<int>(Game_Parameters::SCREEN_HEIGHT));
}

void Editor::Start()
{
	this->buildPanel = std::make_shared<Panel>(glm::vec2(0.0F), "Build Panel", glm::vec2(130, Game_Parameters::SCREEN_HEIGHT - 55), *textRenderer, true, false, 1.0F, glm::vec3(0.21F));
	this->buildPanel->setMovable(false);
	this->controlPanel = std::make_shared<Panel>(glm::vec2(0.0F), "Control Panel", glm::vec2(130, Game_Parameters::SCREEN_HEIGHT), *textRenderer, true, false, 1.0F, glm::vec3(0.21F));
	this->controlPanel->setMovable(false);
	//this->buildPanel->setParent(controlPanel.get(), true);
	this->buildPanel->setPosition(200, 0);
	this->controlPanel->setPosition(500, 0);

	this->buildPanel->setEnable(true);
	this->controlPanel->setEnable(true);

	cellWidth = ResourceManager::GetTexture("cs2dnorm").Width / 32;
	cellHeight = ResourceManager::GetTexture("cs2dnorm").Height / 32;
	tileCount = cellWidth * cellHeight;

	int curIndex = 0;
	for (int i = 0; i < cellWidth; i++)
	{
		for (int j = 0; j < cellHeight; j++)
		{
			const int xPos = (curIndex % 5);
			const int yPos = (curIndex / 5);
			const glm::vec2 pos(Game_Parameters::SCREEN_HEIGHT / 40 * xPos, Game_Parameters::SCREEN_HEIGHT / 40 * yPos);
			const glm::vec2 size(glm::vec2(Game_Parameters::SCREEN_HEIGHT / 40, Game_Parameters::SCREEN_HEIGHT / 40));
			const int xoffset = curIndex % (ResourceManager::GetTexture("cs2dnorm").Width / 32);
			const int yoffset = curIndex++ / (ResourceManager::GetTexture("cs2dnorm").Width / 32);
			const Sprite sprite = Sprite(ResourceManager::GetTexture("cs2dnorm"), (xoffset)*32, yoffset * 32, 32, 32);
			const Tile tile(pos, sprite, size);
			Button button = Button(tile);
			//button.setParent(buildPanel.get(), true);
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
	this->buildPanel->Update(dt);
	this->controlPanel->Update(dt);
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

	this->controlPanel->Draw(*squareRenderer.get(), *menuRenderer.get());
	this->buildPanel->Draw(*squareRenderer.get(), *menuRenderer.get());

	if (!tiles.empty())
	{
		for (auto &tile : tiles)
		{
			tile.Draw(*menuRenderer);
		}
	}
}
