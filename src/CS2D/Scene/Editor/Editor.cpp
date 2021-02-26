#include "Editor.hpp"

#if defined(WIN32) && defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

Editor::Editor()
{
    this->tileCount = 0;
    this->maxCellInColumn = 0;
    this->maxCellInRow = 0;
    this->position = Vector2(0);
    this->firstSelect = false;
    this->time = 0.0F;
    this->mapLimit = Vector2<int>(0);
    this->texture = Vector2<int>(0);
    this->selectedMode = SelectedMode::TILE_MOD;
}

Editor::~Editor() { OnDisable(); }

void Editor::Initialize()
{
    this->tileCount = 0;
    this->maxCellInColumn = 0;
    this->maxCellInRow = 0;
    this->position = Vector2(0);
    this->firstSelect = false;
    this->time = 0.0F;
    this->mapLimit = Vector2<int>(0);
    this->texture = Vector2<int>(0);
    this->selectedMode = SelectedMode::TILE_MOD;
}

void Editor::Start()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    this->menuRenderer = new SpriteRenderer(ResourceManager::GetShader("menu"));
    this->worldRenderer =
        new SpriteRenderer(ResourceManager::GetShader("sprite"));
    this->textRenderer = new TextRenderer(GameParameters::SCREEN_WIDTH,
                                          GameParameters::SCREEN_HEIGHT);
    this->textRenderer->Load(
        GameParameters::resDirectory + "fonts/liberationsans.ttf", 16);
    this->squareRenderer = new SquareRenderer(true);
    this->camera = new Camera(static_cast<int>(GameParameters::SCREEN_WIDTH),
                              static_cast<int>(GameParameters::SCREEN_HEIGHT));
    camera->setPosition(position);
    worldRenderer->SetProjection(camera->cameraMatrix);
    squareRenderer->SetProjection(camera->cameraMatrix);
    this->mouse_yellow = Vector3<float>(0.73F, 0.73F, 0.0F);
    this->cell_yellow = Vector3<float>(0.15F, 0.15F, 0.0F);
    this->maxCellInColumn = 5;
    this->maxCellInRow =
        (GameParameters::SCREEN_HEIGHT - (32 * 4) - 22) / 32 + 1;

    this->buildPanel = new Panel(Vector2<int>(0, 0), "Build Panel",
                                 Vector2<int>(32 * maxCellInColumn + (5 * 2),
                                              GameParameters::SCREEN_HEIGHT),
                                 *textRenderer, true, false, 1.0F,
                                 Vector3<float>(0.21F), 1.0F);
    this->buildPanel->setMovable(false);
    this->buildPanel->SetEnable(true);

    this->controlPanel = new Panel(
        Vector2<int>(buildPanel->GetPosition().x + 5, buildPanel->GetPosition().y + 5), "Control Panel",
        Vector2<int>(32 * maxCellInColumn, 32 * 2 - 11), *textRenderer, buildPanel, true,
        false, 1.0F, Vector3<float>(0.21F), 1.0F);
    this->controlPanel->setMovable(false);
    this->controlPanel->SetEnable(true);

    this->tilePanel = new Panel(
        Vector2<int>(buildPanel->GetPosition().x + 5, buildPanel->GetPosition().y + 75), "Tile Panel",
        Vector2<int>(32 * maxCellInColumn, 32 * maxCellInRow), *textRenderer, buildPanel,
        true, false, 1.0F, Vector3<float>(0.21F), 1.0F);
    this->tilePanel->SetEnable(true);
    this->tilePanel->setMovable(false);
    this->tilePanel->SetScrollable(true);
    this->tilePanel->setOutline(true);
    this->tilePanel->setOutlineColor(Vector3<float>(0.47F));

    this->objectPanel = new Panel(
        Vector2<int>(buildPanel->GetPosition().x + 5, buildPanel->GetPosition().y + 75), "Object Panel",
        Vector2<int>(32 * maxCellInColumn, 32 * maxCellInRow), *textRenderer, buildPanel,
        true, false, 1.0F, Vector3<float>(0.21F), 1.0F);
    this->objectPanel->SetEnable(false);
    this->objectPanel->setMovable(false);
    this->objectPanel->SetScrollable(true);
    this->objectPanel->setOutline(true);
    this->objectPanel->setOutlineColor(Vector3<float>(0.47F));

    objects_ui = new ListItem(this->objectPanel);
    objects_ui->Clear();
    std::string a = "Env_Item";
    objects_ui->AddItem(a);

    Sprite sprite;
    Vector2<int> pos;

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 16, 0, 16,
                    16);  // new_sprite
    pos = Vector2<int>(0) + controlPanel->GetPosition();
    b_new = new SpriteButton(sprite, pos, Vector2<int>(16), controlPanel);
    b_new->setHaveOutline(true);
    b_new->setOutlineColor(Vector3<float>(0.45));
    b_new->setMargin(Vector2<int>(8, 8));
    b_new->setButtonColor(Vector3<float>(0.15F));
    b_new->setButtonClickColor(Vector3<float>(0.30F));
    b_new->setButtonHoverColor(Vector3<float>(0.30F));
    b_new->addListenerDown(std::bind(&Editor::b_newMap_click, this));

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 32, 0, 16,
                    16);  // load_sprite
    pos = Vector2<int>(30, 0) + controlPanel->GetPosition();
    ;
    b_load = new SpriteButton(sprite, pos, Vector2<int>(16), controlPanel);
    b_load->setHaveOutline(true);
    b_load->setOutlineColor(Vector3<float>(0.45));
    b_load->setMargin(Vector2<int>(8, 8));
    b_load->setButtonColor(Vector3<float>(0.15F));
    b_load->setButtonClickColor(Vector3<float>(0.30F));
    b_load->setButtonHoverColor(Vector3<float>(0.30F));
    b_load->addListenerDown(std::bind(&Editor::b_loadMap_click, this));

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 48, 0, 16,
                    16);  // save_sprite
    pos = Vector2<int>(60, 0) + controlPanel->GetPosition();
    ;
    b_save = new SpriteButton(sprite, pos, Vector2<int>(16), controlPanel);
    b_save->setHaveOutline(true);
    b_save->setOutlineColor(Vector3<float>(0.45));
    b_save->setMargin(Vector2<int>(8, 8));
    b_save->setButtonColor(Vector3<float>(0.15F));
    b_save->setButtonClickColor(Vector3<float>(0.30F));
    b_save->setButtonHoverColor(Vector3<float>(0.30F));
    b_save->addListenerDown(std::bind(&Editor::b_saveMap_click, this));

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 32, 16, 16,
                    16);  // save_sprite
    pos = Vector2<int>(0, 25) + controlPanel->GetPosition();
    ;
    b_tiles = new SpriteButton(sprite, pos, Vector2<int>(16), controlPanel);
    b_tiles->setHaveOutline(true);
    b_tiles->setOutlineColor(Vector3<float>(0.45));
    b_tiles->setMargin(Vector2<int>(8, 8));
    b_tiles->setButtonColor(Vector3<float>(0.15F));
    b_tiles->setButtonClickColor(Vector3<float>(0.30F));
    b_tiles->setButtonHoverColor(Vector3<float>(0.30F));
    b_tiles->addListenerDown(std::bind(&Editor::b_tiles_click, this));

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 48, 16, 16,
                    16);  // save_sprite
    pos = Vector2<int>(30, 25) + controlPanel->GetPosition();
    ;
    b_objects = new SpriteButton(sprite, pos, Vector2<int>(16), controlPanel);
    b_objects->setHaveOutline(true);
    b_objects->setOutlineColor(Vector3<float>(0.45));
    b_objects->setMargin(Vector2<int>(8, 8));
    b_objects->setButtonColor(Vector3<float>(0.15F));
    b_objects->setButtonClickColor(Vector3<float>(0.30F));
    b_objects->setButtonHoverColor(Vector3<float>(0.30F));
    b_objects->addListenerDown(std::bind(&Editor::b_objects_click, this));

    // yeni harita paneli
    this->NewMap = new NewMapSystem();
    NewMap->b_okey->addListenerDown(std::bind(&Editor::newMap_okay, this));


    // harita yukle paneli
    this->SaveLoad = new SaveLoadSystem();
    SaveLoad->b_map_save->addListenerDown(std::bind(&Editor::save_okay, this));
    SaveLoad->b_map_load->addListenerDown(std::bind(&Editor::load_okay, this));

    // env_item
    envItemManager = new Env_Item_Manager();
    envItemManager->AddCancelListener(std::bind(&Editor::envitem_cancel, this));
    envItemManager->AddDelListener(std::bind(&Editor::envitem_delete, this));
    envItemManager->AddOkayListener(std::bind(&Editor::envitem_okay, this));

    // tile properties
    this->tilePropertiesPanel = new Panel(
        Vector2<int>(tilePanel->GetPosition().x + tilePanel->GetSize().x + 20, tilePanel->GetPosition().y + controlPanel->GetSize().y),
        "Tile Properties", Vector2<int>(400, 400), *textRenderer, true, true,
        1.0F, Vector3<float>(0.21F), 0.8F);
    this->tilePropertiesPanel->setMovable(false);
    this->tilePropertiesPanel->SetEnable(false);

    this->b_tileProperties = new TextButton(
        "Tile Properties", Vector2<int>(buildPanel->GetPosition().x + 10, buildPanel->GetPosition().y + buildPanel->GetSize().y - 35),
        Vector2<int>(30, 15), *textRenderer, buildPanel);
    this->b_tileProperties->setHaveOutline(true);
    this->b_tileProperties->setOutlineColor(Vector3<float>(0.54));
    this->b_tileProperties->setTextColor(Vector3<float>(0.54F));
    this->b_tileProperties->setTextHoverColor(Vector3<float>(0.60F));
    this->b_tileProperties->setTextClickColor(Vector3<float>(0.60F));
    this->b_tileProperties->setButtonColor(Vector3<float>(0.15F));
    this->b_tileProperties->setButtonClickColor(Vector3<float>(0.30F));
    this->b_tileProperties->setButtonHoverColor(Vector3<float>(0.30F));
    this->b_tileProperties->addListenerDown(std::bind(&Editor::tileProperties_click, this));

    this->rb_tileProperties =
        new RadioButton(*textRenderer, Vector2<int>(tilePropertiesPanel->GetPosition().x + 20, tilePropertiesPanel->GetPosition().y + 50), 30, tilePropertiesPanel);
    this->rb_tileProperties->Clear();
    this->rb_tileProperties->AddElement("Wall", Vector3<float>(0.15F),
                                        Vector3<float>(0.58F), 1.0F);
    this->rb_tileProperties->AddElement("Obstacle", Vector3<float>(0.15F),
                                        Vector3<float>(0.58F), 1.0F);
    this->rb_tileProperties->AddElement("Floor", Vector3<float>(0.15F),
                                        Vector3<float>(0.58F), 1.0F);
    std::function<void(RadioButtonElement *, RadioButtonElement *)> t =
        std::bind(&Editor::SelectedRbChanged, this, std::placeholders::_1,
                  std::placeholders::_2);
    this->rb_tileProperties->AddChangeListener(t);

    this->selectedMode = SelectedMode::TILE_MOD;

    for (auto &item : tils->tiles)
    {
        item->tileButton->addListener(std::bind(&Editor::select_tile_world, this, std::placeholders::_1));
    }
    for (auto &item : tils->tilesUI)
    {
        item->addListener(std::bind(&Editor::select_tile_ui, this, std::placeholders::_1));
    }
}

void Editor::OnEnable()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    currentTileSet = "cs2dnorm";
    if (tils != nullptr)
    {
        for (auto tile : tils->tiles)
        {
            delete tile;
        }
        tils->tiles.clear();
        for (auto tile : tils->tilesUI)
        {
            delete tile;
        }
        tils->tilesUI.clear();
        delete tils;
    }

    for (auto &env : env_items)
    {
        if (env != nullptr) delete env;
    }
    env_items.clear();
    Start();
    tils = nullptr;
    tils = new NewMapResult();
    NewMapResult r = NewMap->NewMap("cs2dnorm", Vector2<int>(50));
    tils->tiles = r.tiles;
    tils->tilesUI = r.tilesUI;
    selectedTile = &tils->tilesUI.at(0)->getTile();
}

void Editor::OnDisable()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    selectedTile = nullptr;

    if (tils != nullptr)
    {
        for (auto tile : tils->tiles)
        {
            delete tile;
        }
        tils->tiles.clear();
        for (auto tile : tils->tilesUI)
        {
            delete tile;
        }
        tils->tilesUI.clear();
        delete tils;
    }
    tils = nullptr;

    if (objects_ui != nullptr) delete objects_ui;
    objects_ui = nullptr;

    for (auto &env : env_items)
    {
        if (env != nullptr) delete env;
    }
    env_items.clear();

    if (envItemManager != nullptr) delete envItemManager;
    envItemManager = nullptr;

    if (NewMap != nullptr) delete NewMap;
    NewMap = nullptr;
    if (SaveLoad != nullptr) delete SaveLoad;
    SaveLoad = nullptr;
    if (b_cancel != nullptr) delete b_cancel;
    b_cancel = nullptr;
    if (rb_tileProperties != nullptr) delete rb_tileProperties;
    rb_tileProperties = nullptr;
    if (b_tileProperties != nullptr) delete b_tileProperties;
    b_tileProperties = nullptr;
    if (tilePropertiesPanel != nullptr) delete tilePropertiesPanel;
    tilePropertiesPanel = nullptr;
    if (objects_ui != nullptr) delete objects_ui;
    objects_ui = nullptr;

    if (b_save != nullptr) delete b_save;
    b_save = nullptr;
    if (b_new != nullptr) delete b_new;
    b_new = nullptr;
    if (b_load != nullptr) delete b_load;
    b_load = nullptr;
    if (b_objects != nullptr) delete b_objects;
    b_objects = nullptr;
    if (b_tiles != nullptr) delete b_tiles;
    b_tiles = nullptr;

    if (tilePanel != nullptr) delete tilePanel;
    tilePanel = nullptr;
    if (objectPanel != nullptr) delete objectPanel;
    objectPanel = nullptr;
    if (controlPanel != nullptr) delete controlPanel;
    controlPanel = nullptr;
    if (buildPanel != nullptr) delete buildPanel;
    buildPanel = nullptr;

    if (menuRenderer != nullptr) delete menuRenderer;
    menuRenderer = nullptr;
    if (squareRenderer != nullptr) delete squareRenderer;
    squareRenderer = nullptr;
    if (worldRenderer != nullptr) delete worldRenderer;
    worldRenderer = nullptr;
    if (textRenderer != nullptr) delete textRenderer;
    textRenderer = nullptr;

    if (camera != nullptr) delete camera;
    camera = nullptr;
}

void Editor::SetEnable(const bool value)
{
    if (this->enable == value) return;
    this->enable = value;
    if (this->enable)
        OnEnable();
    else
        OnDisable();
}

void Editor::Update()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    this->time += Timer::DeltaTime;
    this->buildPanel->Update();
    this->NewMap->Update();
    this->tilePropertiesPanel->Update();
    envItemManager->Update();
    SaveLoad->Update();
    objects_ui->Update();
    for (std::vector<int>::size_type i = 0; i < env_items.size(); i++)
    {
        env_items[i]->Update();
    }

    if (InputManager::scrollYPressed &&
        selectedMode == SelectedMode::TILE_MOD && tilePanel->IsScrollable())
    {
        if (!tils->tilesUI.empty())
        {
            bool check_1 = tils->tilesUI.at(0)->GetLocalPosition().y == 0 &&
                           InputManager::scroll.y > 0;
            bool check_2 =
                tils->tilesUI.at(tileCount - 1)->GetLocalPosition().y ==
                    maxCellInRow * 32 &&
                InputManager::scroll.y < 0;

            if (!check_1 && !check_2)
            {
                for (auto &tile : tils->tilesUI)
                {
                    tile->SetPosition(Vector2<int>(tile->GetLocalPosition().x,
                                                   tile->GetLocalPosition().y +
                                                       InputManager::scroll.y * 32));
                }
            }
        }
        InputManager::scrollYPressed = false;
    }
}

void Editor::ProcessInput()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    this->buildPanel->ProcessInput();
    this->NewMap->ProcessInput();
    this->tilePropertiesPanel->ProcessInput();
    envItemManager->ProcessInput();
    this->SaveLoad->ProcessInput();
    this->objects_ui->ProcessInput();

    bool passMovement = SaveLoad->isEditMode() || NewMap->isEditMode();

    if (!passMovement)
    {
        if (InputManager::isKey(KeyboardKeys::KEY_W))
        {
            this->position = Vector2(
                this->position.x,
                this->position.y -
                    static_cast<int>(
                        static_cast<float>(GameParameters::SCREEN_HEIGHT) *
                        Timer::DeltaTime));
            camera->setPosition(position);
            worldRenderer->SetProjection(camera->cameraMatrix);
            squareRenderer->SetProjection(camera->cameraMatrix);
        }
        if (InputManager::isKey(KeyboardKeys::KEY_S))
        {
            this->position = Vector2(
                this->position.x,
                this->position.y +
                    static_cast<int>(
                        static_cast<float>(GameParameters::SCREEN_HEIGHT) *
                        Timer::DeltaTime));
            camera->setPosition(position);
            worldRenderer->SetProjection(camera->cameraMatrix);
            squareRenderer->SetProjection(camera->cameraMatrix);
        }
        if (InputManager::isKey(KeyboardKeys::KEY_A))
        {
            this->position = Vector2(
                this->position.x -
                    static_cast<int>(
                        static_cast<float>(GameParameters::SCREEN_HEIGHT) *
                        Timer::DeltaTime),
                this->position.y);
            camera->setPosition(position);
            worldRenderer->SetProjection(camera->cameraMatrix);
            squareRenderer->SetProjection(camera->cameraMatrix);
        }
        if (InputManager::isKey(KeyboardKeys::KEY_D))
        {
            this->position = Vector2(
                this->position.x +
                    static_cast<int>(
                        static_cast<float>(GameParameters::SCREEN_HEIGHT) *
                        Timer::DeltaTime),
                this->position.y);
            camera->setPosition(position);
            worldRenderer->SetProjection(camera->cameraMatrix);
            squareRenderer->SetProjection(camera->cameraMatrix);
        }
    }

    if (InputManager::isKeyDown(KeyboardKeys::KEY_ESCAPE))
    {
        Game::SetGameState(GameState::MENU);
        return;
    }

    panelsPressed =
        buildPanel->isPressed || tilePropertiesPanel->isPressed ||
        buildPanel->isMouseHover(false) || NewMap->isPressedOrHover() ||
        tilePropertiesPanel->isMouseHover(false) ||
        SaveLoad->isPressedOrHover() || envItemManager->isPressedOrHover();

    for (std::vector<int>::size_type i = 0; i < env_items.size(); i++)
    {
        if (!envItemManager->p_panel->IsEnable())
        {
            if (selectedMode == SelectedMode::OBJECT_MOD &&
                InputManager::isButtonDown(MOUSE_BUTTON_LEFT))
            {
                Vector2<int> sw =
                    Utils::ScreenToWorld(camera->view, InputManager::mousePos);
                Vector2<int> c =
                    Utils::PositionToCell(env_items[i]->getPosition());
                Vector2<int> d = Utils::PositionToCell(sw);
                if (d == c)
                {
                    envItemManager->p_panel->SetEnable(true);
                    envItemManager->t_id->setText(
                        std::to_string(env_items[i]->getItemID()));
                    selectedItem = env_items[i];
                }
            }
        }
    }


    if (selectedMode == SelectedMode::OBJECT_MOD)
    {
        if (!panelsPressed)
        {
            if (InputManager::isButtonDown(MOUSE_BUTTON_LEFT) &&
                objects_ui->getSelectedIndex() == 0)
            {
                Vector2 wd =
                    Utils::ScreenToWorld(camera->view, InputManager::mousePos);
                Vector2 selectedCell = Utils::PositionToCell(wd);
                for (auto &tile : tils->tiles)
                {
                    if (tile->tileButton->getTile().GetCellPos() == selectedCell)
                    {
                        if (tile->item == nullptr)
                        {
                            Env_Item *a = new Env_Item(
                                1, Utils::CellToPosition(selectedCell));
                            tile->SetItem(a);
                            break;
                        }
                    }
                }
            }
        }
    }
}

void Editor::Render()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    Vector2<int> ms = Utils::PositionToCell(
        Utils::ScreenToWorld(camera->view, InputManager::mousePos));
    bool f = false;
    for (auto &tile_1 : tils->tiles)
    {
        Vector2 pos = Utils::WorldToScreen(
            camera->view,
            tile_1->tileButton->getTile().GetCellPos() * Vector2<int>(GameParameters::SIZE_TILE));
        if (pos.x <= GameParameters::SCREEN_WIDTH && pos.x >= 0 &&
            pos.y <= GameParameters::SCREEN_HEIGHT && pos.y >= 0)
        {
            tile_1->tileButton->Draw(*worldRenderer, *squareRenderer);
            squareRenderer->world_RenderEmptySquare(
                tile_1->tileButton->getTile().GetCellPos(),
                Vector2<int>(GameParameters::SIZE_TILE), cell_yellow);
        }

        if (!f && ms == tile_1->tileButton->getTile().GetCellPos() && !NewMap->isMouseHover() &&
            !buildPanel->isMouseHover(false) && !SaveLoad->isMouseHover() &&
            !envItemManager->isPressedOrHover())
        {
            f = true;
            Vector2<int> pos = Utils::CellToPosition(tile_1->tileButton->getTile().GetCellPos());
            squareRenderer->world_RenderEmptySquare(
                pos, Vector2<int>(GameParameters::SIZE_TILE), mouse_yellow,
                1.0F, 0, 4.0F);
        }
    }
    for (std::vector<int>::size_type i = 0; i < env_items.size(); i++)
    {
        env_items[i]->Render(*worldRenderer, *menuRenderer, *squareRenderer,
                             this->time);
    }

    // ui
    this->buildPanel->Draw(*menuRenderer, *squareRenderer);

    this->NewMap->Render(*menuRenderer, *squareRenderer);

    this->tilePropertiesPanel->Draw(*menuRenderer, *squareRenderer);

    envItemManager->Draw(*menuRenderer, *squareRenderer);

    SaveLoad->Render(*menuRenderer, *squareRenderer);

    if (!tils->tilesUI.empty())
    {
        for (auto &tile : tils->tilesUI)
        {
            if (firstSelect &&
                selectedTile->GetId() == tile->getTile().GetId())
            {
                tile->Draw(*menuRenderer, *squareRenderer, 0.3F, true,
                           this->time);
            }
            else if (tile->isMouseHover())
            {
                tile->Draw(*menuRenderer, *squareRenderer, 0.3F, false,
                           this->time);
            }
            else
            {
                tile->Draw(*menuRenderer, *squareRenderer);
                int a = 2;
            }
        }
    }
    objects_ui->Draw(*squareRenderer);
    this->textRenderer->RenderText(
        "fps: " + std::to_string(InputManager::m_fps), Vector2(700, 135), 1.0F,
        0.5F);
}

void Editor::SelectedRbChanged(RadioButtonElement *old, RadioButtonElement *n)
{
    selectedTile->setType((TileTypes)n->getIndex());
}

void Editor::b_newMap_click()
{
    this->NewMap->newPanel->SetEnable(true);
}

void Editor::b_saveMap_click()
{
    SaveLoad->B_SaveMap();
}

void Editor::b_loadMap_click()
{
    SaveLoad->B_LoadMap();
}

void Editor::b_objects_click()
{
    tilePanel->SetEnable(false);
    objectPanel->SetEnable(true);
    selectedMode = SelectedMode::OBJECT_MOD;
}

void Editor::b_tiles_click()
{
    objectPanel->SetEnable(false);
    tilePanel->SetEnable(true);
    selectedMode = SelectedMode::TILE_MOD;
}

void Editor::select_tile_world(TileButtonWorld *n)
{
    if (!panelsPressed)
    {
        if (selectedMode == SelectedMode::TILE_MOD && firstSelect)
        {
            if (selectedTile->frame != n->getTile().frame)
            {
                n->getTile().frame = selectedTile->frame;
                n->getTile().sprite = selectedTile->sprite;
                n->getTile().setType(selectedTile->getType());
            }
        }
        else if (selectedMode == SelectedMode::OBJECT_MOD && objects_ui->getSelectedIndex() == 0)
        {
        }
    }
}

void Editor::select_tile_ui(TileButtonScreen *n)
{
    if (n->IsRenderable())
    {
        selectedTile = &n->getTile();
        firstSelect = true;
    }
}

void Editor::newMap_okay()
{
    NewMapResult t = NewMap->B_NewMap();

    if (!t.tiles.empty() && !t.tilesUI.empty())
    {
        if (tils != nullptr)
        {
            for (auto tile : tils->tiles)
            {
                delete tile;
            }
            tils->tiles.clear();
            for (auto tile : tils->tilesUI)
            {
                delete tile;
            }
            tils->tilesUI.clear();
            delete tils;
        }

        for (auto &env : env_items)
        {
            if (env != nullptr) delete env;
        }
        env_items.clear();
        tils = nullptr;
        NewMap->newPanel->SetEnable(false);
        tils = new NewMapResult();
        tils->tiles = t.tiles;
        tils->tilesUI = t.tilesUI;
    }
    else
    {
        for (auto tile : t.tiles)
        {
            delete tile;
        }
        t.tiles.clear();
        for (auto tile : t.tilesUI)
        {
            delete tile;
        }
        t.tilesUI.clear();
        // delete t;

        // t = nullptr;
        // oops
    }
}

void Editor::save_okay()
{
    SaveLoad->SaveMap();
}

void Editor::load_okay()
{
    this->time = 0.0F;
    this->position = Vector2<int>(0 - buildPanel->GetSize().x, 0);
    std::string newMapName = SaveLoad->t_load->getText();
    OnDisable();
    OnEnable();
    currentTileSet = "cs2dnorm";
    if (tils != nullptr)
    {
        for (auto tile : tils->tiles)
        {
            delete tile;
        }
        tils->tiles.clear();
    }

    tils->tiles = SaveLoad->LoadMap(newMapName);
    selectedTile = &tils->tilesUI.at(0)->getTile();
}

void Editor::tileProperties_click()
{
    this->tilePropertiesPanel->SetEnable(true);
    this->rb_tileProperties->Select(
        static_cast<int>(selectedTile->getType()));
}

void Editor::envitem_okay()
{
    if (envItemManager->p_panel->IsEnable())
    {
        selectedItem->setItemID(
            atoi(envItemManager->t_id->getText().c_str()));
        envItemManager->p_panel->SetEnable(false);
    }
}

void Editor::envitem_cancel()
{
    if (envItemManager->p_panel->IsEnable())
    {
        envItemManager->p_panel->SetEnable(false);
    }
}


void Editor::envitem_delete()
{
    if (envItemManager->p_panel->IsEnable())
    {
        for (std::vector<int>::size_type i = 0; i < env_items.size(); i++)
        {
            if (env_items[i]->getObjID() == selectedItem->getObjID())
            {
                for (std::vector<int>::size_type j = 0;
                     j < tils->tiles.size(); j++)
                {
                    if (tils->tiles[j]->item != nullptr &&
                        tils->tiles[j]->item->getObjID() ==
                            selectedItem->getObjID())
                    {
                        tils->tiles[j]->item = nullptr;
                        break;
                    }
                }

                delete env_items[i];
                env_items.erase(env_items.begin() + i);
                selectedItem = nullptr;
                break;
            }
        }
        envItemManager->p_panel->SetEnable(false);
    }
}
