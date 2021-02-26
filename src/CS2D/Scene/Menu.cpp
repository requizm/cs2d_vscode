#include "Menu.hpp"
#if defined(WIN32) && defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

Menu::Menu() = default;

Menu::~Menu() { OnDisable(); }

void Menu::Start()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    this->menuRenderer = new SpriteRenderer(ResourceManager::GetShader("menu"));
    this->textRenderer = new TextRenderer(GameParameters::SCREEN_WIDTH,
                                          GameParameters::SCREEN_HEIGHT);
    this->textRenderer->Load(
        GameParameters::resDirectory + "fonts/liberationsans.ttf", 16);
    this->squareRenderer = new SquareRenderer(true);

    this->l_console = new Label(
        "Console", Vector2<int>(10, GameParameters::SCREEN_HEIGHT / 2 - 50),
        *textRenderer, 0.8F, Vector3<float>(0.55F));
    this->l_newgame = new Label(
        "New Game", Vector2<int>(10, GameParameters::SCREEN_HEIGHT / 2 - 20),
        *textRenderer, 1.0F, Vector3<float>(0.58F));
    l_newgame->addListenerDown(std::bind(&Menu::newGameLabel_click, this));
    this->l_options = new Label(
        "Options", Vector2<int>(10, GameParameters::SCREEN_HEIGHT / 2),
        *textRenderer, 1.0F, Vector3<float>(0.58F));
    l_options->addListenerDown(std::bind(&Menu::options_click, this));
    this->l_editor = new Label(
        "Editor", Vector2<int>(10, GameParameters::SCREEN_HEIGHT / 2 + 20),
        *textRenderer, 1.0F, Vector3<float>(0.58F));
    l_editor->addListenerDown(std::bind(&Menu::editor_click, this));

    this->optionsPanel =
        new Panel(Vector2<int>(GameParameters::SCREEN_WIDTH / 2 - 210.0F,
                               GameParameters::SCREEN_HEIGHT / 2 - 225.0F),
                  "Options", Vector2<int>(420, 450), *textRenderer, true, true,
                  1.0F, Vector3<float>(0.21F));
    this->optionsPanel->setMovable(true);

    this->t_test =
        new TextBox(Vector2<int>(optionsPanel->GetPosition().x + 20, optionsPanel->GetPosition().y + 20), *textRenderer, Vector2<int>(100, 20), optionsPanel,
                    true, 1.0F, Vector3<float>(0.58F));
    this->t_test->SetParentCenterPos();

    this->newPanel =
        new Panel(Vector2<int>(GameParameters::SCREEN_WIDTH / 2 - 210.0F,
                               GameParameters::SCREEN_HEIGHT / 2 - 225.0F),
                  "New Game", Vector2<int>(420, 450), *textRenderer, true, true,
                  1.0F, Vector3<float>(0.21F));
    this->newPanel->setMovable(true);

    this->mapsPanel =
        new Panel(Vector2<int>(newPanel->GetPosition().x + 100, newPanel->GetPosition().y + 100), "Maps", Vector2<int>(120, 200),
                  *textRenderer, newPanel, true, false, 1.0F, Vector3<float>(0.21F));
    this->mapsPanel->setMovable(false);
    this->mapsPanel->SetScrollable(true);
    this->mapsPanel->setOutline(true);
    this->mapsPanel->setOutlineColor(Vector3<float>(0.47F));
    this->mapNames = new ListItem(mapsPanel);

    this->t_mapName =
        new TextBox(Vector2<int>(newPanel->GetPosition().x + 100, newPanel->GetPosition().y + 320), *textRenderer,
                    Vector2<int>(120, 20), newPanel, true, 1.0F, Vector3<float>(0.58F));

    this->b_newGame = new TextButton(
        "Start", Vector2<int>(newPanel->GetPosition().x + 240, newPanel->GetPosition().y + 320), Vector2<int>(60, 20), *textRenderer, newPanel,
        Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F);
    this->b_newGame->setButtonClickColor(Vector3<float>(0.30F));
    this->b_newGame->setButtonHoverColor(Vector3<float>(0.30F));
    this->b_newGame->setTextHoverColor(Vector3<float>(0.58F));
    this->b_newGame->setTextClickColor(Vector3<float>(1.0F));
    this->b_newGame->setHaveOutline(true);
    this->b_newGame->setOutlineColor(Vector3<float>(1.0F));
    this->b_newGame->addListenerDown(std::bind(&Menu::newGame_click, this));

    std::function<void(TextButton *, TextButton *)> mapChange =
        std::bind(&Menu::selectedMapChange, this, std::placeholders::_1,
                  std::placeholders::_2);
    this->mapNames->AddListener(mapChange);
}

void Menu::Initialize(Sprite menuSprites[4])
{
    for (int i = 0; i < 4; i++)
    {
        this->menuSprites[i] = menuSprites[i];
    }
    this->SetEnable(true);
}

void Menu::OnEnable()
{
    this->Start();
    this->optionsPanel->SetEnable(false);
    this->mapsPanel->SetEnable(false);
}

void Menu::OnDisable()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    if (l_console != nullptr) delete l_console;
    l_console = nullptr;
    if (l_newgame != nullptr) delete l_newgame;
    l_newgame = nullptr;
    if (l_options != nullptr) delete l_options;
    l_options = nullptr;
    if (l_editor != nullptr) delete l_editor;
    l_editor = nullptr;

    if (t_test != nullptr) delete t_test;
    t_test = nullptr;
    if (optionsPanel != nullptr) delete optionsPanel;
    optionsPanel = nullptr;

    if (mapNames != nullptr) delete mapNames;
    mapNames = nullptr;

    if (t_mapName != nullptr) delete t_mapName;
    t_mapName = nullptr;
    if (b_newGame != nullptr) delete b_newGame;
    b_newGame = nullptr;
    if (mapsPanel != nullptr) delete mapsPanel;
    mapsPanel = nullptr;
    if (newPanel != nullptr) delete newPanel;
    newPanel = nullptr;

    if (textRenderer != nullptr) delete textRenderer;
    textRenderer = nullptr;
    if (menuRenderer != nullptr) delete menuRenderer;
    menuRenderer = nullptr;
    if (squareRenderer != nullptr) delete squareRenderer;
    squareRenderer = nullptr;
}

void Menu::SetEnable(const bool value)
{
    if (this->enable == value) return;
    this->enable = value;
    if (this->enable)
        OnEnable();
    else
        OnDisable();
}

void Menu::Update()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    if (gonnaDieForGame)
    {
        std::string mName = GameParameters::resDirectory + "levels/" +
                            t_mapName->getText() + ".xml";
        StartGame::instance().Initialize(mName);
        Game::SetGameState(GameState::INGAME);
        return;
    }
    if (gonnaDieForEditor)
    {
        Game::SetGameState(GameState::EDITOR);
        return;
    }
    l_options->Update();
    l_console->Update();
    l_editor->Update();
    l_newgame->Update();
    optionsPanel->Update();
    newPanel->Update();
    mapNames->Update();
}

void Menu::ProcessInput()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    l_options->ProcessInput();
    l_console->ProcessInput();
    l_editor->ProcessInput();
    l_newgame->ProcessInput();
    optionsPanel->ProcessInput();
    newPanel->ProcessInput();
    mapNames->ProcessInput();
}

void Menu::Render()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
            case 0:
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                menuRenderer->DrawSprite(
                    menuSprites[3], Vector2<int>(0),
                    Vector2<int>(GameParameters::SCREEN_WIDTH,
                                 GameParameters::SCREEN_HEIGHT));
                break;
        }
    }
    l_options->Draw();
    l_editor->Draw();
    l_console->Draw();
    l_newgame->Draw();
    optionsPanel->Draw(*menuRenderer, *squareRenderer);
    newPanel->Draw(*menuRenderer, *squareRenderer);
    mapNames->Draw(*squareRenderer);
}

void Menu::selectedMapChange(TextButton *old, TextButton *n)
{
    if (this->enable)
    {
        t_mapName->setText(n->getText());
    }
}

void Menu::newGame_click()
{
#if defined(WIN32) && defined(TRACY_ENABLE)
    ZoneScoped;
#endif
    if (this->enable)
    {
        gonnaDieForGame = true;
    }
}

void Menu::newGameLabel_click()
{
    if (this->enable)
    {
        mapNames->Clear();
        std::vector<std::string> maps = getMapNames();
        for (std::vector<int>::size_type i = 0; i != maps.size(); i++)
        {
            mapNames->AddItem(maps[i]);
        }
        newPanel->SetEnable(true);
    }
}

void Menu::options_click()
{
    if (this->enable)
    {
        optionsPanel->SetEnable(true);
    }
}

void Menu::editor_click()
{
    if (this->enable)
    {
        gonnaDieForEditor = true;
    }
}
