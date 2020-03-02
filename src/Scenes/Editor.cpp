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
	this->tileCount = 0;
	this->maxCellInColumn = 0;
	this->maxCellInRow = 0;
	this->position = glm::vec2(0.0F);
	this->firstSelect = false;
	this->dt = 0.0F;
	this->mapLimit = glm::ivec2(0);
	this->texture = glm::vec2(0.0F);
}

Editor::Editor(const SpriteRenderer &menuRenderer, const SpriteRenderer &worldRenderer)
{
	this->menuRenderer = menuRenderer;
	this->worldRenderer = worldRenderer;

	this->tileCount = 0;
	this->maxCellInColumn = 0;
	this->maxCellInRow = 0;
	this->position = glm::vec2(0.0F);
	this->firstSelect = false;
	this->dt = 0.0F;
	this->mapLimit = glm::ivec2(0);
	this->texture = glm::vec2(0.0F);

	//this->SetEnable(true);
}

Editor::~Editor() = default;

void Editor::Start()
{
	this->textRenderer = std::make_shared<TextRenderer>(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	this->textRenderer->Load("../resources/fonts/liberationsans.ttf", 16);
	this->squareRenderer = SquareRenderer(true);
	this->camera = std::make_shared<Camera>(static_cast<int>(Game_Parameters::SCREEN_WIDTH), static_cast<int>(Game_Parameters::SCREEN_HEIGHT));
	this->mouse_yellow = glm::vec3(0.73F, 0.73F, 0.0F);
	this->cell_yellow = glm::vec3(0.15F, 0.15F, 0.0F);
	this->maxCellInColumn = 5;
	this->maxCellInRow = (Game_Parameters::SCREEN_HEIGHT - (32 * 4) - 22) / 32 + 1;

	this->buildPanel = std::make_shared<Panel>(glm::vec2(0.0F, 0.0F), "Build Panel", glm::vec2(32 * maxCellInColumn + (5 * 2), Game_Parameters::SCREEN_HEIGHT), *textRenderer, true, false, 1.0F, glm::vec3(0.21F), 1.0F);
	this->buildPanel->setMovable(false);
	this->buildPanel->setEnable(true);

	this->controlPanel = std::make_shared<Panel>(glm::vec2(5.0F, 5.0F), "Control Panel", glm::vec2(32 * maxCellInColumn, 32 * 2 - 11), *textRenderer, true, false, 1.0F, glm::vec3(0.21F), 1.0F);
	this->controlPanel->setMovable(false);
	this->controlPanel->setEnable(true);

	this->tilePanel = std::make_shared<Panel>(glm::vec2(5.0F, 75.0F), "", glm::vec2(32 * maxCellInColumn, 32 * maxCellInRow), *textRenderer, true, false, 1.0F, glm::vec3(0.21F), 1.0F);
	this->tilePanel->setEnable(true);
	this->tilePanel->setMovable(false);
	this->tilePanel->setScrollable(true);
	this->tilePanel->setOutline(true);
	this->tilePanel->setOutlineColor(glm::vec3(0.47F));

	this->newPanel = std::make_shared<Panel>(glm::vec2(tilePanel->getSize().x + 20, controlPanel->getSize().y), "New Map", glm::vec2(400, 135), *textRenderer, true, true, 1.0F, glm::vec3(0.21F));
	this->newPanel->setMovable(false);
	this->newPanel->setEnable(false);

	Sprite sprite;
	glm::vec2 pos;

	sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 16, 0, 16, 16); //new_sprite
	pos = this->controlPanel->getPosition();
	b_new = Button(sprite, pos, glm::vec2(16.0F));
	b_new.setOutline(true);
	b_new.setOutlineColor(glm::vec3(0.45));
	b_new.setMargin(glm::vec2(8, 8));

	sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 32, 0, 16, 16); //load_sprite
	pos = glm::vec2(controlPanel->getPosition().x + 30, controlPanel->getPosition().y);
	b_load = Button(sprite, pos, glm::vec2(16.0F));
	b_load.setOutline(true);
	b_load.setOutlineColor(glm::vec3(0.45));
	b_load.setMargin(glm::vec2(8, 8));

	sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 48, 0, 16, 16); //save_sprite
	pos = glm::vec2(controlPanel->getPosition().x + 60, controlPanel->getPosition().y);
	b_save = Button(sprite, pos, glm::vec2(16.0F));
	b_save.setOutline(true);
	b_save.setOutlineColor(glm::vec3(0.45));
	b_save.setMargin(glm::vec2(8, 8));

	t_mapSizeX = std::make_shared<TextBox>(glm::vec2(180.0F, 40.0F), *textRenderer, glm::vec2(60.0F, 20.0F), true, 1.0F, glm::vec3(0.58F));
	t_mapSizeX->setParent(newPanel.get());
	t_mapSizeY = std::make_shared<TextBox>(glm::vec2(250.0F, 40.0F), *textRenderer, glm::vec2(60.0F, 20.0F), true, 1.0F, glm::vec3(0.58F));
	t_mapSizeY->setParent(newPanel.get());
	t_tile = std::make_shared<TextBox>(glm::vec2(180.0F, 65.0F), *textRenderer, glm::vec2(120.0F, 20.0F), true, 1.0F, glm::vec3(0.58F));
	t_tile->setParent(newPanel.get());

	l_mapSize = std::make_shared<Label>("Map Size", glm::vec2(40.0F, 40.0F), *textRenderer, 1.0F, glm::vec3(0.58F));
	l_mapSize->setParent(newPanel.get());
	l_mapSize->setMouseEvent(false);
	l_x = std::make_shared<Label>("x", glm::vec2(240.0F, 40.0F), *textRenderer, 1.0F, glm::vec3(0.58F));
	l_x->setParent(newPanel.get());
	l_x->setMouseEvent(false);
	l_tile = std::make_shared<Label>("Tileset", glm::vec2(40.0F, 65.0F), *textRenderer, 1.0F, glm::vec3(0.58F));
	l_tile->setParent(newPanel.get());
	l_tile->setMouseEvent(false);
	b_okey = std::make_shared<Button>("Okay", glm::vec2(50.0F, 105.0F), glm::vec2(60.0F, 20.0F), *textRenderer, glm::vec3(0.15F), glm::vec3(0.58F), 1.0F);
	b_okey->setMouseClickColor(glm::vec3(0.30F));
	b_okey->setMouseHoverColor(glm::vec3(0.30F));
	b_okey->setLabelMouseHoverColor(glm::vec3(0.58F));
	b_okey->setLabelClickColor(glm::vec3(1.0F));
	b_okey->setParent(newPanel.get());
}

void Editor::OnEnable()
{
	Start();
	NewMap("cs2dnorm", glm::vec2(50));
}

void Editor::OnDisable()
{
}

void Editor::SetEnable(const bool value)
{
	if (this->enable == value)
		return;
	this->enable = value;
	if (this->enable)
		OnEnable();
	else
		OnDisable();
}

void Editor::Update(const float dt)
{
	this->dt += dt;

	this->controlPanel->Update(dt);
	this->buildPanel->Update(dt);
	this->tilePanel->Update(dt);
	this->b_save.Update(dt);
	this->b_new.Update(dt);
	this->b_load.Update(dt);
	this->t_tile->Update(dt);
	this->t_mapSizeX->Update(dt);
	this->t_mapSizeY->Update(dt);
	this->newPanel->Update(dt);
	this->b_okey->Update(dt);

	if (this->tilePanel->isScrollable() && InputManager::scrollYPressed)
	{
		if (!tilesUI.empty())
		{
			bool check_1 = tilesUI.at(0).getLocalPosition().y == 0 && InputManager::scroll.y > 0;
			bool check_2 = tilesUI.at(tileCount - 1).getLocalPosition().y == maxCellInRow * 32 && InputManager::scroll.y < 0;

			if (!check_1 && !check_2)
			{
				for (auto &tile : tilesUI)
				{
					tile.setPosition(tile.getLocalPosition().x, tile.getLocalPosition().y + InputManager::scroll.y * 32);
				}
			}
		}
		InputManager::scrollYPressed = false;
	}
}

void Editor::ProcessInput(const float dt)
{
	this->controlPanel->ProcessInput();
	this->buildPanel->ProcessInput();
	this->tilePanel->ProcessInput();
	this->b_save.ProcessInput();
	this->b_new.ProcessInput();
	this->b_load.ProcessInput();
	this->newPanel->ProcessInput();
	this->b_okey->ProcessInput();

	if (!tilesUI.empty())
	{
		for (auto &tile : tilesUI)
		{
			if (tile.isRenderable())
			{
				tile.ProcessInput();
				if (tile.isMouseDown())
				{
					selectedTile = tile.getTile();
					firstSelect = true;
				}
			}
		}
	}

	bool passMovement = false;
	for (std::vector<int>::size_type i = 0; i != newPanel->childs.size(); i++)
	{
		if (newPanel->childs[i]->GetObjectTypeString() == "TextBox")
		{
			TextBox *t = dynamic_cast<TextBox *>(newPanel->childs[i]);
			if (t->editMode)
			{
				passMovement = true;
				break;
			}
		}
	}

	if (!passMovement)
	{
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
	}

	if (InputManager::isKeyDown(GLFW_KEY_ESCAPE))
	{
		Game::SetGameState(GameState::MENU);
	}

	if (b_okey->isMouseDown())
	{
		B_NewMap();
	}

	if (b_new.isMouseDown())
	{
		this->newPanel->setEnable(true);
	}

	if (b_save.isMouseDown())
	{
		SaveMap();
	}

	if (firstSelect && !buildPanel->isPressed && !newPanel->isPressed && !buildPanel->isMouseHover(false) && !newPanel->isMouseHover(false))
	{
		if (InputManager::isButton(GLFW_MOUSE_BUTTON_LEFT))
		{
			glm::vec2 wd = Utils::ScreenToWorld(camera->view, InputManager::mousePos);
			//Logger::DebugLog("pos: " + std::to_string(wd.x) + " - " + std::to_string(wd.y));
			glm::ivec2 selectedCell = Utils::PositionToCell(wd);
			//Logger::DebugLog("pos: " + std::to_string(selectedCell.x) + " - " + std::to_string(selectedCell.y));
			for (auto &tile : tiles)
			{
				if (tile.cell == selectedCell)
				{
					Tile tilee = Tile(Utils::CellToPosition(selectedCell), selectedTile.sprite, glm::vec2(Game_Parameters::SIZE_TILE), selectedTile.getType(), selectedTile.frame);
					Button bt = Button(tilee);
					if (!(selectedTile.frame == tile.button.getTile().frame || (!tile.exist && selectedTile.frame == 0)))
					{
						tile.button = bt;
						if (!tile.exist)
						{
							tile.exist = true;
						}
					}
				}
			}
		}
	}
}

void Editor::Render(const float dt)
{
	camera->setPosition(position);

	worldRenderer.SetProjection(camera->cameraMatrix);
	squareRenderer.SetProjection(camera->cameraMatrix);

	glm::vec2 mouse = Utils::ScreenToWorld(camera->view, InputManager::mousePos);
	glm::ivec2 ms = Utils::PositionToCell(mouse);

	for (auto &tile_1 : tiles)
	{
		if (tile_1.exist)
			tile_1.button.Draw(worldRenderer, squareRenderer);

		squareRenderer.world_RenderEmptySquare(Utils::CellToPosition(tile_1.cell), glm::vec2(Game_Parameters::SIZE_TILE), cell_yellow);

		if (ms == tile_1.cell && !newPanel->isMouseHover(false) && !buildPanel->isMouseHover(false))
		{
			glm::vec2 pos = Utils::CellToPosition(tile_1.cell);
			squareRenderer.world_RenderEmptySquareWithLine(pos, glm::vec2(Game_Parameters::SIZE_TILE), mouse_yellow, 2.0F);
		}
	}

	//ui

	this->controlPanel->Draw(squareRenderer, menuRenderer);
	this->buildPanel->Draw(squareRenderer, menuRenderer);
	this->tilePanel->Draw(squareRenderer, menuRenderer);
	this->b_save.Draw(menuRenderer, squareRenderer);
	this->b_new.Draw(menuRenderer, squareRenderer);
	this->b_load.Draw(menuRenderer, squareRenderer);

	this->newPanel->Draw(squareRenderer, menuRenderer);
	this->t_tile->Draw(squareRenderer, menuRenderer);
	this->t_mapSizeX->Draw(squareRenderer, menuRenderer);
	this->t_mapSizeY->Draw(squareRenderer, menuRenderer);
	this->l_tile->Draw();
	this->l_mapSize->Draw();
	this->l_x->Draw();
	this->b_okey->Draw(menuRenderer, squareRenderer);

	if (!tilesUI.empty())
	{
		for (auto &tile : tilesUI)
		{
			if (firstSelect && selectedTile.frame == tile.getTile().frame)
			{
				tile.Draw(menuRenderer, squareRenderer, 0.3F, this->dt, true);
			}
			else if (tile.isMouseHover())
			{
				tile.Draw(menuRenderer, squareRenderer, 0.3F, this->dt, false);
			}
			else
			{
				tile.Draw(menuRenderer, squareRenderer);
			}
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

void Editor::NewMap(std::string tileSet, glm::vec2 mapSize)
{
	this->dt = 0.0F;
	position = glm::vec2(0.0F);
	tiles.clear();
	tilesUI.clear();

	firstSelect = false;
	mapLimit = mapSize;

	texture.x = ResourceManager::GetTexture(tileSet).Width / 32;
	texture.y = ResourceManager::GetTexture(tileSet).Height / 32;
	tileCount = texture.x * texture.y;

	InputManager::scroll.y = 0.0F;

	int curIndex = 0;
	for (int i = 0; i < tileCount; i++)
	{
		const int xPos = 32 * (curIndex % maxCellInColumn);
		const int yPos = 32 * (curIndex / maxCellInColumn);
		const glm::vec2 pos(xPos, yPos);
		const glm::vec2 size(glm::vec2(32, 32));
		const int xoffset = curIndex % (ResourceManager::GetTexture(tileSet).Width / 32);
		const int yoffset = curIndex / (ResourceManager::GetTexture(tileSet).Width / 32);
		const Sprite sprite = Sprite(ResourceManager::GetTexture(tileSet), (xoffset)*32, yoffset * 32, 32, 32);
		Tile tile = Tile(pos, sprite, size, TileTypes::FLOOR, curIndex++);
		Button button = Button(tile);
		button.setParent(tilePanel.get(), true);
		tilesUI.push_back(button);
	}

	for (int i = 0; i < mapLimit.x; i++)
	{
		for (int j = 0; j < mapLimit.y; j++)
		{
			ButtonTile t = ButtonTile(glm::ivec2(i, j));
			tiles.push_back(t);
		}
	}
}

bool Editor::B_NewMap()
{
	std::string sizeX = t_mapSizeX->getText();
	std::string sizeY = t_mapSizeY->getText();
	std::string tileSet = t_tile->getText();
	if (sizeX.empty() || sizeY.empty() || tileSet.empty())
	{
		Logger::DebugLog("BOS");
		return false;
	}
	if (ResourceManager::GetTexture(tileSet).Width == 0)
	{
		Logger::DebugLog("BOYLE BIR TEXTURE YOK");
		return false;
	}
	if (!Utils::TryStringToInt(sizeX.c_str()) || !Utils::TryStringToInt(sizeY.c_str()))
	{
		Logger::DebugLog("BUNLAR SAYI DEGIL");
		return false;
	}

	int isizeX = Utils::StringToInt(sizeX.c_str());
	int isizeY = Utils::StringToInt(sizeY.c_str());

	if (isizeX <= 0 || isizeY <= 0)
	{
		Logger::DebugLog("BUNLAR NEGATIF");
		return false;
	}

	Start();
	NewMap(tileSet, glm::vec2(isizeX, isizeY));
	return true;
}
