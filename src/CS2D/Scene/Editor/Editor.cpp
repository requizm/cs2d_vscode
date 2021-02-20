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
    this->buildPanel->setEnable(true);

    this->controlPanel = new Panel(
        Vector2<int>(5, 5), "Control Panel",
        Vector2<int>(32 * maxCellInColumn, 32 * 2 - 11), *textRenderer, true,
        false, 1.0F, Vector3<float>(0.21F), 1.0F);
    this->controlPanel->setMovable(false);
    this->controlPanel->setEnable(true);
    this->controlPanel->setParent(buildPanel);

    this->tilePanel = new Panel(
        Vector2<int>(5, 75), "Tile Panel",
        Vector2<int>(32 * maxCellInColumn, 32 * maxCellInRow), *textRenderer,
        true, false, 1.0F, Vector3<float>(0.21F), 1.0F);
    this->tilePanel->setEnable(true);
    this->tilePanel->setMovable(false);
    this->tilePanel->setScrollable(true);
    this->tilePanel->setOutline(true);
    this->tilePanel->setOutlineColor(Vector3<float>(0.47F));
    this->tilePanel->setParent(buildPanel);

    this->objectPanel = new Panel(
        Vector2<int>(5, 75), "Object Panel",
        Vector2<int>(32 * maxCellInColumn, 32 * maxCellInRow), *textRenderer,
        true, false, 1.0F, Vector3<float>(0.21F), 1.0F);
    this->objectPanel->setEnable(false);
    this->objectPanel->setMovable(false);
    this->objectPanel->setScrollable(true);
    this->objectPanel->setOutline(true);
    this->objectPanel->setOutlineColor(Vector3<float>(0.47F));
    this->objectPanel->setParent(buildPanel);

    objects_ui = new ListItem(this->objectPanel);
    objects_ui->Clear();
    std::string a = "Env_Item";
    objects_ui->AddItem(a);

    Sprite sprite;
    Vector2<int> pos;

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 16, 0, 16,
                    16);  // new_sprite
    pos = Vector2<int>(0);
    b_new = new Button(sprite, pos, Vector2<int>(16));
    b_new->setOutline(true);
    b_new->setOutlineColor(Vector3<float>(0.45));
    b_new->setMargin(Vector2<int>(8, 8));
    b_new->setButtonColor(Vector3<float>(0.15F));
    b_new->setMouseClickColor(Vector3<float>(0.30F));
    b_new->setMouseHoverColor(Vector3<float>(0.30F));
    b_new->setParent(controlPanel);

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 32, 0, 16,
                    16);  // load_sprite
    pos = Vector2<int>(30, 0);
    b_load = new Button(sprite, pos, Vector2<int>(16));
    b_load->setOutline(true);
    b_load->setOutlineColor(Vector3<float>(0.45));
    b_load->setMargin(Vector2<int>(8, 8));
    b_load->setButtonColor(Vector3<float>(0.15F));
    b_load->setMouseClickColor(Vector3<float>(0.30F));
    b_load->setMouseHoverColor(Vector3<float>(0.30F));
    b_load->setParent(controlPanel);

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 48, 0, 16,
                    16);  // save_sprite
    pos = Vector2<int>(60, 0);
    b_save = new Button(sprite, pos, Vector2<int>(16));
    b_save->setOutline(true);
    b_save->setOutlineColor(Vector3<float>(0.45));
    b_save->setMargin(Vector2<int>(8, 8));
    b_save->setButtonColor(Vector3<float>(0.15F));
    b_save->setMouseClickColor(Vector3<float>(0.30F));
    b_save->setMouseHoverColor(Vector3<float>(0.30F));
    b_save->setParent(controlPanel);

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 32, 16, 16,
                    16);  // save_sprite
    pos = Vector2<int>(0, 25);
    b_tiles = new Button(sprite, pos, Vector2<int>(16));
    b_tiles->setOutline(true);
    b_tiles->setOutlineColor(Vector3<float>(0.45));
    b_tiles->setMargin(Vector2<int>(8, 8));
    b_tiles->setButtonColor(Vector3<float>(0.15F));
    b_tiles->setMouseClickColor(Vector3<float>(0.30F));
    b_tiles->setMouseHoverColor(Vector3<float>(0.30F));
    b_tiles->setParent(controlPanel);

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 48, 16, 16,
                    16);  // save_sprite
    pos = Vector2<int>(30, 25);
    b_objects = new Button(sprite, pos, Vector2<int>(16));
    b_objects->setOutline(true);
    b_objects->setOutlineColor(Vector3<float>(0.45));
    b_objects->setMargin(Vector2<int>(8, 8));
    b_objects->setButtonColor(Vector3<float>(0.15F));
    b_objects->setMouseClickColor(Vector3<float>(0.30F));
    b_objects->setMouseHoverColor(Vector3<float>(0.30F));
    b_objects->setParent(controlPanel);

    // yeni harita paneli
    this->NewMap = new NewMapSystem();
    this->NewMap->newPanel = new Panel(
        Vector2<int>(tilePanel->getSize().x + 20, controlPanel->getSize().y),
        "New Map", Vector2<int>(400, 135), *textRenderer, true, true, 1.0F,
        Vector3<float>(0.21F), 0.8F);
    this->NewMap->newPanel->setMovable(false);
    this->NewMap->newPanel->setEnable(false);

    NewMap->t_mapSizeX =
        new TextBox(Vector2<int>(180, 40), *textRenderer, Vector2<int>(60, 20),
                    true, 1.0F, Vector3<float>(0.58F));
    NewMap->t_mapSizeX->setParent(NewMap->newPanel);
    NewMap->t_mapSizeY =
        new TextBox(Vector2<int>(250, 40), *textRenderer, Vector2<int>(60, 20),
                    true, 1.0F, Vector3<float>(0.58F));
    NewMap->t_mapSizeY->setParent(NewMap->newPanel);
    NewMap->t_tile =
        new TextBox(Vector2<int>(180, 65), *textRenderer, Vector2<int>(120, 20),
                    true, 1.0F, Vector3<float>(0.58F));
    NewMap->t_tile->setParent(NewMap->newPanel);

    NewMap->l_mapSize = new Label(
        "Map Size", Vector2<int>(40, 40), *textRenderer, 1.0F,
        Vector3<float>(0.58F), UIObjectType::LABEL, LabelType::NOT_CLICKABLE);
    NewMap->l_mapSize->setParent(NewMap->newPanel);
    NewMap->l_mapSize->setMouseEvent(false);
    NewMap->l_x = new Label("x", Vector2<int>(240, 40), *textRenderer, 1.0F,
                            Vector3<float>(0.58F), UIObjectType::LABEL,
                            LabelType::NOT_CLICKABLE);
    NewMap->l_x->setParent(NewMap->newPanel);
    NewMap->l_x->setMouseEvent(false);
    NewMap->l_tile = new Label("Tileset", Vector2<int>(40, 65), *textRenderer,
                               1.0F, Vector3<float>(0.58F), UIObjectType::LABEL,
                               LabelType::NOT_CLICKABLE);
    NewMap->l_tile->setParent(NewMap->newPanel);
    NewMap->l_tile->setMouseEvent(false);
    NewMap->b_okey = new Button(
        "Okay", Vector2<int>(50, 105), Vector2<int>(60, 20), *textRenderer,
        Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    NewMap->b_okey->setMouseClickColor(Vector3<float>(0.30F));
    NewMap->b_okey->setMouseHoverColor(Vector3<float>(0.30F));
    NewMap->b_okey->setLabelMouseHoverColor(Vector3<float>(0.58F));
    NewMap->b_okey->setLabelClickColor(Vector3<float>(1.0F));
    NewMap->b_okey->setOutline(true);
    NewMap->b_okey->setOutlineColor(Vector3<float>(1.0F));
    NewMap->b_okey->setParent(NewMap->newPanel);

    // harita yukle paneli
    this->SaveLoad = new SaveLoadSystem();
    this->SaveLoad->loadPanel = new Panel(
        Vector2<int>(tilePanel->getSize().x + 20, controlPanel->getSize().y),
        "Load Panel", Vector2<int>(400, 200), *textRenderer, true, true, 1.0F,
        Vector3<float>(0.21F), 0.8F);
    this->SaveLoad->loadPanel->setMovable(false);
    this->SaveLoad->loadPanel->setEnable(false);
    this->SaveLoad->load_mapsPanel = new Panel(
        Vector2<int>(20, 60), "Map Panel", Vector2<int>(300, 100),
        *textRenderer, true, false, 1.0F, Vector3<float>(0.21F), 0.6F);
    this->SaveLoad->load_mapsPanel->setMovable(false);
    this->SaveLoad->load_mapsPanel->setEnable(false);
    this->SaveLoad->load_mapsPanel->setScrollable(true);
    this->SaveLoad->load_mapsPanel->setOutline(true);
    this->SaveLoad->load_mapsPanel->setVisible(true);
    this->SaveLoad->load_mapsPanel->setOutlineColor(Vector3<float>(0.47F));
    this->SaveLoad->load_mapsPanel->setParent(SaveLoad->loadPanel, true);
    this->SaveLoad->load_mapsPanel->setParentCenterPos();
    this->SaveLoad->load_listMaps =
        new ListItem(this->SaveLoad->load_mapsPanel);
    // this->SaveLoad->load_listMaps->setParent(this->SaveLoad->load_mapsPanel,
    // true);
    this->SaveLoad->t_load =
        new TextBox(Vector2<int>(20, 170), *textRenderer, Vector2<int>(120, 20),
                    true, 1.0F, Vector3<float>(0.58F));
    this->SaveLoad->t_load->setParent(SaveLoad->loadPanel);
    this->SaveLoad->t_load->editable = false;
    this->SaveLoad->b_map_load = new Button(
        "Load", Vector2<int>(180, 170), Vector2<int>(60, 20), *textRenderer,
        Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    this->SaveLoad->b_map_load->setMouseClickColor(Vector3<float>(0.30F));
    this->SaveLoad->b_map_load->setMouseHoverColor(Vector3<float>(0.30F));
    this->SaveLoad->b_map_load->setLabelMouseHoverColor(Vector3<float>(0.58F));
    this->SaveLoad->b_map_load->setLabelClickColor(Vector3<float>(1.0F));
    this->SaveLoad->b_map_load->setOutline(true);
    this->SaveLoad->b_map_load->setOutlineColor(Vector3<float>(1.0F));
    this->SaveLoad->b_map_load->setParent(SaveLoad->loadPanel);
    std::function<void(Button *, Button *)> loadListChanged =
        std::bind(&SaveLoadSystem::LoadListChanged, this->SaveLoad,
                  std::placeholders::_1, std::placeholders::_2);
    this->SaveLoad->load_listMaps->AddListener(loadListChanged);

    // harita save paneli
    this->SaveLoad->savePanel = new Panel(
        Vector2<int>(tilePanel->getSize().x + 20, controlPanel->getSize().y),
        "Save Panel", Vector2<int>(400, 200), *textRenderer, true, true, 1.0F,
        Vector3<float>(0.21F), 0.8F);
    this->SaveLoad->savePanel->setMovable(false);
    this->SaveLoad->savePanel->setEnable(false);
    this->SaveLoad->save_mapsPanel = new Panel(
        Vector2<int>(20, 60), "Map Panel", Vector2<int>(300, 100),
        *textRenderer, true, false, 1.0F, Vector3<float>(0.21F), 0.6F);
    this->SaveLoad->save_mapsPanel->setMovable(false);
    this->SaveLoad->save_mapsPanel->setEnable(false);
    this->SaveLoad->save_mapsPanel->setScrollable(true);
    this->SaveLoad->save_mapsPanel->setOutline(true);
    this->SaveLoad->save_mapsPanel->setVisible(true);
    this->SaveLoad->save_mapsPanel->setOutlineColor(Vector3<float>(0.47F));
    this->SaveLoad->save_mapsPanel->setParent(SaveLoad->savePanel, true);
    this->SaveLoad->save_mapsPanel->setParentCenterPos();
    this->SaveLoad->save_listMaps =
        new ListItem(this->SaveLoad->save_mapsPanel);
    // this->SaveLoad->save_listMaps->setParent(this->SaveLoad->save_mapsPanel,
    // true);
    this->SaveLoad->t_save =
        new TextBox(Vector2<int>(20, 170), *textRenderer, Vector2<int>(120, 20),
                    true, 1.0F, Vector3<float>(0.58F));
    this->SaveLoad->t_save->setParent(SaveLoad->savePanel);
    this->SaveLoad->b_map_save = new Button(
        "Save", Vector2<int>(180, 170), Vector2<int>(60, 20), *textRenderer,
        Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    this->SaveLoad->b_map_save->setMouseClickColor(Vector3<float>(0.30F));
    this->SaveLoad->b_map_save->setMouseHoverColor(Vector3<float>(0.30F));
    this->SaveLoad->b_map_save->setLabelMouseHoverColor(Vector3<float>(0.58F));
    this->SaveLoad->b_map_save->setLabelClickColor(Vector3<float>(1.0F));
    this->SaveLoad->b_map_save->setOutline(true);
    this->SaveLoad->b_map_save->setOutlineColor(Vector3<float>(1.0F));
    this->SaveLoad->b_map_save->setParent(SaveLoad->savePanel);
    std::function<void(Button *, Button *)> saveListChanged =
        std::bind(&SaveLoadSystem::SaveListChanged, this->SaveLoad,
                  std::placeholders::_1, std::placeholders::_2);
    this->SaveLoad->save_listMaps->AddListener(saveListChanged);

    // env_item
    envItemManager = new Env_Item_Manager();

    // tile properties
    this->tilePropertiesPanel = new Panel(
        Vector2<int>(tilePanel->getSize().x + 20, controlPanel->getSize().y),
        "Tile Properties", Vector2<int>(400, 400), *textRenderer, true, true,
        1.0F, Vector3<float>(0.21F), 0.8F);
    this->tilePropertiesPanel->setMovable(false);
    this->tilePropertiesPanel->setEnable(false);

    this->b_tileProperties = new Button(
        "Tile Properties", Vector2<int>(10, buildPanel->getSize().y - 35),
        Vector2<int>(30, 15), *textRenderer);
    this->b_tileProperties->setOutline(true);
    this->b_tileProperties->setOutlineColor(Vector3<float>(0.54));
    this->b_tileProperties->setLabelColor(Vector3<float>(0.54F));
    this->b_tileProperties->setLabelMouseHoverColor(Vector3<float>(0.60F));
    this->b_tileProperties->setLabelClickColor(Vector3<float>(0.60F));
    this->b_tileProperties->setButtonColor(Vector3<float>(0.15F));
    this->b_tileProperties->setMouseClickColor(Vector3<float>(0.30F));
    this->b_tileProperties->setMouseHoverColor(Vector3<float>(0.30F));
    this->b_tileProperties->setParent(buildPanel);

    this->rb_tileProperties =
        new RadioButton(*textRenderer, Vector2<int>(20, 50), 30);
    this->rb_tileProperties->setParent(tilePropertiesPanel);
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
    this->rb_tileProperties->AddListener(t);

    this->selectedMode = SelectedMode::TILE_MOD;
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
    selectedTile = tils->tilesUI.at(0)->getTile();
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
        selectedMode == SelectedMode::TILE_MOD && tilePanel->isScrollable())
    {
        if (!tils->tilesUI.empty())
        {
            bool check_1 = tils->tilesUI.at(0)->getLocalPosition().y == 0 &&
                           InputManager::scroll.y > 0;
            bool check_2 =
                tils->tilesUI.at(tileCount - 1)->getLocalPosition().y ==
                    maxCellInRow * 32 &&
                InputManager::scroll.y < 0;

            if (!check_1 && !check_2)
            {
                for (auto &tile : tils->tilesUI)
                {
                    tile->setPosition(tile->getLocalPosition().x,
                                      tile->getLocalPosition().y +
                                          InputManager::scroll.y * 32);
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

    for (auto &tile : tils->tilesUI)
    {
        if (tile->isRenderable())
        {
            // tile->ProcessInput();
            if (tile->isMouseDown())
            {
                selectedTile = tile->getTile();
                firstSelect = true;
            }
        }
    }

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

    if (NewMap->b_okey->isMouseDown())
    {
#if defined(WIN32) && defined(TRACY_ENABLE)
        ZoneScoped;
#endif
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
            NewMap->newPanel->setEnable(false);
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

    if (b_new->isMouseDown())
    {
        this->NewMap->newPanel->setEnable(true);
    }

    if (b_save->isMouseDown())
    {
        SaveLoad->B_SaveMap();
    }

    if (SaveLoad->b_map_save->isMouseDown())
    {
        SaveLoad->SaveMap();
    }

    if (b_load->isMouseDown())
    {
        SaveLoad->B_LoadMap();
    }

    if (b_objects->isMouseDown())
    {
        tilePanel->setEnable(false);
        objectPanel->setEnable(true);
        selectedMode = SelectedMode::OBJECT_MOD;
    }

    if (b_tiles->isMouseDown())
    {
        objectPanel->setEnable(false);
        tilePanel->setEnable(true);
        selectedMode = SelectedMode::TILE_MOD;
    }

    if (SaveLoad->b_map_load->isMouseDown())
    {
#if defined(WIN32) && defined(TRACY_ENABLE)
        ZoneScoped;
#endif
        this->time = 0.0F;
        this->position = Vector2<int>(0 - buildPanel->getSize().x, 0);
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
        selectedTile = tils->tilesUI.at(0)->getTile();
    }

    if (b_tileProperties->isMouseDown())
    {
        this->tilePropertiesPanel->setEnable(true);
        this->rb_tileProperties->Select(
            static_cast<int>(selectedTile->getType()));
    }

    bool panelsPressed =
        buildPanel->isPressed || tilePropertiesPanel->isPressed ||
        buildPanel->isMouseHover(false) || NewMap->isPressedOrHover() ||
        tilePropertiesPanel->isMouseHover(false) ||
        SaveLoad->isPressedOrHover() || envItemManager->isPressedOrHover();

    for (std::vector<int>::size_type i = 0; i < env_items.size(); i++)
    {
        if (!envItemManager->p_panel->isEnable())
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
                    envItemManager->p_panel->setEnable(true);
                    envItemManager->t_id->setText(
                        std::to_string(env_items[i]->getItemID()));
                    selectedItem = env_items[i];
                }
            }
        }
    }

    if (envItemManager->p_panel->isEnable())
    {
        if (envItemManager->b_okay->isMouseDown())
        {
            selectedItem->setItemID(
                atoi(envItemManager->t_id->getText().c_str()));
            envItemManager->p_panel->setEnable(false);
        }
        else if (envItemManager->b_cancel->isMouseDown())
        {
            envItemManager->p_panel->setEnable(false);
        }
        else if (envItemManager->b_delete->isMouseDown())
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
#if defined(WIN32) && defined(TRACY_ENABLE)
                    ZoneScoped;
#endif
                    delete env_items[i];
                    env_items.erase(env_items.begin() + i);
                    selectedItem = nullptr;
                    break;
                }
            }
            envItemManager->p_panel->setEnable(false);
        }
    }

    if (selectedMode == SelectedMode::TILE_MOD)
    {
        if (firstSelect && !panelsPressed)
        {
            if (InputManager::isButton(MOUSE_BUTTON_LEFT))
            {
                Vector2 wd =
                    Utils::ScreenToWorld(camera->view, InputManager::mousePos);
                Vector2 selectedCell = Utils::PositionToCell(wd);
                for (auto &tile : tils->tiles)
                {
                    if (tile->cell == selectedCell)
                    {
                        Tile tilee =
                            Tile(Utils::CellToPosition(selectedCell),
                                 selectedTile->sprite,
                                 Vector2<int>(GameParameters::SIZE_TILE),
                                 selectedTile->getType(), selectedTile->frame);
                        if (!(selectedTile->frame ==
                              tile->button->getTile()->frame))
                        {
#if defined(WIN32) && defined(TRACY_ENABLE)
                            ZoneScoped;
#endif
                            Button *bt = new Button(tilee);
                            tile->SetButton(bt);
                            break;
                        }
                    }
                }
            }
        }
    }
    else if (selectedMode == SelectedMode::OBJECT_MOD)
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
                    if (tile->cell == selectedCell)
                    {
                        if (tile->item == nullptr)
                        {
#if defined(WIN32) && defined(TRACY_ENABLE)
                            ZoneScoped;
#endif
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
            tile_1->cell * Vector2<int>(GameParameters::SIZE_TILE));
        if (pos.x <= GameParameters::SCREEN_WIDTH && pos.x >= 0 &&
            pos.y <= GameParameters::SCREEN_HEIGHT && pos.y >= 0)
        {
            tile_1->button->Draw(*worldRenderer, *squareRenderer);
            squareRenderer->world_RenderEmptySquare(
                Utils::CellToPosition(tile_1->cell),
                Vector2<int>(GameParameters::SIZE_TILE), cell_yellow);
        }

        if (!f && ms == tile_1->cell && !NewMap->isMouseHover() &&
            !buildPanel->isMouseHover(false) && !SaveLoad->isMouseHover() &&
            !envItemManager->isPressedOrHover())
        {
            f = true;
            Vector2<int> pos = Utils::CellToPosition(tile_1->cell);
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
                selectedTile->GetID() == tile->getTile()->GetID())
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
    objects_ui->Draw(*menuRenderer, *squareRenderer);
    this->textRenderer->RenderText(
        "fps: " + std::to_string(InputManager::m_fps), Vector2(700, 135), 1.0F,
        0.5F);
}

void Editor::SelectedRbChanged(RadioButtonElement *old, RadioButtonElement *n)
{
    selectedTile->setType((TileTypes)n->getIndex());
}
