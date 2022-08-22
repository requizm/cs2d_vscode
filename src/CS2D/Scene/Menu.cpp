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
    Initialize();
}

void Menu::Load()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    this->menuRenderer = std::unique_ptr<SpriteRenderer>(new SpriteRenderer(ResourceManager::GetShader("menu")));
    this->textRenderer = std::unique_ptr<TextRenderer>(new TextRenderer(GameParameters::SCREEN_WIDTH,
                                          GameParameters::SCREEN_HEIGHT));
    this->textRenderer->Load(
        GameParameters::resDirectory + "fonts/liberationsans.ttf", 16);
    this->squareRenderer = std::unique_ptr<SquareRenderer>(new SquareRenderer(true));

    this->l_console = std::unique_ptr<Label>(new Label(
        "Console", Vector2<int>(10, GameParameters::SCREEN_HEIGHT / 2 - 50),
        *textRenderer, 0.8F, Vector3<float>(0.55F)));
    this->l_newgame = std::unique_ptr<Label>(new Label(
        "New Game", Vector2<int>(10, GameParameters::SCREEN_HEIGHT / 2 - 20),
        *textRenderer, 1.0F, Vector3<float>(0.58F)));
    this->l_options = std::unique_ptr<Label>(new Label(
        "Options", Vector2<int>(10, GameParameters::SCREEN_HEIGHT / 2),
        *textRenderer, 1.0F, Vector3<float>(0.58F)));
    this->l_editor = std::unique_ptr<Label>(new Label(
        "Editor", Vector2<int>(10, GameParameters::SCREEN_HEIGHT / 2 + 20),
        *textRenderer, 1.0F, Vector3<float>(0.58F)));

    this->optionsPanel =
        std::unique_ptr<Panel>(new Panel(Vector2<int>(GameParameters::SCREEN_WIDTH / 2 - 210.0F,
                               GameParameters::SCREEN_HEIGHT / 2 - 225.0F),
                  "Options", Vector2<int>(420, 450), *textRenderer, true, true,
                  1.0F, Vector3<float>(0.21F)));
    this->optionsPanel->setMovable(true);

    this->t_test =
        std::unique_ptr<TextBox>(new TextBox(Vector2<int>(20, 20), *textRenderer, Vector2<int>(100, 20),
                    true, 1.0F, Vector3<float>(0.58F)));
    this->t_test->setParent(optionsPanel.get());
    this->t_test->setParentCenterPos();

    this->newPanel =
        std::unique_ptr<Panel>(new Panel(Vector2<int>(GameParameters::SCREEN_WIDTH / 2 - 210.0F,
                               GameParameters::SCREEN_HEIGHT / 2 - 225.0F),
                  "New Game", Vector2<int>(420, 450), *textRenderer, true, true,
                  1.0F, Vector3<float>(0.21F)));
    this->newPanel->setMovable(true);

    this->mapsPanel =
        std::unique_ptr<Panel>(new Panel(Vector2<int>(100, 100), "Maps", Vector2<int>(120, 200),
                  *textRenderer, true, false, 1.0F, Vector3<float>(0.21F)));
    this->mapsPanel->setMovable(false);
    this->mapsPanel->setScrollable(true);
    this->mapsPanel->setOutline(true);
    this->mapsPanel->setVisible(true);
    this->mapsPanel->setOutlineColor(Vector3<float>(0.47F));
    this->mapsPanel->setParent(newPanel.get(), true);
    this->mapNames = std::unique_ptr<ListItem>(new ListItem(mapsPanel.get()));

    this->t_mapName =
        std::unique_ptr<TextBox>(new TextBox(Vector2<int>(100, 320), *textRenderer,
                    Vector2<int>(120, 20), true, 1.0F, Vector3<float>(0.58F)));
    this->t_mapName->setParent(newPanel.get(), true);

    this->b_newGame = std::unique_ptr<TextButton>(new TextButton(
        "Start", Vector2<int>(240, 320), Vector2<int>(60, 20), *textRenderer,
        Vector3<float>(0.15F), Vector3<float>(0.58F), 1.0F, true));
    this->b_newGame->setButtonClickColor(Vector3<float>(0.30F));
    this->b_newGame->setButtonHoverColor(Vector3<float>(0.30F));
    this->b_newGame->setTextHoverColor(Vector3<float>(0.58F));
    this->b_newGame->setTextClickColor(Vector3<float>(1.0F));
    this->b_newGame->setHaveOutline(true);
    this->b_newGame->setOutlineColor(Vector3<float>(1.0F));
    this->b_newGame->setParent(newPanel.get(), true);
    this->b_newGame->addListenerDown(std::bind(&Menu::newGameBtnClick, this));

    std::function<void(TextButton *, TextButton *)> mapChange =
        std::bind(&Menu::selectedMapChange, this, std::placeholders::_1,
                  std::placeholders::_2);
    this->mapNames->AddListener(mapChange);

    this->optionsPanel->setEnable(false);
    this->mapsPanel->setEnable(false);
}

void Menu::Initialize()
{
    Sprite cs2d = Sprite(ResourceManager::GetTexture("cs2d"));
    Sprite unrealsoftware =
        Sprite(ResourceManager::GetTexture("unrealsoftware"));
    Sprite splash = Sprite(ResourceManager::GetTexture("splash"));
    Sprite gametitle = Sprite(ResourceManager::GetTexture("gametitle"));
    menuSprites[0] = unrealsoftware;
    menuSprites[1] = cs2d;
    menuSprites[2] = gametitle;
    menuSprites[3] = splash;
}

void Menu::Unload()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
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
