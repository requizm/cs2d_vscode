#include "Editor.hpp"

#include "../../../Core/Manager/InputManager.hpp"
#include "../../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../../Core/Manager/ResourceManager.hpp"
#include "../../../Core/Manager/Timer.hpp"
#include "../../../Core/Manager/Utils.hpp"
#include "../../Other/GameParameters.hpp"
#include "../../Other/SceneManager.hpp"


#if defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

Editor::Editor() : Scene("Editor")
{
    this->tileCount = 0;
    this->maxCellInColumn = 0;
    this->maxCellInRow = 0;
    this->position = Vector2(0);
    this->mapLimit = Vector2<int>(0);
    this->texture = Vector2<int>(0);
    this->selectedMode = SelectedMode::TILE_MOD;
    Initialize();
}

void Editor::Initialize()
{
    this->tileCount = 0;
    this->maxCellInColumn = 0;
    this->maxCellInRow = 0;
    this->position = Vector2(0);
    this->mapLimit = Vector2<int>(0);
    this->texture = Vector2<int>(0);
    this->selectedMode = SelectedMode::TILE_MOD;
}

void Editor::Load()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    this->menuRenderer = std::make_shared<SpriteRenderer>(
        ResourceManager::GetShader("menu"));
    this->worldRenderer = std::make_shared<SpriteRenderer>(ResourceManager::GetShader("sprite"));
    this->textRenderer = std::make_shared<TextRenderer>(
        GameParameters::SCREEN_WIDTH,
        GameParameters::SCREEN_HEIGHT);
    this->textRenderer->Load(
        GameParameters::resDirectory + "fonts/liberationsans.ttf", 16);
    this->squareRenderer = std::make_shared<SquareRenderer>(true);
    this->camera = std::make_shared<Camera>(static_cast<int>(GameParameters::SCREEN_WIDTH),
                                            static_cast<int>(GameParameters::SCREEN_HEIGHT));
    camera->setPosition(position);
    worldRenderer->SetProjection(camera->cameraMatrix);
    squareRenderer->SetProjection(camera->cameraMatrix);
    this->mouse_yellow = Vector3<float>(0.73F, 0.73F, 0.0F);
    this->cell_yellow = Vector3<float>(0.15F, 0.15F, 0.0F);
    this->maxCellInColumn = 5;
    this->maxCellInRow =
        (GameParameters::SCREEN_HEIGHT - (32 * 4) - 22) / 32 + 1;

    this->buildPanel = std::make_shared<Panel>(Vector2<int>(0, 0), "Build Panel",
                                               Vector2<int>(32 * maxCellInColumn + (5 * 2),
                                                            GameParameters::SCREEN_HEIGHT),
                                               *textRenderer, true, false, 1.0F,
                                               Vector3<float>(0.21F), 1.0F);
    this->buildPanel->InitTitleAndEscapeButton(*textRenderer, "Build Panel");
    this->buildPanel->setMovable(false);
    this->buildPanel->setEnable(true);

    this->controlPanel = std::make_shared<Panel>(Vector2<int>(5, 5), "Control Panel",
                                                 Vector2<int>(32 * maxCellInColumn, 32 * 2 - 11),
                                                 *textRenderer, true, false, 1.0F,
                                                 Vector3<float>(0.21F), 1.0F);
    this->controlPanel->InitTitleAndEscapeButton(*textRenderer, "Control Panel");
    this->controlPanel->setMovable(false);
    this->controlPanel->setEnable(true);
    this->controlPanel->setParent(buildPanel);

    this->tilePanel = std::make_shared<Panel>(Vector2<int>(5, 75), "Tile Panel",
                                              Vector2<int>(32 * maxCellInColumn, 32 * maxCellInRow),
                                              *textRenderer, true, false, 1.0F,
                                              Vector3<float>(0.21F), 1.0F);
    this->tilePanel->InitTitleAndEscapeButton(*textRenderer, "Tile Panel");
    this->tilePanel->setEnable(true);
    this->tilePanel->setMovable(false);
    this->tilePanel->setScrollable(true);
    this->tilePanel->setOutline(true);
    this->tilePanel->setOutlineColor(Vector3<float>(0.47F));
    this->tilePanel->setParent(buildPanel);

    this->objectPanel = std::make_shared<Panel>(Vector2<int>(5, 75), "Object Panel",
                                                Vector2<int>(32 * maxCellInColumn, 32 * maxCellInRow),
                                                *textRenderer, true, false, 1.0F,
                                                Vector3<float>(0.21F), 1.0F);
    this->objectPanel->InitTitleAndEscapeButton(*textRenderer, "Object Panel");
    this->objectPanel->setEnable(false);
    this->objectPanel->setMovable(false);
    this->objectPanel->setScrollable(true);
    this->objectPanel->setOutline(true);
    this->objectPanel->setOutlineColor(Vector3<float>(0.47F));
    this->objectPanel->setParent(buildPanel);

    objects_ui = std::make_shared<ListItem>(this->objectPanel);
    objects_ui->Clear();
    std::string a = "Env_Item";
    objects_ui->AddItem(a);

    Sprite sprite;
    Vector2<int> pos;

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 16, 0, 16,
                    16);  // new_sprite
    pos = Vector2<int>(0);
    b_new = std::make_shared<SpriteButton>(sprite, pos, Vector2<int>(16));
    b_new->setHaveOutline(true);
    b_new->setOutlineColor(Vector3<float>(0.45F));
    b_new->setMargin(Vector2<int>(8, 8));
    b_new->setButtonColor(Vector3<float>(0.15F));
    b_new->setButtonClickColor(Vector3<float>(0.30F));
    b_new->setButtonHoverColor(Vector3<float>(0.30F));
    b_new->setParent(controlPanel);

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 32, 0, 16,
                    16);  // load_sprite
    pos = Vector2<int>(30, 0);
    b_load = std::make_shared<SpriteButton>(sprite, pos, Vector2<int>(16));
    b_load->setHaveOutline(true);
    b_load->setOutlineColor(Vector3<float>(0.45F));
    b_load->setMargin(Vector2<int>(8, 8));
    b_load->setButtonColor(Vector3<float>(0.15F));
    b_load->setButtonClickColor(Vector3<float>(0.30F));
    b_load->setButtonHoverColor(Vector3<float>(0.30F));
    b_load->setParent(controlPanel);

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 48, 0, 16,
                    16);  // save_sprite
    pos = Vector2<int>(60, 0);
    b_save = std::make_shared<SpriteButton>(sprite, pos, Vector2<int>(16));
    b_save->setHaveOutline(true);
    b_save->setOutlineColor(Vector3<float>(0.45F));
    b_save->setMargin(Vector2<int>(8, 8));
    b_save->setButtonColor(Vector3<float>(0.15F));
    b_save->setButtonClickColor(Vector3<float>(0.30F));
    b_save->setButtonHoverColor(Vector3<float>(0.30F));
    b_save->setParent(controlPanel);

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 32, 16, 16,
                    16);  // save_sprite
    pos = Vector2<int>(0, 25);
    b_tiles = std::make_shared<SpriteButton>(sprite, pos, Vector2<int>(16));
    b_tiles->setHaveOutline(true);
    b_tiles->setOutlineColor(Vector3<float>(0.45F));
    b_tiles->setMargin(Vector2<int>(8, 8));
    b_tiles->setButtonColor(Vector3<float>(0.15F));
    b_tiles->setButtonClickColor(Vector3<float>(0.30F));
    b_tiles->setButtonHoverColor(Vector3<float>(0.30F));
    b_tiles->setParent(controlPanel);

    sprite = Sprite(ResourceManager::GetTexture("gui_icons"), 48, 16, 16,
                    16);  // save_sprite
    pos = Vector2<int>(30, 25);
    // b_objects = new SpriteButton(sprite, pos, Vector2<int>(16));
    b_objects = std::make_shared<SpriteButton>(sprite, pos, Vector2<int>(16));
    b_objects->setHaveOutline(true);
    b_objects->setOutlineColor(Vector3<float>(0.45F));
    b_objects->setMargin(Vector2<int>(8, 8));
    b_objects->setButtonColor(Vector3<float>(0.15F));
    b_objects->setButtonClickColor(Vector3<float>(0.30F));
    b_objects->setButtonHoverColor(Vector3<float>(0.30F));
    b_objects->setParent(controlPanel);

    // yeni harita paneli
    this->NewMap = std::make_shared<NewMapSystem>();
    this->NewMap->Load();

    // harita yukle paneli
    this->SaveLoad = std::make_shared<SaveLoadSystem>();
    this->SaveLoad->Load();

    // env_item
    envItemManager = std::make_shared<Env_Item_Manager>();

    // tile properties
    this->tilePropertiesPanel = std::make_shared<Panel>(
        Vector2<int>(tilePanel->getSize().x + 20, controlPanel->getSize().y),
        "Tile Properties", Vector2<int>(400, 400), *textRenderer, true, true,
        1.0F, Vector3<float>(0.21F), 0.8F);
    this->tilePropertiesPanel->InitTitleAndEscapeButton(*textRenderer, "Tile Properties");
    this->tilePropertiesPanel->setMovable(false);
    this->tilePropertiesPanel->setEnable(false);

    this->b_tileProperties = std::make_shared<TextButton>(
        "Tile Properties", Vector2<int>(10, 10), Vector2<int>(380, 15),
        *textRenderer);
    this->b_tileProperties->setHaveOutline(true);
    this->b_tileProperties->setOutlineColor(Vector3<float>(0.54F));
    this->b_tileProperties->setTextColor(Vector3<float>(0.54F));
    this->b_tileProperties->setTextHoverColor(Vector3<float>(0.60F));
    this->b_tileProperties->setTextClickColor(Vector3<float>(0.60F));
    this->b_tileProperties->setButtonColor(Vector3<float>(0.15F));
    this->b_tileProperties->setButtonClickColor(Vector3<float>(0.30F));
    this->b_tileProperties->setButtonHoverColor(Vector3<float>(0.30F));
    this->b_tileProperties->setParent(buildPanel);

    this->rb_tileProperties = std::make_shared<RadioButton>(
        *textRenderer, Vector2<int>(20, 50), 30);
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

    editorMapRenderer = std::make_shared<EditorMapRenderer>();

    if (firstLoad == true)
    {
        tils = std::move(NewMap->NewMap("cs2dnorm", Vector2<int>(50)));
        tils->tilesUI[0]->getTile();
        selectedTile = std::make_shared<Tile>(tils->tilesUI[0]->getTile());

        int mapL = mapLimit.x * mapLimit.y;
        editorMapRenderer->init(mapL);

        for (int i = 0; i < mapL; i++)
        {
            Vector2<int> pos = Utils::CellToPosition(tils->tiles[i]->cell);
            editorMapRenderer->addRect(pos, Vector2<int>(GameParameters::SIZE_TILE), cell_yellow, 1.0F, 0);
        }
        editorMapRenderer->updateData();

        firstLoad = false;
    }
}

void Editor::Unload()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    selectedTile = nullptr;

    objects_ui.reset();

    for (auto &env : env_items)
    {
        env.reset();
    }
    env_items.clear();

    envItemManager.reset();

    NewMap.reset();
    SaveLoad.reset();
    rb_tileProperties.reset();
    b_tileProperties.reset();
    tilePropertiesPanel.reset();
    objects_ui.reset();

    b_save.reset();
    b_new.reset();
    b_load.reset();
    b_objects.reset();
    b_tiles.reset();

    tilePanel.reset();
    objectPanel.reset();
    controlPanel.reset();
    buildPanel.reset();

    menuRenderer.reset();
    squareRenderer.reset();
    worldRenderer.reset();
    textRenderer.reset();

    camera.reset();

    editorMapRenderer.reset();
}

void Editor::Update()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    Timer::timeSinceSceneStart += Timer::DeltaTime;
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
        if (texture.x > 0)
        {
            bool check_1 = tils->tilesUI[0]->getLocalPosition().y == 0 &&
                           InputManager::scroll.y > 0;
            bool check_2 =
                tils->tilesUI[tileCount - 1]->getLocalPosition().y ==
                    maxCellInRow * 32 &&
                InputManager::scroll.y < 0;

            if (!check_1 && !check_2)
            {
                for (int i = 0; i < tileCount; i++)
                {
                    tils->tilesUI[i]->setLocalPosition(Vector2<int>(tils->tilesUI[i]->getLocalPosition().x,
                                                                    tils->tilesUI[i]->getLocalPosition().y +
                                                                        InputManager::scroll.y * 32));
                }
            }
        }
        InputManager::scrollYPressed = false;
    }
}

void Editor::ProcessInput()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    this->buildPanel->ProcessInput();
    this->NewMap->ProcessInput();
    this->tilePropertiesPanel->ProcessInput();
    envItemManager->ProcessInput();
    this->SaveLoad->ProcessInput();
    this->objects_ui->ProcessInput();

    for (int i = 0; i < tileCount; i++)
    {
        if (tils->tilesUI[i]->isRenderable())
        {
            // tils->tilesUIProcessInput();
            if (tils->tilesUI[i]->IsMouseDown())
            {
                selectedTile = std::make_shared<Tile>(tils->tilesUI[i]->getTile());
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
            editorMapRenderer->setProjection(camera->cameraMatrix);
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
            editorMapRenderer->setProjection(camera->cameraMatrix);
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
            editorMapRenderer->setProjection(camera->cameraMatrix);
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
            editorMapRenderer->setProjection(camera->cameraMatrix);
        }
    }

    if (InputManager::isKeyDown(KeyboardKeys::KEY_ESCAPE))
    {
        firstLoad = true;
        SceneManager::instance().RequestLoadScene("Menu");
        return;
    }

    if (NewMap->b_okey->IsMouseDown())
    {
        std::unique_ptr<NewMapResult> t = NewMap->B_NewMap();
        if (t != nullptr)
        {
            for (auto &env : env_items)
            {
                env.reset();
            }
            env_items.clear();
            NewMap->newPanel->setEnable(false);
            tils = std::move(t);

            int mapL = mapLimit.x * mapLimit.y;
            editorMapRenderer = std::make_shared<EditorMapRenderer>();
            editorMapRenderer->init(mapL);

            for (int i = 0; i < mapL; i++)
            {
                Vector2<int> pos = Utils::CellToPosition(tils->tiles[i]->cell);
                editorMapRenderer->addRect(pos, Vector2<int>(GameParameters::SIZE_TILE), cell_yellow, 1.0F, 0);
            }
            editorMapRenderer->updateData();
        }
    }
    if (!(NewMap->newPanel->isEnable() || SaveLoad->loadPanel->isEnable() || SaveLoad->savePanel->isEnable() || tilePropertiesPanel->isEnable() || envItemManager->p_panel->isEnable()))
    {
        if (b_new->IsMouseDown())
        {
            this->NewMap->newPanel->setEnable(true);
        }

        if (b_save->IsMouseDown())
        {
            SaveLoad->B_SaveMap();
        }

        if (b_load->IsMouseDown())
        {
            SaveLoad->B_LoadMap();
        }

        if (b_tileProperties->IsMouseDown())
        {
            this->tilePropertiesPanel->setEnable(true);
            this->rb_tileProperties->Select(
                static_cast<int>(selectedTile->getType()));
        }

        for (std::vector<int>::size_type i = 0; i < env_items.size(); i++)
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

    if (SaveLoad->b_map_save->IsMouseDown())
    {
        SaveLoad->SaveMap();
    }


    if (b_objects->IsMouseDown())
    {
        tilePanel->setEnable(false);
        objectPanel->setEnable(true);
        selectedMode = SelectedMode::OBJECT_MOD;
    }

    if (b_tiles->IsMouseDown())
    {
        objectPanel->setEnable(false);
        tilePanel->setEnable(true);
        selectedMode = SelectedMode::TILE_MOD;
    }

    if (SaveLoad->b_map_load->IsMouseDown())
    {
        Timer::timeSinceSceneStart = 0.0F;
        this->position = Vector2<int>(0 - buildPanel->getSize().x, 0);
        std::string newMapName = SaveLoad->t_load->getText();
        Unload();
        Load();

        tils = std::move(SaveLoad->LoadMap(newMapName));
        selectedTile = std::make_shared<Tile>(tils->tilesUI[0]->getTile());

        int mapL = mapLimit.x * mapLimit.y;
        editorMapRenderer->init(mapL);

        for (int i = 0; i < mapL; i++)
        {
            Vector2<int> pos = Utils::CellToPosition(tils->tiles[i]->cell);
            editorMapRenderer->addRect(pos, Vector2<int>(GameParameters::SIZE_TILE), cell_yellow, 1.0F, 0);
        }
        editorMapRenderer->updateData();
    }

    bool panelsPressed =
        buildPanel->isPressed || tilePropertiesPanel->isPressed ||
        buildPanel->isMouseHover(false) || NewMap->isPressedOrHover() ||
        tilePropertiesPanel->isMouseHover(false) ||
        SaveLoad->isPressedOrHover() || envItemManager->isPressedOrHover();


    if (envItemManager->p_panel->isEnable())
    {
        if (envItemManager->b_okay->IsMouseDown())
        {
            selectedItem->setItemID(
                atoi(envItemManager->t_id->getText().c_str()));
            envItemManager->p_panel->setEnable(false);
        }
        else if (envItemManager->b_cancel->IsMouseDown())
        {
            envItemManager->p_panel->setEnable(false);
        }
        else if (envItemManager->b_delete->IsMouseDown())
        {
            for (std::vector<int>::size_type i = 0; i < env_items.size(); i++)
            {
                if (env_items[i]->getObjID() == selectedItem->getObjID())
                {
                    for (int j = 0; j < mapLimit.x * mapLimit.y; j++)
                    {
                        if (tils->tiles[j]->item != nullptr &&
                            tils->tiles[j]->item->getObjID() ==
                                selectedItem->getObjID())
                        {
                            tils->tiles[j]->item = nullptr;
                            break;
                        }
                    }
                }
                env_items[i].reset();
                env_items.erase(env_items.begin() + i);
                selectedItem = nullptr;
                break;
            }
            envItemManager->p_panel->setEnable(false);
        }
    }

    if (selectedMode == SelectedMode::TILE_MOD)
    {
        if (!panelsPressed)
        {
            if (InputManager::isButton(MOUSE_BUTTON_LEFT))
            {
                Vector2 wd =
                    Utils::ScreenToWorld(camera->view, InputManager::mousePos);
                Vector2 selectedCell = Utils::PositionToCell(wd);
                for (int i = 0; i < mapLimit.x * mapLimit.y; i++)
                {
                    if (tils->tiles[i]->cell == selectedCell)
                    {
                        Tile tilee =
                            Tile(Utils::CellToPosition(selectedCell),
                                 selectedTile->sprite,
                                 Vector2<int>(GameParameters::SIZE_TILE),
                                 selectedTile->getType(), selectedTile->frame);
                        if (!(selectedTile->frame ==
                              tils->tiles[i]->button.getTile().frame))
                        {
                            TileButtonWorld bt = TileButtonWorld(tilee);
                            tils->tiles[i]->SetButton(bt);
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
                for (int i = 0; i < mapLimit.x * mapLimit.y; i++)
                {
                    if (tils->tiles[i]->cell == selectedCell)
                    {
                        if (tils->tiles[i]->item == nullptr)
                        {
                            auto a = std::make_shared<Env_Item>(
                                1, Utils::CellToPosition(selectedCell));
                            a->Initialize();
                            tils->tiles[i]->SetItem(a);
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
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    Vector2<int> ms = Utils::PositionToCell(
        Utils::ScreenToWorld(camera->view, InputManager::mousePos));
    bool f = false;

    editorMapRenderer->render();

    for (int i = 0; i < mapLimit.x * mapLimit.y; i++)
    {
        Vector2 pos = Utils::WorldToScreen(
            camera->view,
            tils->tiles[i]->cell * Vector2<int>(GameParameters::SIZE_TILE));
        if (pos.x <= GameParameters::SCREEN_WIDTH && pos.x >= 0 &&
            pos.y <= GameParameters::SCREEN_HEIGHT && pos.y >= 0)
        {
            tils->tiles[i]->button.Draw(*worldRenderer, *squareRenderer);
        }

        if (!f && ms == tils->tiles[i]->cell && !NewMap->isMouseHover() &&
            !buildPanel->isMouseHover(false) && !SaveLoad->isMouseHover() &&
            !envItemManager->isPressedOrHover() && !tilePropertiesPanel->isMouseHover(false))
        {
            f = true;
            Vector2<int> pos = Utils::CellToPosition(tils->tiles[i]->cell);
            squareRenderer->world_RenderEmptySquare(
                pos, Vector2<int>(GameParameters::SIZE_TILE), mouse_yellow,
                1.0F, 0, 4.0F);
        }
    }
    for (std::vector<int>::size_type i = 0; i < env_items.size(); i++)
    {
        env_items[i]->Render(*worldRenderer, *menuRenderer, *squareRenderer,
                             Timer::timeSinceSceneStart);
    }

    // ui
    this->buildPanel->Draw(*menuRenderer, *squareRenderer);

    this->NewMap->Render(*menuRenderer, *squareRenderer);

    this->tilePropertiesPanel->Draw(*menuRenderer, *squareRenderer);

    envItemManager->Draw(*menuRenderer, *squareRenderer);

    SaveLoad->Render(*menuRenderer, *squareRenderer);

    if (tils->tilesUI)
    {
        for (int i = 0; i < tileCount; i++)
        {
            if (selectedTile->GetID() == tils->tilesUI[i]->getTile().GetID())
            {
                tils->tilesUI[i]->Draw(*menuRenderer, *squareRenderer, 0.3F, true,
                                       Timer::timeSinceSceneStart);
            }
            else if (tils->tilesUI[i]->IsMouseHover())
            {
                tils->tilesUI[i]->Draw(*menuRenderer, *squareRenderer, 0.3F, false,
                                       Timer::timeSinceSceneStart);
            }
            else
            {
                tils->tilesUI[i]->Draw(*menuRenderer, *squareRenderer);
                int a = 2;
            }
        }
    }
    objects_ui->Draw(*squareRenderer);
    this->textRenderer->RenderText(
        "fps: " + std::to_string(InputManager::m_fps), Vector2(700, 135), 1.0F,
        Vector3<float>(0.5F));
}

void Editor::SelectedRbChanged(RadioButtonElement *old, RadioButtonElement *n)
{
    selectedTile->setType((TileTypes)n->getIndex());
}
