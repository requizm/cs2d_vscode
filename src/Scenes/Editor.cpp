#include "Editor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
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
	this->controlPanel->setParent(buildPanel.get());

	this->tilePanel = std::make_shared<Panel>(glm::vec2(5.0F, 75.0F), "Tile Panel", glm::vec2(32 * maxCellInColumn, 32 * maxCellInRow), *textRenderer, true, false, 1.0F, glm::vec3(0.21F), 1.0F);
	this->tilePanel->setEnable(true);
	this->tilePanel->setMovable(false);
	this->tilePanel->setScrollable(true);
	this->tilePanel->setOutline(true);
	this->tilePanel->setOutlineColor(glm::vec3(0.47F));
	this->tilePanel->setParent(buildPanel.get());

	Sprite sprite;
	glm::vec2 pos;

	sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 16, 0, 16, 16); //new_sprite
	pos = glm::vec2(0.0F);
	b_new = Button(sprite, pos, glm::vec2(16.0F));
	b_new.setOutline(true);
	b_new.setOutlineColor(glm::vec3(0.45));
	b_new.setMargin(glm::vec2(8, 8));
	b_new.setButtonColor(glm::vec3(0.15F));
	b_new.setMouseClickColor(glm::vec3(0.30F));
	b_new.setMouseHoverColor(glm::vec3(0.30F));
	b_new.setParent(controlPanel.get());

	sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 32, 0, 16, 16); //load_sprite
	pos = glm::vec2(30.0F, 0.0F);
	b_load = Button(sprite, pos, glm::vec2(16.0F));
	b_load.setOutline(true);
	b_load.setOutlineColor(glm::vec3(0.45));
	b_load.setMargin(glm::vec2(8, 8));
	b_load.setButtonColor(glm::vec3(0.15F));
	b_load.setMouseClickColor(glm::vec3(0.30F));
	b_load.setMouseHoverColor(glm::vec3(0.30F));
	b_load.setParent(controlPanel.get());

	sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 48, 0, 16, 16); //save_sprite
	pos = glm::vec2(60.0F, 0.0F);
	b_save = Button(sprite, pos, glm::vec2(16.0F));
	b_save.setOutline(true);
	b_save.setOutlineColor(glm::vec3(0.45));
	b_save.setMargin(glm::vec2(8, 8));
	b_save.setButtonColor(glm::vec3(0.15F));
	b_save.setMouseClickColor(glm::vec3(0.30F));
	b_save.setMouseHoverColor(glm::vec3(0.30F));
	b_save.setParent(controlPanel.get());

	//yeni harita paneli
	this->newPanel = std::make_shared<Panel>(glm::vec2(tilePanel->getSize().x + 20, controlPanel->getSize().y), "New Map", glm::vec2(400, 135), *textRenderer, true, true, 1.0F, glm::vec3(0.21F), 0.8F);
	this->newPanel->setMovable(false);
	this->newPanel->setEnable(false);

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
	b_okey->setOutline(true);
	b_okey->setOutlineColor(glm::vec3(1.0F));
	b_okey->setParent(newPanel.get());

	//harita yukle paneli
	this->loadPanel = std::make_shared<Panel>(glm::vec2(tilePanel->getSize().x + 20, controlPanel->getSize().y), "Load Panel", glm::vec2(400, 200), *textRenderer, true, true, 1.0F, glm::vec3(0.21F), 0.8F);
	this->loadPanel->setMovable(false);
	this->loadPanel->setEnable(false);
	this->load_mapsPanel = std::make_shared<Panel>(glm::vec2(20, 60), "Map Panel", glm::vec2(300, 100), *textRenderer, true, false, 1.0F, glm::vec3(0.21F), 0.6F);
	this->load_mapsPanel->setMovable(false);
	this->load_mapsPanel->setEnable(false);
	this->load_mapsPanel->setScrollable(true);
	this->load_mapsPanel->setOutline(true);
	this->load_mapsPanel->setOutlineColor(glm::vec3(0.47F));
	this->load_mapsPanel->setParent(loadPanel.get());
	this->load_mapsPanel->setParentCenterPos();
	this->t_load = std::make_shared<TextBox>(glm::vec2(20.0F, 170.0F), *textRenderer, glm::vec2(120.0F, 20.0F), true, 1.0F, glm::vec3(0.58F));
	this->t_load->setParent(loadPanel.get());
	this->b_map_load = std::make_shared<Button>("Load", glm::vec2(180.0F, 170.0F), glm::vec2(60.0F, 20.0F), *textRenderer, glm::vec3(0.15F), glm::vec3(0.58F), 1.0F);
	this->b_map_load->setMouseClickColor(glm::vec3(0.30F));
	this->b_map_load->setMouseHoverColor(glm::vec3(0.30F));
	this->b_map_load->setLabelMouseHoverColor(glm::vec3(0.58F));
	this->b_map_load->setLabelClickColor(glm::vec3(1.0F));
	this->b_map_load->setOutline(true);
	this->b_map_load->setOutlineColor(glm::vec3(1.0F));
	this->b_map_load->setParent(loadPanel.get());

	//harita save paneli
	this->savePanel = std::make_shared<Panel>(glm::vec2(tilePanel->getSize().x + 20, controlPanel->getSize().y), "Save Panel", glm::vec2(400, 200), *textRenderer, true, true, 1.0F, glm::vec3(0.21F), 0.8F);
	this->savePanel->setMovable(false);
	this->savePanel->setEnable(false);
	this->save_mapsPanel = std::make_shared<Panel>(glm::vec2(20, 60), "Map Panel", glm::vec2(300, 100), *textRenderer, true, false, 1.0F, glm::vec3(0.21F), 0.6F);
	this->save_mapsPanel->setMovable(false);
	this->save_mapsPanel->setEnable(false);
	this->save_mapsPanel->setScrollable(true);
	this->save_mapsPanel->setOutline(true);
	this->save_mapsPanel->setOutlineColor(glm::vec3(0.47F));
	this->save_mapsPanel->setParent(savePanel.get());
	this->save_mapsPanel->setParentCenterPos();
	this->t_save = std::make_shared<TextBox>(glm::vec2(20.0F, 170.0F), *textRenderer, glm::vec2(120.0F, 20.0F), true, 1.0F, glm::vec3(0.58F));
	this->t_save->setParent(savePanel.get());
	this->b_map_save = std::make_shared<Button>("Save", glm::vec2(180.0F, 170.0F), glm::vec2(60.0F, 20.0F), *textRenderer, glm::vec3(0.15F), glm::vec3(0.58F), 1.0F);
	this->b_map_save->setMouseClickColor(glm::vec3(0.30F));
	this->b_map_save->setMouseHoverColor(glm::vec3(0.30F));
	this->b_map_save->setLabelMouseHoverColor(glm::vec3(0.58F));
	this->b_map_save->setLabelClickColor(glm::vec3(1.0F));
	this->b_map_save->setOutline(true);
	this->b_map_save->setOutlineColor(glm::vec3(1.0F));
	this->b_map_save->setParent(savePanel.get());

	tiles.clear();
	maps.clear();
	mapsUI.clear();
	load_mapsPanel->childs.clear();
	save_mapsPanel->childs.clear();
}

void Editor::OnEnable()
{
	Start();
	currentTileSet = "cs2dnorm";
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
	this->buildPanel->Update(dt);

	this->newPanel->Update(dt);

	this->loadPanel->Update(dt);

	this->savePanel->Update(dt);

	if (!mapsUI.empty())
	{
		for (std::vector<int>::size_type i = 0; i != mapsUI.size(); i++)
		{
			mapsUI[i]->Update(dt);
		}
	}

	if (this->tilePanel->isScrollable() && InputManager::scrollYPressed)
	{
		if (!tilesUI.empty() && !loadPanel->isEnable())
		{
			bool check_1 = tilesUI.at(0)->getLocalPosition().y == 0 && InputManager::scroll.y > 0;
			bool check_2 = tilesUI.at(tileCount - 1)->getLocalPosition().y == maxCellInRow * 32 && InputManager::scroll.y < 0;

			if (!check_1 && !check_2)
			{
				for (auto &tile : tilesUI)
				{
					tile->setPosition(tile->getLocalPosition().x, tile->getLocalPosition().y + InputManager::scroll.y * 32);
				}
			}
		}

		if (!mapsUI.empty())
		{
			bool check_1 = mapsUI.at(0)->getLocalPosition().y == 0 && InputManager::scroll.y > 0;
			bool check_2 = mapsUI.at(mapsUI.size() - 1)->getLocalPosition().y == load_mapsPanel->getSize().y && InputManager::scroll.y < 0;

			if (!check_1 && !check_2)
			{
				for (auto &tile : mapsUI)
				{
					tile->setPosition(tile->getLocalPosition().x, tile->getLocalPosition().y + InputManager::scroll.y * 20);
				}
			}
		}

		InputManager::scrollYPressed = false;
	}
}

void Editor::ProcessInput(const float dt)
{
	this->buildPanel->ProcessInput();
	this->newPanel->ProcessInput();

	this->loadPanel->ProcessInput();
	this->savePanel->ProcessInput();
	if (!mapsUI.empty())
	{
		for (std::vector<int>::size_type i = 0; i != mapsUI.size(); i++)
		{
			mapsUI[i]->ProcessInput();
		}
	}

	if (!tilesUI.empty())
	{
		for (auto &tile : tilesUI)
		{
			if (tile->isRenderable())
			{
				tile->ProcessInput();
				if (tile->isMouseDown())
				{
					selectedTile = *(tile->getTile());
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
			t = nullptr;
		}
	}
	if (t_load->editMode)
	{
		passMovement = true;
	}

	if (t_save->editMode)
	{
		passMovement = true;
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
		B_SaveMap();
	}

	if (b_map_save->isMouseDown())
	{
		SaveMap();
	}

	if (b_load.isMouseDown())
	{
		B_LoadMap();
	}

	if (b_map_load->isMouseDown())
	{
		LoadMap(t_load->getText());
	}

	for (std::vector<int>::size_type i = 0; i != mapsUI.size(); i++)
	{
		if (mapsUI[i]->isMouseDown() && mapsUI[i]->isRenderable())
		{
			if (selectedMap != -1)
			{
				mapsUI.at(selectedMap)->setButtonColor(glm::vec3(0.21F));
				mapsUI.at(selectedMap)->setMouseHoverColor(glm::vec3(0.25F));
				mapsUI.at(selectedMap)->setLabelColor(glm::vec3(0.58F));
			}
			mapsUI[i]->setButtonColor(glm::vec3(0.35F));
			mapsUI[i]->setMouseHoverColor(glm::vec3(0.35F));
			mapsUI[i]->setLabelColor(glm::vec3(1.0F));
			t_load->setText(mapsUI[i]->getText());
			t_save->setText(mapsUI[i]->getText());
			selectedMap = i;
			break;
		}
	}

	if (firstSelect && !buildPanel->isPressed && !newPanel->isPressed && !loadPanel->isPressed && !savePanel->isPressed &&
		!buildPanel->isMouseHover(false) && !newPanel->isMouseHover(false) && !loadPanel->isMouseHover(false) && !savePanel->isMouseHover(false))
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
					if (!(selectedTile.frame == tile.button.getTile()->frame))
					{
						tile.button = bt;
						/*if (!tile.exist)
						{
							tile.exist = true;
						}*/
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
		tile_1.button.Draw(worldRenderer, squareRenderer);

		squareRenderer.world_RenderEmptySquare(Utils::CellToPosition(tile_1.cell), glm::vec2(Game_Parameters::SIZE_TILE), cell_yellow);

		if (ms == tile_1.cell && !newPanel->isMouseHover(false) && !buildPanel->isMouseHover(false) && !loadPanel->isMouseHover(false) && !savePanel->isMouseHover(false))
		{
			glm::vec2 pos = Utils::CellToPosition(tile_1.cell);
			squareRenderer.world_RenderEmptySquareWithLine(pos, glm::vec2(Game_Parameters::SIZE_TILE), mouse_yellow, 2.0F);
		}
	}

	//ui
	this->buildPanel->Draw(menuRenderer, squareRenderer);

	this->newPanel->Draw(menuRenderer, squareRenderer);

	this->loadPanel->Draw(menuRenderer, squareRenderer);

	this->savePanel->Draw(menuRenderer, squareRenderer);
	if (!mapsUI.empty())
	{
		for (std::vector<int>::size_type i = 0; i != mapsUI.size(); i++)
		{
			mapsUI[i]->Draw(menuRenderer, squareRenderer);
		}
	}

	if (!tilesUI.empty())
	{
		for (auto &tile : tilesUI)
		{
			if (firstSelect && selectedTile.GetID() == tile->getTile()->GetID())
			{
				tile->Draw(menuRenderer, squareRenderer, 0.3F, this->dt, true);
			}
			else if (tile->isMouseHover())
			{
				tile->Draw(menuRenderer, squareRenderer, 0.3F, this->dt, false);
			}
			else
			{
				tile->Draw(menuRenderer, squareRenderer);
			}
		}
	}
}

void Editor::SaveMap()
{
	if (!tiles.empty() && !t_save->getText().empty())
	{
		rapidxml::xml_document<> doc;
		rapidxml::xml_node<> *node_map = doc.allocate_node(rapidxml::node_element, "map");

		for (auto &tile : tiles)
		{
			rapidxml::xml_node<> *node_tile = doc.allocate_node(rapidxml::node_element, "tile");
			char *cellX = doc.allocate_string(std::to_string(tile.cell.x).c_str());
			char *cellY = doc.allocate_string(std::to_string(tile.cell.y).c_str());
			char *frame = doc.allocate_string(std::to_string(tile.button.getTile()->frame).c_str());
			char *type = doc.allocate_string(std::to_string((int)tile.button.getTile()->getType()).c_str());
			rapidxml::xml_node<> *node_tile_texture;
			/*if (!tile.exist)
			{
				node_tile_texture = doc.allocate_node(rapidxml::node_element, "tileTexture", "0");
			}*/
			//else
			//{
			node_tile_texture = doc.allocate_node(rapidxml::node_element, "tileTexture", frame);
			//}

			rapidxml::xml_node<> *node_cellX = doc.allocate_node(rapidxml::node_element, "cellX", cellX);
			rapidxml::xml_node<> *node_cellY = doc.allocate_node(rapidxml::node_element, "cellY", cellY);
			rapidxml::xml_node<> *node_tile_type = doc.allocate_node(rapidxml::node_element, "tileType", type);

			node_tile->append_node(node_tile_texture);
			node_tile->append_node(node_cellX);
			node_tile->append_node(node_cellY);
			node_tile->append_node(node_tile_type);
			node_map->append_node(node_tile);

			delete cellX, cellY, frame, type;
		}
		char *limitX = doc.allocate_string(std::to_string(mapLimit.x).c_str());
		char *limitY = doc.allocate_string(std::to_string(mapLimit.y).c_str());
		char *tile = doc.allocate_string(currentTileSet.c_str());
		char *name = doc.allocate_string(t_save->getText().c_str());
		rapidxml::xml_node<> *node_info = doc.allocate_node(rapidxml::node_element, "info");
		rapidxml::xml_node<> *node_name = doc.allocate_node(rapidxml::node_element, "name", name);
		rapidxml::xml_node<> *node_tileset = doc.allocate_node(rapidxml::node_element, "tileSet", tile);
		rapidxml::xml_node<> *node_maplimitx = doc.allocate_node(rapidxml::node_element, "mapLimitX", limitX);
		rapidxml::xml_node<> *node_maplimity = doc.allocate_node(rapidxml::node_element, "mapLimitY", limitY);
		node_info->append_node(node_name);
		node_info->append_node(node_tileset);
		node_info->append_node(node_maplimitx);
		node_info->append_node(node_maplimity);
		doc.append_node(node_map);
		doc.append_node(node_info);
		std::ofstream fileC;
		std::string a("../resources/levels/");
		a += t_save->getText();
		a += ".xml";
		fileC.open(a.c_str());
		if (!fileC)
		{
			std::string str = "dosya acilamadi: ";
			Logger::DebugLog(str);
			Logger::WriteLog(str);
			exit(EXIT_FAILURE);
		}
		fileC << doc;
		fileC.close();
		delete limitX, limitY, name, tile;
		delete node_map;
		this->savePanel->setEnable(false);
	}
}

void Editor::NewMap(std::string tileSet, glm::vec2 mapSize)
{
	this->dt = 0.0F;
	this->position = glm::vec2(0.0F - buildPanel->getSize().x, 0.0F);
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
		Button *button = new Button(tile);
		button->independent = true;
		button->setParent(tilePanel.get(), true);
		tilesUI.push_back(std::make_shared<Button>(*button));
	}

	for (int i = 0; i < mapLimit.x; i++)
	{
		for (int j = 0; j < mapLimit.y; j++)
		{
			ButtonTile t = ButtonTile(glm::ivec2(i, j));
			t.button.getTile()->frame = 0;
			t.button.getTile()->setType(TileTypes::FLOOR);
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
	currentTileSet = tileSet;
	Start();
	NewMap(tileSet, glm::vec2(isizeX, isizeY));
	return true;
}

void Editor::LoadMap(std::string mapName)
{
	this->dt = 0.0F;
	this->position = glm::vec2(0.0F - buildPanel->getSize().x, 0.0F);
	tiles.clear();
	maps.clear();
	mapsUI.clear();
	load_mapsPanel->childs.clear();
	firstSelect = false;
	InputManager::scroll.y = 0.0F;
	this->loadPanel->setEnable(false);

	mapName = "../resources/levels/" + mapName + ".xml";
	std::string codeString;
	std::ifstream fileC(mapName.c_str());
	if (!fileC)
	{
		std::string str = "dosya acilamadi: ";
		str += mapName.c_str();
		Logger::DebugLog(str);
		Logger::WriteLog(str);
		exit(EXIT_FAILURE);
	}

	std::stringstream fileStream;
	fileStream << fileC.rdbuf();
	fileC.close();
	codeString = fileStream.str();
	rapidxml::xml_document<> doc;
	char *codeChar = new char[codeString.length() + 1];
	strcpy(codeChar, codeString.c_str());
	doc.parse<0>(codeChar);
	this->t_save->setText(doc.first_node("info")->first_node("name")->value());
	this->currentTileSet = doc.first_node("info")->first_node("tileSet")->value();
	char *mapx = doc.first_node("info")->first_node("mapLimitX")->value();
	char *mapy = doc.first_node("info")->first_node("mapLimitY")->value();
	this->mapLimit.x = atoi(mapx);
	this->mapLimit.y = atoi(mapy);
	rapidxml::xml_node<> *node = doc.first_node("map");
	//std::cout << node->first_node("tile")->first_node("cellX")->next_sibling()->name() << std::endl;
	int i = 0;
	for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
	{
		//std::cout << child->first_node("cellY")->value() << std::endl;
		//tile.SetSize(glm::vec2(Game::Width / 26.5, Game::Width / 26.5));
		char *x = child->first_node("cellX")->value();
		char *y = child->first_node("cellY")->value();
		char *tIndex = child->first_node("tileTexture")->value();
		char *tType = child->first_node("tileType")->value();
		int cellX = atoi(x);
		int cellY = atoi(y);
		int textureIndex = atoi(tIndex);
		int tileType = atoi(tType);
		const glm::vec2 pos(Game_Parameters::SIZE_TILE * cellX, Game_Parameters::SIZE_TILE * cellY);
		const glm::vec2 size(glm::vec2(Game_Parameters::SIZE_TILE, Game_Parameters::SIZE_TILE));
		const int xoffset = textureIndex % (ResourceManager::GetTexture(currentTileSet).Width / 32);
		const int yoffset = textureIndex / (ResourceManager::GetTexture(currentTileSet).Width / 32);
		const Sprite sprite = Sprite(ResourceManager::GetTexture(currentTileSet), (xoffset)*32, yoffset * 32, 32, 32);
		Tile tile = Tile(pos, sprite, size, TileTypes(tileType), textureIndex);
		Button b = Button(tile);
		ButtonTile t = ButtonTile(b, glm::ivec2(cellX, cellY));
		tiles.push_back(t);

		delete x, y, tIndex, tType;
	}

	delete codeChar, mapx, mapy;
}

void Editor::B_LoadMap()
{
	maps.clear();
	mapsUI.clear();
	load_mapsPanel->childs.clear();
	selectedMap = -1;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("../resources/levels")) != NULL)
	{
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_name[0] == '.')
				continue;
			std::string mapName(ent->d_name);
			if (mapName.substr(mapName.size() - 4) == ".xml")
			{
				std::string a = mapName.substr(0, mapName.size() - 4);
				maps.push_back(a);
			}
		}
		closedir(dir);
	}
	else
	{
		perror("could not open directory");
	}

	for (std::vector<int>::size_type i = 0; i != maps.size(); i++)
	{
		Button *bt = new Button(maps[i], glm::vec2(0.0F, static_cast<float>(i * 20)), glm::vec2(load_mapsPanel->getSize().x, 20.0F), *textRenderer, glm::vec3(0.21F), glm::vec3(0.58F), 1.0F);
		bt->setMouseClickColor(glm::vec3(0.35F));
		bt->setMouseHoverColor(glm::vec3(0.25F));
		bt->setLabelMouseHoverColor(glm::vec3(1.0F));
		bt->setLabelClickColor(glm::vec3(1.0F));
		bt->setOutline(false);
		bt->setParent(load_mapsPanel.get());
		bt->independent = true;
		bt->center = false;
		mapsUI.push_back(std::make_shared<Button>(*bt));
	}
	this->loadPanel->setEnable(true);
}

void Editor::B_SaveMap()
{
	maps.clear();
	mapsUI.clear();
	save_mapsPanel->childs.clear();
	selectedMap = -1;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir("../resources/levels")) != NULL)
	{
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL)
		{
			if (ent->d_name[0] == '.')
				continue;
			std::string mapName(ent->d_name);
			if (mapName.substr(mapName.size() - 4) == ".xml")
			{
				std::string a = mapName.substr(0, mapName.size() - 4);
				maps.push_back(a);
			}
		}
		closedir(dir);
	}
	else
	{
		perror("could not open directory");
	}

	for (std::vector<int>::size_type i = 0; i != maps.size(); i++)
	{
		Button *bt = new Button(maps[i], glm::vec2(0.0F, static_cast<float>(i * 20)), glm::vec2(save_mapsPanel->getSize().x, 20.0F), *textRenderer, glm::vec3(0.21F), glm::vec3(0.58F), 1.0F);
		bt->setMouseClickColor(glm::vec3(0.35F));
		bt->setMouseHoverColor(glm::vec3(0.25F));
		bt->setLabelMouseHoverColor(glm::vec3(1.0F));
		bt->setLabelClickColor(glm::vec3(1.0F));
		bt->setOutline(false);
		bt->setParent(save_mapsPanel.get());
		bt->independent = true;
		bt->center = false;
		mapsUI.push_back(std::make_shared<Button>(*bt));
	}
	this->savePanel->setEnable(true);
}
