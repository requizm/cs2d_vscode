#include "Editor.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "../../Others/Game_Parameters.hpp"
#include "../../Others/Utils.hpp"
#include "../../Game.hpp"

Editor::Editor()
{
	this->tileCount = 0;
	this->maxCellInColumn = 0;
	this->maxCellInRow = 0;
	this->position = Vector2(0.0F);
	this->firstSelect = false;
	this->time = 0.0F;
	this->mapLimit = Vector2<int>(0);
	this->texture = Vector2<int>(0);
	this->selectedMode = SelectedMode::TILE_MOD;
}

Editor::Editor(const SpriteRenderer &menuRenderer, const SpriteRenderer &worldRenderer)
{
	this->menuRenderer = menuRenderer;
	this->worldRenderer = worldRenderer;

	this->tileCount = 0;
	this->maxCellInColumn = 0;
	this->maxCellInRow = 0;
	this->position = Vector2(0.0F);
	this->firstSelect = false;
	this->time = 0.0F;
	this->mapLimit = Vector2<int>(0);
	this->texture = Vector2<int>(0);
	this->selectedMode = SelectedMode::TILE_MOD;

	//this->SetEnable(true);
}

Editor::~Editor()
{
	for (std::vector<int>::size_type i = 0; i != env_items.size(); i++)
	{
		delete env_items[i];
	}
}

void Editor::Initialize(const SpriteRenderer &menuRenderer, const SpriteRenderer &worldRenderer)
{
	this->menuRenderer = menuRenderer;
	this->worldRenderer = worldRenderer;

	this->tileCount = 0;
	this->maxCellInColumn = 0;
	this->maxCellInRow = 0;
	this->position = Vector2(0.0F);
	this->firstSelect = false;
	this->time = 0.0F;
	this->mapLimit = Vector2<int>(0);
	this->texture = Vector2<int>(0);
	this->selectedMode = SelectedMode::TILE_MOD;
}

void Editor::Start()
{
	this->textRenderer = std::make_shared<TextRenderer>(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	this->textRenderer->Load("../resources/fonts/liberationsans.ttf", 16);
	this->squareRenderer = SquareRenderer(true);
	this->camera = std::make_shared<Camera>(static_cast<int>(Game_Parameters::SCREEN_WIDTH), static_cast<int>(Game_Parameters::SCREEN_HEIGHT));
	this->mouse_yellow = Vector3<float>(0.73F, 0.73F, 0.0F);
	this->cell_yellow = Vector3<float>(0.15F, 0.15F, 0.0F);
	this->maxCellInColumn = 5;
	this->maxCellInRow = (Game_Parameters::SCREEN_HEIGHT - (32 * 4) - 22) / 32 + 1;

	this->buildPanel = std::make_shared<Panel>(Vector2<float>(0.0F, 0.0F), "Build Panel", Vector2<float>(32 * maxCellInColumn + (5 * 2), Game_Parameters::SCREEN_HEIGHT), *textRenderer, true, false, 1.0F, Vector3<float>(0.21F), 1.0F);
	this->buildPanel->setMovable(false);
	this->buildPanel->setEnable(true);

	this->controlPanel = std::make_shared<Panel>(Vector2<float>(5.0F, 5.0F), "Control Panel", Vector2<float>(32 * maxCellInColumn, 32 * 2 - 11), *textRenderer, true, false, 1.0F, Vector3<float>(0.21F), 1.0F);
	this->controlPanel->setMovable(false);
	this->controlPanel->setEnable(true);
	this->controlPanel->setParent(buildPanel.get());

	this->tilePanel = std::make_shared<Panel>(Vector2<float>(5.0F, 75.0F), "Tile Panel", Vector2<float>(32 * maxCellInColumn, 32 * maxCellInRow), *textRenderer, true, false, 1.0F, Vector3<float>(0.21F), 1.0F);
	this->tilePanel->setEnable(true);
	this->tilePanel->setMovable(false);
	this->tilePanel->setScrollable(true);
	this->tilePanel->setOutline(true);
	this->tilePanel->setOutlineColor(Vector3<float>(0.47F));
	this->tilePanel->setParent(buildPanel.get());

	this->objectPanel = std::make_shared<Panel>(Vector2<float>(5.0F, 75.0F), "Object Panel", Vector2<float>(32 * maxCellInColumn, 32 * maxCellInRow), *textRenderer, true, false, 1.0F, Vector3<float>(0.21F), 1.0F);
	this->objectPanel->setEnable(false);
	this->objectPanel->setMovable(false);
	this->objectPanel->setScrollable(true);
	this->objectPanel->setOutline(true);
	this->objectPanel->setOutlineColor(Vector3<float>(0.47F));
	this->objectPanel->setParent(buildPanel.get());

	objects_ui = std::make_unique<ListItem>(this->objectPanel.get());
	objects_ui->Clear();
	std::string a = "Env_Item";
	objects_ui->AddItem(a);

	Sprite sprite;
	Vector2<float> pos;

	sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 16, 0, 16, 16); //new_sprite
	pos = Vector2<float>(0.0F);
	b_new = Button(sprite, pos, Vector2<float>(16.0F));
	b_new.setOutline(true);
	b_new.setOutlineColor(Vector3<float>(0.45));
	b_new.setMargin(Vector2<float>(8, 8));
	b_new.setButtonColor(Vector3<float>(0.15F));
	b_new.setMouseClickColor(Vector3<float>(0.30F));
	b_new.setMouseHoverColor(Vector3<float>(0.30F));
	b_new.setParent(controlPanel.get());

	sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 32, 0, 16, 16); //load_sprite
	pos = Vector2<float>(30.0F, 0.0F);
	b_load = Button(sprite, pos, Vector2<float>(16.0F));
	b_load.setOutline(true);
	b_load.setOutlineColor(Vector3<float>(0.45));
	b_load.setMargin(Vector2<float>(8, 8));
	b_load.setButtonColor(Vector3<float>(0.15F));
	b_load.setMouseClickColor(Vector3<float>(0.30F));
	b_load.setMouseHoverColor(Vector3<float>(0.30F));
	b_load.setParent(controlPanel.get());

	sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 48, 0, 16, 16); //save_sprite
	pos = Vector2<float>(60.0F, 0.0F);
	b_save = Button(sprite, pos, Vector2<float>(16.0F));
	b_save.setOutline(true);
	b_save.setOutlineColor(Vector3<float>(0.45));
	b_save.setMargin(Vector2<float>(8, 8));
	b_save.setButtonColor(Vector3<float>(0.15F));
	b_save.setMouseClickColor(Vector3<float>(0.30F));
	b_save.setMouseHoverColor(Vector3<float>(0.30F));
	b_save.setParent(controlPanel.get());

	sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 32, 16, 16, 16); //save_sprite
	pos = Vector2<float>(0.0F, 25.0F);
	b_tiles = Button(sprite, pos, Vector2<float>(16.0F));
	b_tiles.setOutline(true);
	b_tiles.setOutlineColor(Vector3<float>(0.45));
	b_tiles.setMargin(Vector2<float>(8, 8));
	b_tiles.setButtonColor(Vector3<float>(0.15F));
	b_tiles.setMouseClickColor(Vector3<float>(0.30F));
	b_tiles.setMouseHoverColor(Vector3<float>(0.30F));
	b_tiles.setParent(controlPanel.get());

	sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 48, 16, 16, 16); //save_sprite
	pos = Vector2<float>(30.0F, 25.0F);
	b_objects = Button(sprite, pos, Vector2<float>(16.0F));
	b_objects.setOutline(true);
	b_objects.setOutlineColor(Vector3<float>(0.45));
	b_objects.setMargin(Vector2<float>(8, 8));
	b_objects.setButtonColor(Vector3<float>(0.15F));
	b_objects.setMouseClickColor(Vector3<float>(0.30F));
	b_objects.setMouseHoverColor(Vector3<float>(0.30F));
	b_objects.setParent(controlPanel.get());

	//yeni harita paneli
	this->NewMap.newPanel = std::make_shared<Panel>(Vector2<float>(tilePanel->getSize().x + 20, controlPanel->getSize().y), "New Map", Vector2<float>(400, 135), *textRenderer, true, true, 1.0F, Vector3<float>(0.21F), 0.8F);
	this->NewMap.newPanel->setMovable(false);
	this->NewMap.newPanel->setEnable(false);

	NewMap.t_mapSizeX = std::make_shared<TextBox>(Vector2<float>(180.0F, 40.0F), *textRenderer, Vector2<float>(60.0F, 20.0F), true, 1.0F, Vector3<float>(0.58F));
	NewMap.t_mapSizeX->setParent(NewMap.newPanel.get());
	NewMap.t_mapSizeY = std::make_shared<TextBox>(Vector2<float>(250.0F, 40.0F), *textRenderer, Vector2<float>(60.0F, 20.0F), true, 1.0F, Vector3<float>(0.58F));
	NewMap.t_mapSizeY->setParent(NewMap.newPanel.get());
	NewMap.t_tile = std::make_shared<TextBox>(Vector2<float>(180.0F, 65.0F), *textRenderer, Vector2<float>(120.0F, 20.0F), true, 1.0F, Vector3<float>(0.58F));
	NewMap.t_tile->setParent(NewMap.newPanel.get());

	NewMap.l_mapSize = std::make_shared<Label>("Map Size", Vector2<float>(40.0F, 40.0F), *textRenderer, 1.0F, Vector3<float>(0.58F));
	NewMap.l_mapSize->setParent(NewMap.newPanel.get());
	NewMap.l_mapSize->setMouseEvent(false);
	NewMap.l_x = std::make_shared<Label>("x", Vector2<float>(240.0F, 40.0F), *textRenderer, 1.0F, Vector3<float>(0.58F));
	NewMap.l_x->setParent(NewMap.newPanel.get());
	NewMap.l_x->setMouseEvent(false);
	NewMap.l_tile = std::make_shared<Label>("Tileset", Vector2<float>(40.0F, 65.0F), *textRenderer, 1.0F, Vector3<float>(0.58F));
	NewMap.l_tile->setParent(NewMap.newPanel.get());
	NewMap.l_tile->setMouseEvent(false);
	NewMap.b_okey = std::make_shared<Button>("Okay", Vector2<float>(50.0F, 105.0F), Vector2<float>(60.0F, 20.0F), *textRenderer, Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
	NewMap.b_okey->setMouseClickColor(Vector3<float>(0.30F));
	NewMap.b_okey->setMouseHoverColor(Vector3<float>(0.30F));
	NewMap.b_okey->setLabelMouseHoverColor(Vector3<float>(0.58F));
	NewMap.b_okey->setLabelClickColor(Vector3<float>(1.0F));
	NewMap.b_okey->setOutline(true);
	NewMap.b_okey->setOutlineColor(Vector3<float>(1.0F));
	NewMap.b_okey->setParent(NewMap.newPanel.get());

	//harita yukle paneli
	this->SaveLoad.loadPanel = std::make_shared<Panel>(Vector2<float>(tilePanel->getSize().x + 20, controlPanel->getSize().y), "Load Panel", Vector2<float>(400, 200), *textRenderer, true, true, 1.0F, Vector3<float>(0.21F), 0.8F);
	this->SaveLoad.loadPanel->setMovable(false);
	this->SaveLoad.loadPanel->setEnable(false);
	this->SaveLoad.load_mapsPanel = std::make_shared<Panel>(Vector2<float>(20, 60), "Map Panel", Vector2<float>(300, 100), *textRenderer, true, false, 1.0F, Vector3<float>(0.21F), 0.6F);
	this->SaveLoad.load_mapsPanel->setMovable(false);
	this->SaveLoad.load_mapsPanel->setEnable(false);
	this->SaveLoad.load_mapsPanel->setScrollable(true);
	this->SaveLoad.load_mapsPanel->setOutline(true);
	this->SaveLoad.load_mapsPanel->setOutlineColor(Vector3<float>(0.47F));
	this->SaveLoad.load_mapsPanel->setParent(SaveLoad.loadPanel.get(), false);
	this->SaveLoad.load_mapsPanel->setParentCenterPos();
	this->SaveLoad.load_listMaps = std::make_shared<ListItem>(this->SaveLoad.load_mapsPanel.get());
	this->SaveLoad.t_load = std::make_shared<TextBox>(Vector2<float>(20.0F, 170.0F), *textRenderer, Vector2<float>(120.0F, 20.0F), true, 1.0F, Vector3<float>(0.58F));
	this->SaveLoad.t_load->setParent(SaveLoad.loadPanel.get());
	this->SaveLoad.b_map_load = std::make_shared<Button>("Load", Vector2<float>(180.0F, 170.0F), Vector2<float>(60.0F, 20.0F), *textRenderer, Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
	this->SaveLoad.b_map_load->setMouseClickColor(Vector3<float>(0.30F));
	this->SaveLoad.b_map_load->setMouseHoverColor(Vector3<float>(0.30F));
	this->SaveLoad.b_map_load->setLabelMouseHoverColor(Vector3<float>(0.58F));
	this->SaveLoad.b_map_load->setLabelClickColor(Vector3<float>(1.0F));
	this->SaveLoad.b_map_load->setOutline(true);
	this->SaveLoad.b_map_load->setOutlineColor(Vector3<float>(1.0F));
	this->SaveLoad.b_map_load->setParent(SaveLoad.loadPanel.get());
	std::function<void(Button *, Button *)> loadListChanged = std::bind(&SaveLoadSystem::LoadListChanged, &this->SaveLoad, std::placeholders::_1, std::placeholders::_2);
	this->SaveLoad.load_listMaps->AddListener(loadListChanged);

	//harita save paneli
	this->SaveLoad.savePanel = std::make_shared<Panel>(Vector2<float>(tilePanel->getSize().x + 20, controlPanel->getSize().y), "Save Panel", Vector2<float>(400, 200), *textRenderer, true, true, 1.0F, Vector3<float>(0.21F), 0.8F);
	this->SaveLoad.savePanel->setMovable(false);
	this->SaveLoad.savePanel->setEnable(false);
	this->SaveLoad.save_mapsPanel = std::make_shared<Panel>(Vector2<float>(20, 60), "Map Panel", Vector2<float>(300, 100), *textRenderer, true, false, 1.0F, Vector3<float>(0.21F), 0.6F);
	this->SaveLoad.save_mapsPanel->setMovable(false);
	this->SaveLoad.save_mapsPanel->setEnable(false);
	this->SaveLoad.save_mapsPanel->setScrollable(true);
	this->SaveLoad.save_mapsPanel->setOutline(true);
	this->SaveLoad.save_mapsPanel->setOutlineColor(Vector3<float>(0.47F));
	this->SaveLoad.save_mapsPanel->setParent(SaveLoad.savePanel.get(), false);
	this->SaveLoad.save_mapsPanel->setParentCenterPos();
	this->SaveLoad.save_listMaps = std::make_shared<ListItem>(this->SaveLoad.save_mapsPanel.get());
	this->SaveLoad.t_save = std::make_shared<TextBox>(Vector2<float>(20.0F, 170.0F), *textRenderer, Vector2<float>(120.0F, 20.0F), true, 1.0F, Vector3<float>(0.58F));
	this->SaveLoad.t_save->setParent(SaveLoad.savePanel.get());
	this->SaveLoad.b_map_save = std::make_shared<Button>("Save", Vector2<float>(180.0F, 170.0F), Vector2<float>(60.0F, 20.0F), *textRenderer, Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
	this->SaveLoad.b_map_save->setMouseClickColor(Vector3<float>(0.30F));
	this->SaveLoad.b_map_save->setMouseHoverColor(Vector3<float>(0.30F));
	this->SaveLoad.b_map_save->setLabelMouseHoverColor(Vector3<float>(0.58F));
	this->SaveLoad.b_map_save->setLabelClickColor(Vector3<float>(1.0F));
	this->SaveLoad.b_map_save->setOutline(true);
	this->SaveLoad.b_map_save->setOutlineColor(Vector3<float>(1.0F));
	this->SaveLoad.b_map_save->setParent(SaveLoad.savePanel.get());
	std::function<void(Button *, Button *)> saveListChanged = std::bind(&SaveLoadSystem::SaveListChanged, &this->SaveLoad, std::placeholders::_1, std::placeholders::_2);
	this->SaveLoad.load_listMaps->AddListener(saveListChanged);

	//env_item

	//tile properties
	this->tilePropertiesPanel = std::make_shared<Panel>(Vector2<float>(tilePanel->getSize().x + 20, controlPanel->getSize().y), "Tile Properties", Vector2<float>(400, 400), *textRenderer, true, true, 1.0F, Vector3<float>(0.21F), 0.8F);
	this->tilePropertiesPanel->setMovable(false);
	this->tilePropertiesPanel->setEnable(false);

	this->b_tileProperties = std::make_shared<Button>("Tile Properties", Vector2<float>(10.0F, buildPanel->getSize().y - 35.0F), Vector2<float>(30.0F, 15.0F), *textRenderer);
	this->b_tileProperties->setOutline(true);
	this->b_tileProperties->setOutlineColor(Vector3<float>(0.54));
	this->b_tileProperties->setLabelColor(Vector3<float>(0.54F));
	this->b_tileProperties->setLabelMouseHoverColor(Vector3<float>(0.60F));
	this->b_tileProperties->setLabelClickColor(Vector3<float>(0.60F));
	this->b_tileProperties->setButtonColor(Vector3<float>(0.15F));
	this->b_tileProperties->setMouseClickColor(Vector3<float>(0.30F));
	this->b_tileProperties->setMouseHoverColor(Vector3<float>(0.30F));
	this->b_tileProperties->setParent(buildPanel.get());

	this->rb_tileProperties = std::make_shared<RadioButton>(*textRenderer, Vector2<float>(20.0F, 50.0F), 30);
	this->rb_tileProperties->setParent(tilePropertiesPanel.get());
	this->rb_tileProperties->Clear();
	this->rb_tileProperties->AddElement("Wall", Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
	this->rb_tileProperties->AddElement("Obstacle", Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
	this->rb_tileProperties->AddElement("Floor", Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
	std::function<void(RadioButtonElement *, RadioButtonElement *)> t = std::bind(&Editor::SelectedRbChanged, this, std::placeholders::_1, std::placeholders::_2);
	this->rb_tileProperties->AddListener(t);

	item_0.Initialize();

	this->selectedMode = SelectedMode::TILE_MOD;
}

void Editor::OnEnable()
{
	currentTileSet = "cs2dnorm";
	Start();
	NewMapResult r = NewMap.NewMap("cs2dnorm", Vector2<int>(50), this->time, position, firstSelect, mapLimit, texture,
								   tileCount, tilePanel, buildPanel, *selectedTile, maxCellInColumn);
	tiles = r.tiles;
	tilesUI = r.tilesUI;
	selectedTile = tilesUI.at(0).get()->getTile();
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

void Editor::Update()
{
	this->time += Timer::DeltaTime;
	this->buildPanel->Update();
	this->NewMap.Update();
	this->tilePropertiesPanel->Update();
	SaveLoad.Update();
	objects_ui->Update();
	item_0.p_panel->Update();

	if (InputManager::scrollYPressed && selectedMode == SelectedMode::TILE_MOD && tilePanel->isScrollable())
	{
		if (!tilesUI.empty())
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
		InputManager::scrollYPressed = false;
	}
}

void Editor::ProcessInput()
{
	this->buildPanel->ProcessInput();
	this->NewMap.ProcessInput();
	this->tilePropertiesPanel->ProcessInput();
	this->SaveLoad.ProcessInput();
	this->objects_ui->ProcessInput();
	item_0.p_panel->ProcessInput();

	if (!tilesUI.empty())
	{
		for (auto &tile : tilesUI)
		{
			if (tile->isRenderable())
			{
				tile->ProcessInput();
				if (tile->isMouseDown())
				{
					selectedTile = tile->getTile();
					firstSelect = true;
				}
			}
		}
	}

	/*for (std::vector<int>::size_type i = 0; i != newMap.newPanel->childs.size(); i++)
	{
		if (newMap.newPanel->childs[i]->GetObjectTypeString() == "TextBox")
		{
			TextBox *t = dynamic_cast<TextBox *>(newMap.newPanel->childs[i]);
			if (t->editMode)
			{
				passMovement = true;
				break;
			}
			t = nullptr;
		}
	}*/

	bool passMovement = SaveLoad.isEditMode() || NewMap.isEditMode();

	if (!passMovement)
	{
		if (InputManager::isKey(GLFW_KEY_W))
		{
			this->position = Vector2(this->position.x, this->position.y - Game_Parameters::SCREEN_HEIGHT * Timer::DeltaTime);
		}
		if (InputManager::isKey(GLFW_KEY_S))
		{
			this->position = Vector2(this->position.x, this->position.y + Game_Parameters::SCREEN_HEIGHT * Timer::DeltaTime);
		}
		if (InputManager::isKey(GLFW_KEY_A))
		{
			this->position = Vector2(this->position.x - Game_Parameters::SCREEN_HEIGHT * Timer::DeltaTime, this->position.y);
		}
		if (InputManager::isKey(GLFW_KEY_D))
		{
			this->position = Vector2(this->position.x + Game_Parameters::SCREEN_HEIGHT * Timer::DeltaTime, this->position.y);
		}
	}

	if (InputManager::isKeyDown(GLFW_KEY_ESCAPE))
	{
		Game::SetGameState(GameState::MENU);
	}

	if (NewMap.b_okey->isMouseDown())
	{
		NewMapResult r = NewMap.B_NewMap(this->time, position, firstSelect, mapLimit, texture,
										 tileCount, tilePanel, buildPanel, *selectedTile, maxCellInColumn);

		if (!r.tiles.empty() && !r.tilesUI.empty())
		{
			NewMap.newPanel->setEnable(false);
			tiles = r.tiles;
			tilesUI = r.tilesUI;
			selectedTile = tilesUI.at(0).get()->getTile();
		}
		else
		{
			//oops
		}
	}

	if (b_new.isMouseDown())
	{
		this->NewMap.newPanel->setEnable(true);
	}

	if (b_save.isMouseDown())
	{
		SaveLoad.B_SaveMap();
	}

	if (SaveLoad.b_map_save->isMouseDown())
	{
		SaveLoad.SaveMap();
	}

	if (b_load.isMouseDown())
	{
		SaveLoad.B_LoadMap();
	}

	if (b_objects.isMouseDown())
	{
		tilePanel->setEnable(false);
		objectPanel->setEnable(true);
	}

	if (b_tiles.isMouseDown())
	{
		objectPanel->setEnable(false);
		tilePanel->setEnable(true);
	}

	if (SaveLoad.b_map_load->isMouseDown())
	{
		this->time = 0.0F;
		this->position = Vector2<float>(0.0F - buildPanel->getSize().x, 0.0F);
		firstSelect = false;
		tiles = SaveLoad.LoadMap(SaveLoad.t_load->getText());
	}

	if (b_tileProperties->isMouseDown())
	{
		this->tilePropertiesPanel->setEnable(true);
		this->rb_tileProperties->Select(static_cast<int>(selectedTile->getType()));
	}

	bool panelsPressed = !buildPanel->isPressed && !tilePropertiesPanel->isPressed &&
						 !buildPanel->isMouseHover(false) && !NewMap.isPressedOrHover() &&
						 !tilePropertiesPanel->isMouseHover(false) && !SaveLoad.isPressedOrHover();

	if (firstSelect && panelsPressed)
	{
		if (InputManager::isButton(GLFW_MOUSE_BUTTON_LEFT))
		{
			Vector2 wd = Utils::ScreenToWorld(camera->view, InputManager::mousePos);
			//Logger::DebugLog("pos: " + std::to_string(wd.x) + " - " + std::to_string(wd.y));
			Vector2 selectedCell = Utils::PositionToCell(wd);
			//Logger::DebugLog("pos: " + std::to_string(selectedCell.x) + " - " + std::to_string(selectedCell.y));
			for (auto &tile : tiles)
			{
				if (tile.cell == selectedCell)
				{
					Tile tilee = Tile(Utils::CellToPosition(selectedCell), selectedTile->sprite, Vector2<float>(Game_Parameters::SIZE_TILE), selectedTile->getType(), selectedTile->frame);
					Button bt = Button(tilee);
					if (!(selectedTile->frame == tile.button.getTile()->frame))
					{
						tile.button = bt;
					}
				}
			}
		}
	}
}

void Editor::Render()
{
	camera->setPosition(position);

	worldRenderer.SetProjection(camera->cameraMatrix);
	squareRenderer.SetProjection(camera->cameraMatrix);

	Vector2<int> ms = Utils::PositionToCell(Utils::ScreenToWorld(camera->view, InputManager::mousePos));
	bool f = false;
	for (auto &tile_1 : tiles)
	{
		tile_1.button.Draw(worldRenderer, squareRenderer);

		squareRenderer.world_RenderEmptySquare(Utils::CellToPosition(tile_1.cell), Vector2<float>(Game_Parameters::SIZE_TILE), cell_yellow);

		if (!f && ms == tile_1.cell && !NewMap.isMouseHover() && !buildPanel->isMouseHover(false) && !SaveLoad.isMouseHover())
		{
			f = true;
			Vector2<float> pos = Utils::CellToPosition(tile_1.cell);
			squareRenderer.world_RenderEmptySquareWithLine(pos, Vector2<float>(Game_Parameters::SIZE_TILE), mouse_yellow, 2.0F);
		}
	}
	item_0.Render(worldRenderer, menuRenderer, squareRenderer, this->time);
	//ui
	this->buildPanel->Draw(menuRenderer, squareRenderer);

	this->NewMap.Render(menuRenderer, squareRenderer);

	this->tilePropertiesPanel->Draw(menuRenderer, squareRenderer);

	SaveLoad.Render(menuRenderer, squareRenderer);

	if (!tilesUI.empty())
	{
		for (auto &tile : tilesUI)
		{
			if (firstSelect && selectedTile->GetID() == tile->getTile()->GetID())
			{
				tile->Draw(menuRenderer, squareRenderer, 0.3F, true, this->time);
			}
			else if (tile->isMouseHover())
			{
				tile->Draw(menuRenderer, squareRenderer, 0.3F, false, this->time);
			}
			else
			{
				tile->Draw(menuRenderer, squareRenderer);
			}
		}
	}
	objects_ui->Draw(menuRenderer, squareRenderer);
}

void Editor::SelectedRbChanged(RadioButtonElement *old, RadioButtonElement *n)
{
	selectedTile->setType((TileTypes)n->getIndex());
}
