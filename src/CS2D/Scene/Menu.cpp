#include "Menu.hpp"

#include "../../Core/Manager/InputManager.hpp"
#include "../../Core/Manager/Logger.hpp"
#include "../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../Core/Manager/ResourceManager.hpp"
#include "../../Core/Manager/Utils.hpp"
#include "../Other/GameParameters.hpp"
#include "../Other/SceneManager.hpp"


#if defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

Menu::Menu() : Scene("Menu")
{
}

void Menu::Load()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
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
    this->l_options = new Label(
        "Options", Vector2<int>(10, GameParameters::SCREEN_HEIGHT / 2),
        *textRenderer, 1.0F, Vector3<float>(0.58F));
    this->l_editor = new Label(
        "Editor", Vector2<int>(10, GameParameters::SCREEN_HEIGHT / 2 + 20),
        *textRenderer, 1.0F, Vector3<float>(0.58F));

    this->optionsPanel =
        new Panel(Vector2<int>(GameParameters::SCREEN_WIDTH / 2 - 210.0F,
                               GameParameters::SCREEN_HEIGHT / 2 - 225.0F),
                  "Options", Vector2<int>(420, 450), *textRenderer, true, true,
                  1.0F, Vector3<float>(0.21F));
    this->optionsPanel->setMovable(true);

    this->t_test =
        new TextBox(Vector2<int>(20, 20), *textRenderer, Vector2<int>(100, 20),
                    true, 1.0F, Vector3<float>(0.58F));
    this->t_test->setParent(optionsPanel);
    this->t_test->setParentCenterPos();

    this->newPanel =
        new Panel(Vector2<int>(GameParameters::SCREEN_WIDTH / 2 - 210.0F,
                               GameParameters::SCREEN_HEIGHT / 2 - 225.0F),
                  "New Game", Vector2<int>(420, 450), *textRenderer, true, true,
                  1.0F, Vector3<float>(0.21F));
    this->newPanel->setMovable(true);

    this->mapsPanel =
        new Panel(Vector2<int>(100, 100), "Maps", Vector2<int>(120, 200),
                  *textRenderer, true, false, 1.0F, Vector3<float>(0.21F));
    this->mapsPanel->setMovable(false);
    this->mapsPanel->setScrollable(true);
    this->mapsPanel->setOutline(true);
    this->mapsPanel->setVisible(true);
    this->mapsPanel->setOutlineColor(Vector3<float>(0.47F));
    this->mapsPanel->setParent(newPanel, true);
    this->mapNames = new ListItem(mapsPanel);

    this->t_mapName =
        new TextBox(Vector2<int>(100, 320), *textRenderer,
                    Vector2<int>(120, 20), true, 1.0F, Vector3<float>(0.58F));
    this->t_mapName->setParent(newPanel, true);

    this->b_newGame = new TextButton(
        "Start", Vector2<int>(240, 320), Vector2<int>(60, 20), *textRenderer,
        Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F, true);
    this->b_newGame->setButtonClickColor(Vector3<float>(0.30F));
    this->b_newGame->setButtonHoverColor(Vector3<float>(0.30F));
    this->b_newGame->setTextHoverColor(Vector3<float>(0.58F));
    this->b_newGame->setTextClickColor(Vector3<float>(1.0F));
    this->b_newGame->setHaveOutline(true);
    this->b_newGame->setOutlineColor(Vector3<float>(1.0F));
    this->b_newGame->setParent(newPanel, true);
    this->b_newGame->addListenerDown(std::bind(&Menu::newGameBtnClick, this));

    std::function<void(TextButton *, TextButton *)> mapChange =
        std::bind(&Menu::selectedMapChange, this, std::placeholders::_1,
                  std::placeholders::_2);
    this->mapNames->AddListener(mapChange);

    this->optionsPanel->setEnable(false);
    this->mapsPanel->setEnable(false);
}

void Menu::Initialize(Sprite menuSprites[4])
{
    for (int i = 0; i < 4; i++)
    {
        this->menuSprites[i] = menuSprites[i];
    }
}

void Menu::Unload()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
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

void Menu::Update()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
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
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    l_options->ProcessInput();
    l_console->ProcessInput();
    l_editor->ProcessInput();
    l_newgame->ProcessInput();
    optionsPanel->ProcessInput();
    newPanel->ProcessInput();
    mapNames->ProcessInput();

    if (l_editor->isMouseDown())
    {
        SceneManager::instance().RequestLoadScene("Editor");
    }

    if (l_newgame->isMouseDown())
    {
#if defined(TRACY_ENABLE)
        ZoneScopedS(10);
#endif
        mapNames->Clear();
        std::vector<std::string> maps = Utils::GetFileNames(GameParameters::resDirectory + "levels");
        for (std::vector<int>::size_type i = 0; i != maps.size(); i++)
        {
            mapNames->AddItem(maps[i]);
        }
        newPanel->setEnable(true);
    }

    if (l_options->isMouseDown())
    {
        optionsPanel->setEnable(true);
    }
}

void Menu::Render()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
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
    // menuRenderer.DrawSprite(menuSprites["mouseSprite"],
    // Vector2<int>(InputManager::mousePos.x, InputManager::mousePos.y),
    // Vector2<int>(GameParameters::SCREEN_HEIGHT / 35,
    // GameParameters::SCREEN_HEIGHT / 35), 0.0F, true);
    l_options->Draw();
    l_editor->Draw();
    l_console->Draw();
    l_newgame->Draw();
    // button->Draw(*squareRenderer);
    optionsPanel->Draw(*menuRenderer, *squareRenderer);
    newPanel->Draw(*menuRenderer, *squareRenderer);
    mapNames->Draw(*squareRenderer);
    // t_test->Draw(menuRenderer, squareRenderer);
}

void Menu::selectedMapChange(TextButton *old, TextButton *n)
{
    t_mapName->setText(n->getText());
}

void Menu::newGameBtnClick()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    std::string mName = GameParameters::resDirectory + "levels/" +
                        t_mapName->getText() + ".xml";
    if (SceneManager::instance().params.empty())
    {
        SceneManager::instance().params.push_back(mName);
    }
    else
    {
        SceneManager::instance().params.at(0) = mName;
    }
    SceneManager::instance().RequestLoadScene("StartGame");
}
