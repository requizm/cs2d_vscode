#include "Editor.h"
#include <iostream>
#include <fstream>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "../Others/Game_Parameters.h"
#include "../Others/Utils.h"
#include "../Game.h"

Editor::Editor()
{
}

Editor::Editor(const SpriteRenderer &menuRenderer, const SpriteRenderer &worldRenderer)
{
	this->menuRenderer = menuRenderer;
	this->worldRenderer = worldRenderer;
}

Editor::~Editor() = default;

void Editor::Init()
{
	textRenderer = TextRenderer(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	textRenderer.Load("../resources/fonts/liberationsans.ttf", 16);
	squareRenderer = SquareRenderer(true);
	this->camera = std::make_shared<Camera>(static_cast<int>(Game_Parameters::SCREEN_WIDTH), static_cast<int>(Game_Parameters::SCREEN_HEIGHT));
	mouse_yellow = glm::vec3(0.73F, 0.73F, 0.0F);
	cell_yellow = glm::vec3(0.15F, 0.15F, 0.0F);
}

void Editor::Start()
{
	this->dt = 0.0F;
	position = glm::vec2(0.0F);
	tiles.clear();
	tilesUI.clear();

	maxCellInColumn = 5;
	firstSelect = false;

	mapXLimit = 50;
	mapYLimit = 50;

	cellWidth = ResourceManager::GetTexture("cs2dnorm").Width / 32;
	cellHeight = ResourceManager::GetTexture("cs2dnorm").Height / 32;
	tileCount = cellWidth * cellHeight;
	if (tileCount % maxCellInColumn != 0)
		maxCellInRow = (Game_Parameters::SCREEN_HEIGHT - (32 * 4) - 22) / 32 + 1;
	else
		maxCellInRow = (Game_Parameters::SCREEN_HEIGHT - (32 * 4) - 22) / 32;

	this->buildPanel = std::make_shared<Panel>(glm::vec2(0.0F, 0.0F), "Build Panel", glm::vec2(32 * maxCellInColumn + (5 * 2), Game_Parameters::SCREEN_HEIGHT), textRenderer, true, false, 1.0F, glm::vec3(0.21F), 1.0F);
	this->buildPanel->setMovable(false);
	this->buildPanel->setEnable(true);
	this->buildPanel->setID(1);

	this->controlPanel = std::make_shared<Panel>(glm::vec2(5.0F, 5.0F), "Control Panel", glm::vec2(32 * maxCellInColumn, 32 * 2 - 11), textRenderer, true, false, 1.0F, glm::vec3(0.21F), 1.0F);
	this->controlPanel->setMovable(false);
	this->controlPanel->setEnable(true);
	this->buildPanel->setID(3);

	this->tilePanel = std::make_shared<Panel>(glm::vec2(5.0F, 75.0F), "", glm::vec2(32 * maxCellInColumn, 32 * maxCellInRow), textRenderer, true, false, 1.0F, glm::vec3(0.21F), 1.0F);
	this->tilePanel->setEnable(true);
	this->tilePanel->setMovable(false);
	this->tilePanel->setID(2);
	this->tilePanel->setScrollable(true);
	this->tilePanel->setScrollOffset(0);
	this->tilePanel->setOutline(true);
	this->tilePanel->setOutlineColor(glm::vec3(0.47F));
	//this->buildPanel->setParent(controlPanel->get(), true);

	int curIndex = 0;
	for (int i = 0; i < cellWidth * cellHeight; i++)
	{
		const int xPos = 32 * (curIndex % maxCellInColumn);
		const int yPos = 32 * (curIndex / maxCellInColumn);
		const glm::vec2 pos(xPos, yPos);
		const glm::vec2 size(glm::vec2(32, 32));
		const int xoffset = curIndex % (ResourceManager::GetTexture("cs2dnorm").Width / 32);
		const int yoffset = curIndex / (ResourceManager::GetTexture("cs2dnorm").Width / 32);
		const Sprite sprite = Sprite(ResourceManager::GetTexture("cs2dnorm"), (xoffset)*32, yoffset * 32, 32, 32);
		const Tile tile = Tile(pos, sprite, size, TileTypes::FLOOR, curIndex++);
		Button button = Button(tile);
		button.setParent(tilePanel.get(), true);
		tilesUI.push_back(button);
	}

	for (int i = 0; i < mapXLimit; i++)
	{
		for (int j = 0; j < mapYLimit; j++)
		{
			ButtonTile t = ButtonTile(glm::ivec2(i, j));
			tiles.push_back(t);
		}
	}
	start = false;

	Sprite save_sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 48, 0, 16, 16);
	glm::vec2 pos = this->controlPanel->getPosition();
	pos.x += 60;
	save_button = Button(save_sprite, pos, glm::vec2(32 * maxCellInColumn / 7));
}

void Editor::Update(const float dt)
{
	this->dt += dt;
	if (this->dt < 0.5f)
		return;
	if (start)
	{
		Start();
		return;
	}

	this->controlPanel->Update(dt);
	this->buildPanel->Update(dt);
	this->tilePanel->Update(dt);
	this->save_button.Update(dt);

	if (this->tilePanel->isScrollable() && InputManager::scrollYPressed)
	{
		if (!tilesUI.empty())
		{
			bool check_1 = tilesUI.at(0).getLocalPosition().y == 0 && InputManager::scrollY > 0;
			bool check_2 = tilesUI.at(tileCount - 1).getLocalPosition().y == maxCellInRow * 32 && InputManager::scrollY < 0;

			if (!check_1 && !check_2)
			{
				for (auto &tile : tilesUI)
				{
					tile.setPosition(tile.getLocalPosition().x, tile.getLocalPosition().y + InputManager::scrollY * 32);
				}
			}
		}
		InputManager::scrollYPressed = false;
	}
}

void Editor::ProcessInput(const float dt)
{
	if (this->dt < 0.5f)
		return;

	if (!tilesUI.empty())
	{
		for (auto &tile : tilesUI)
		{
			if (tile.isMouseDown(GLFW_MOUSE_BUTTON_LEFT) && tile.isRenderable())
			{
				Logger::DebugLog("down");
				selectedTile = tile.getTile();
				firstSelect = true;
			}
			if (tile.isMouseUp(GLFW_MOUSE_BUTTON_LEFT))
			{
				Logger::DebugLog("up");
			}
		}
	}

	if (InputManager::isKey(GLFW_KEY_W))
	{
		this->position = glm::vec2(this->position.x, this->position.y - Game_Parameters::SCREEN_HEIGHT * dt);
	}
	if (InputManager::isKey(GLFW_KEY_S))
	{
		this->position = glm::vec2(this->position.x, this->position.y + Game_Parameters::SCREEN_HEIGHT * dt);
	}
	if (InputManager::isKey(GLFW_KEY_A))
	{
		this->position = glm::vec2(this->position.x - Game_Parameters::SCREEN_HEIGHT * dt, this->position.y);
	}
	if (InputManager::isKey(GLFW_KEY_D))
	{
		this->position = glm::vec2(this->position.x + Game_Parameters::SCREEN_HEIGHT * dt, this->position.y);
	}
	if (InputManager::isKeyDown(GLFW_KEY_ESCAPE))
	{
		Game::SetGameState(GameState::MENU);
		start = true;
	}
	if (InputManager::isKeyUp(GLFW_KEY_ESCAPE))
	{
	}
	if (save_button.isMouseDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		SaveMap();
	}
	if (save_button.isMouseUp(GLFW_MOUSE_BUTTON_LEFT))
	{
	}
	if (InputManager::isButton(GLFW_MOUSE_BUTTON_LEFT) && firstSelect)
	{
		if (!buildPanel->isMouseHover(false))
		{
			glm::vec2 wd = Utils::ScreenToWorld(glm::vec2(camera->x, camera->y), glm::vec2(InputManager::mouseX, InputManager::mouseY));
			//Logger::DebugLog("pos: " + std::to_string(wd.x) + " - " + std::to_string(wd.y));
			glm::ivec2 selectedCell = Utils::PositionToCell(wd);
			Logger::DebugLog("pos: " + std::to_string(selectedCell.x) + " - " + std::to_string(selectedCell.y));
			for (auto &tile : tiles)
			{
				if (tile.cell == selectedCell)
				{
					Tile tilee = Tile(Utils::CellToPosition(selectedCell), selectedTile.sprite, glm::vec2(Game_Parameters::SIZE_TILE), selectedTile.getType(), selectedTile.frame);
					Button bt = Button(tilee);
					tile.button = bt;
					if (tile.exist)
					{
						Logger::DebugLog("degistirildi!");
					}
					else
					{
						tile.exist = true;
						Logger::DebugLog("eklendi!");
					}
				}
			}
		}
	}

	if (InputManager::isButtonUp(GLFW_MOUSE_BUTTON_LEFT))
	{
	}
}

void Editor::Render(const float dt)
{
	if (this->dt < 0.5f)
		return;
	camera->setPosition(position);
	camera->update();
	worldRenderer.SetProjection(camera->cameraMatrix);
	squareRenderer.SetProjection(camera->cameraMatrix);

	glm::vec2 mouse = Utils::ScreenToWorld(glm::vec2(camera->x, camera->y), glm::vec2(InputManager::mouseX, InputManager::mouseY));
	glm::ivec2 ms = Utils::PositionToCell(mouse);

	for (auto &tile_1 : tiles)
	{
		if (tile_1.exist)
			tile_1.button.Draw(worldRenderer);

		squareRenderer.world_RenderEmptySquare(Utils::CellToPosition(tile_1.cell), glm::vec2(Game_Parameters::SIZE_TILE), cell_yellow);

		if (ms == tile_1.cell)
		{
			glm::vec2 pos = Utils::CellToPosition(tile_1.cell);
			squareRenderer.world_RenderEmptySquareWithLine(pos, glm::vec2(Game_Parameters::SIZE_TILE), mouse_yellow, 2.0F);
		}
	}

	//ui
	this->controlPanel->Draw(squareRenderer, menuRenderer);
	this->tilePanel->Draw(squareRenderer, menuRenderer);
	this->buildPanel->Draw(squareRenderer, menuRenderer);
	//this->menuRenderer.DrawSprite(Sprite(ResourceManager::GetTexture("gui_icons"), 48, 0, 16, 16), glm::vec2(10), glm::vec2(16.0F));
	save_button.Draw(menuRenderer);
	if (!tilesUI.empty())
	{
		for (auto &tile : tilesUI)
		{
			tile.Draw(menuRenderer);
		}
	}
}

void Editor::SaveMap()
{
	if (!tiles.empty())
	{
		rapidxml::xml_document<> doc;
		rapidxml::xml_node<> *node_map = doc.allocate_node(rapidxml::node_element, "map");

		for (auto &tile : tiles)
		{
			if (tile.exist)
			{
				rapidxml::xml_node<> *node_tile = doc.allocate_node(rapidxml::node_element, "tile");
				char *cellX = doc.allocate_string(std::to_string(tile.cell.x).c_str());
				char *cellY = doc.allocate_string(std::to_string(tile.cell.y).c_str());
				char *frame = doc.allocate_string(std::to_string(tile.button.getTile().frame).c_str());
				char *type = doc.allocate_string(std::to_string((int)tile.button.getTile().getType()).c_str());
				rapidxml::xml_node<> *node_tile_texture = doc.allocate_node(rapidxml::node_element, "tileTexture", frame);
				rapidxml::xml_node<> *node_cellX = doc.allocate_node(rapidxml::node_element, "cellX", cellX);
				rapidxml::xml_node<> *node_cellY = doc.allocate_node(rapidxml::node_element, "cellY", cellY);
				rapidxml::xml_node<> *node_tile_type = doc.allocate_node(rapidxml::node_element, "tileType", type);

				node_tile->append_node(node_tile_texture);
				node_tile->append_node(node_cellX);
				node_tile->append_node(node_cellY);
				node_tile->append_node(node_tile_type);
				node_map->append_node(node_tile);
			}
		}
		rapidxml::xml_node<> *node_info = doc.allocate_node(rapidxml::node_element, "info");
		rapidxml::xml_node<> *node_name = doc.allocate_node(rapidxml::node_element, "name", "de_test1");
		node_info->append_node(node_name);
		doc.append_node(node_map);
		doc.append_node(node_info);
		std::ofstream fileC;
		fileC.open("../resources/levels/one.xml");
		if (!fileC)
		{
			std::string str = "dosya acilamadi: ";
			Logger::DebugLog(str);
			Logger::WriteLog(str);
			exit(EXIT_FAILURE);
		}
		fileC << doc;
		fileC.close();
	}
}
