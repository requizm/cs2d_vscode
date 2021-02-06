#include "Game.hpp"



GameState Game::state;

Game::Game()
{
    Game::state = GameState::MENU;
}

Game::~Game() = default;

void Game::Init()
{
    initTextures();
    initShaders();
    initRenderers();
    initMaps();
    initMenuSprites();
    Menu::instance().Initialize(menuSprites);
    Editor::instance().Initialize();
    NewGame();
}

void Game::Update()
{
    switch (Game::state)
    {
    case GameState::MENU:
        Menu::instance().Update();
        break;
    case GameState::EDITOR:
        Editor::instance().Update();
        break;
    case GameState::INGAME:
        StartGame::instance().Update();
        break;
    }
}

void Game::ProcessInput()
{
    switch (Game::state)
    {
    case GameState::MENU:
        Menu::instance().ProcessInput();
        break;
    case GameState::EDITOR:
        Editor::instance().ProcessInput();
        break;
    case GameState::INGAME:
        StartGame::instance().ProcessInput();
        break;
    }
}

void Game::Render()
{
    switch (Game::state)
    {
    case GameState::MENU:
        Menu::instance().Render();
        break;
    case GameState::EDITOR:
        Editor::instance().Render();
        break;
    case GameState::INGAME:
        StartGame::instance().Render();
        break;
    }
    menuRenderer.DrawSprite(mouseSprite, InputManager::mousePos,
                            Vector2<int>(Game_Parameters::SCREEN_HEIGHT / 35, Game_Parameters::SCREEN_HEIGHT / 35), 0,
                            true);
}

void Game::NewGame()
{
    Sprite awp = Sprite(ResourceManager::GetTexture("awp"));
    Sprite awp_d = Sprite(ResourceManager::GetTexture("awp_d"));
    Sprite famas = Sprite(ResourceManager::GetTexture("famas"));
    Sprite famas_d = Sprite(ResourceManager::GetTexture("famas_d"));
    Sprite ak47 = Sprite(ResourceManager::GetTexture("ak47"));
    Sprite ak47_d = Sprite(ResourceManager::GetTexture("ak47_d"));
    /*Sprite deagle = Sprite(ResourceManager::GetTexture("deagle"));
    Sprite deagle_d = Sprite(ResourceManager::GetTexture("deagle_d"));
    Sprite usp = Sprite(ResourceManager::GetTexture("usp"));
    Sprite usp_d = Sprite(ResourceManager::GetTexture("usp_d"));
    Sprite fiveseven = Sprite(ResourceManager::GetTexture("fiveseven"));
    Sprite fiveseven_d = Sprite(ResourceManager::GetTexture("fiveseven_d"));
    Sprite glock = Sprite(ResourceManager::GetTexture("glock"));
    Sprite glock_d = Sprite(ResourceManager::GetTexture("glock_d"));
    Sprite knife = Sprite(ResourceManager::GetTexture("knife"));
    Sprite machete = Sprite(ResourceManager::GetTexture("machete"));*/

    std::shared_ptr<Weapon> main1 = std::make_shared<Weapon>(
        Vector2<int>(65, 65), awp, awp_d, "awp", WeaponType::MAIN, 30, 20, 10, 10);
    std::shared_ptr<Weapon> main2 = std::make_shared<Weapon>(
        Vector2<int>(10, 10), famas, famas_d, "famas", WeaponType::MAIN, 30, 20, 10, 10);
    std::shared_ptr<Weapon> main3 = std::make_shared<Weapon>(
        Vector2<int>(12, 20), ak47, ak47_d, "ak47", WeaponType::MAIN, 30, 20, 10, 10);
    /*Weapon* pistol1 = new Weapon(
        Vector2<int>(170.0f, 30.0f), deagle, deagle_d, "deagle", WeaponType::PISTOL, 30, 20, 10, 10
    );
    Weapon* pistol2 = new Weapon(
        Vector2<int>(260.0f, 30.0f), usp, usp_d, "usp", WeaponType::PISTOL, 30, 20, 10, 10
    );
    Weapon* pistol3 = new Weapon(
        Vector2<int>(320.0f, 30.0f), fiveseven, fiveseven_d, "fiveseven", WeaponType::PISTOL, 30, 20, 10, 10
    );
    Weapon* pistol4 = new Weapon(
        Vector2<int>(20.0f, 90.0f), glock, glock_d, "glock", WeaponType::PISTOL, 30, 20, 10, 10
    );

    Weapon* knife1 = new Weapon(
        Vector2<int>(20.0f, 150.0f), knife, knife, "knife", WeaponType::KNIFE, 30, 20, 10, 10
    );
    Weapon* knife2 = new Weapon(
        Vector2<int>(20.0f, 210.0f), machete, machete, "machete", WeaponType::KNIFE, 30, 20, 10, 10
    );*/

    weapons.push_back(*main1.get());
    weapons.push_back(*main2.get());
    weapons.push_back(*main3.get());
}

void Game::initTextures() const
{
    //tiles
    ResourceManager::LoadTexture("../../resources/textures/tiles/cs2dnorm.png", GL_TRUE, "cs2dnorm");

    //weapons
    ResourceManager::LoadTexture("../../resources/textures/player/ct1.png", GL_TRUE, "ct1");
    ResourceManager::LoadTexture("../../resources/textures/weapons/awp.png", GL_TRUE, "awp");
    ResourceManager::LoadTexture("../../resources/textures/weapons/awp_d.png", GL_TRUE, "awp_d");
    ResourceManager::LoadTexture("../../resources/textures/weapons/ak47.png", GL_TRUE, "ak47");
    ResourceManager::LoadTexture("../../resources/textures/weapons/ak47_d.png", GL_TRUE, "ak47_d");
    ResourceManager::LoadTexture("../../resources/textures/weapons/famas.png", GL_TRUE, "famas");
    ResourceManager::LoadTexture("../../resources/textures/weapons/famas_d.png", GL_TRUE, "famas_d");
    ResourceManager::LoadTexture("../../resources/textures/bulb.png", GL_TRUE, "bulb");
    /*ResourceManager::LoadTexture("../../resources/textures/weapons/deagle.png", GL_TRUE, "deagle");
    ResourceManager::LoadTexture("../../resources/textures/weapons/deagle_d.png", GL_TRUE, "deagle_d");
    ResourceManager::LoadTexture("../../resources/textures/weapons/fiveseven.png", GL_TRUE, "fiveseven");
    ResourceManager::LoadTexture("../../resources/textures/weapons/fiveseven_d.png", GL_TRUE, "fiveseven_d");
    ResourceManager::LoadTexture("../../resources/textures/weapons/elite.png", GL_TRUE, "elite");
    ResourceManager::LoadTexture("../../resources/textures/weapons/elite_d.png", GL_TRUE, "elite_d");
    ResourceManager::LoadTexture("../../resources/textures/weapons/usp.png", GL_TRUE, "usp");
    ResourceManager::LoadTexture("../../resources/textures/weapons/usp_d.png", GL_TRUE, "usp_d");
    ResourceManager::LoadTexture("../../resources/textures/weapons/knife.png", GL_TRUE, "knife");
    ResourceManager::LoadTexture("../../resources/textures/weapons/machete.png", GL_TRUE, "machete");*/

    //menuitems
    ResourceManager::LoadTexture("../../resources/textures/pointer.png", GL_TRUE, "pointer");
    ResourceManager::LoadTexture("../../resources/textures/cs2d.png", GL_TRUE, "cs2d");
    ResourceManager::LoadTexture("../../resources/textures/gametitle.png", GL_TRUE, "gametitle");
    ResourceManager::LoadTexture("../../resources/textures/unrealsoftware.png", GL_TRUE, "unrealsoftware");
    ResourceManager::LoadTexture("../../resources/textures/splash.png", GL_FALSE, "splash");
    ResourceManager::LoadTexture("../../resources/textures/cursor-spec.png", GL_TRUE, "textcursor");

    //GUIIcons
    ResourceManager::LoadTexture("../../resources/textures/gui_icons.png", GL_TRUE, "gui_icons");
}

void Game::initShaders()
{
    ResourceManager::LoadShader("../../resources/shaders/textVertex.txt", "../../resources/shaders/textFragment.txt",
                                nullptr, "text");
    ResourceManager::LoadShader("../../resources/shaders/spriteVertex.txt",
                                "../../resources/shaders/spriteFragment.txt", nullptr, "sprite");
    ResourceManager::LoadShader("../../resources/shaders/spriteVertex.txt",
                                "../../resources/shaders/spriteFragment.txt", nullptr, "menu");

    ResourceManager::GetShader("sprite").Use();
    ResourceManager::GetShader("sprite").SetInteger("image", 0);
    ResourceManager::GetShader("sprite").UnUse();
    //Matrix4 za = Projection::ortho(0.0f, static_cast<GLfloat>(Game_Parameters::SCREEN_WIDTH), static_cast<GLfloat>(Game_Parameters::SCREEN_HEIGHT), 0.0f);
    ResourceManager::GetShader("menu").Use();
    ResourceManager::GetShader("menu").SetMatrix4("projection", Projection::ortho(0.0f, static_cast<float>(Game_Parameters::SCREEN_WIDTH), static_cast<float>(Game_Parameters::SCREEN_HEIGHT), 0.0f), GL_TRUE);
    ResourceManager::GetShader("menu").SetInteger("image", 0);
    ResourceManager::GetShader("menu").UnUse();
}

void Game::initMenuSprites()
{
    Sprite cs2d = Sprite(ResourceManager::GetTexture("cs2d"));
    Sprite unrealsoftware = Sprite(ResourceManager::GetTexture("unrealsoftware"));
    Sprite splash = Sprite(ResourceManager::GetTexture("splash"));
    Sprite gametitle = Sprite(ResourceManager::GetTexture("gametitle"));
    mouseSprite = Sprite(ResourceManager::GetTexture("pointer"), 0, 0, 46, 46);
    menuSprites[0] = unrealsoftware;
    menuSprites[1] = cs2d;
    menuSprites[2] = gametitle;
    menuSprites[3] = splash;
}

void Game::initMaps()
{
    //maps = std::vector<Map>();
    //const Map test_map = Map("../../resources/levels/hadiyav.xml", "test_one");
    //maps.push_back(test_map);
}

void Game::initRenderers()
{
    spriteRenderer = SpriteRenderer(ResourceManager::GetShader("sprite"));
    menuRenderer = SpriteRenderer(ResourceManager::GetShader("menu"));
}

void Game::SetGameState(GameState state)
{
    switch (Game::state)
    {
    case GameState::MENU:
        Menu::instance().SetEnable(false);
        break;
    case GameState::EDITOR:
        Editor::instance().SetEnable(false);
        break;
    case GameState::INGAME:
        StartGame::instance().SetEnable(false);
        break;
    }

    switch (state)
    {
    case GameState::MENU:
        Menu::instance().SetEnable(true);
        break;
    case GameState::EDITOR:
        Editor::instance().SetEnable(true);
        break;
    case GameState::INGAME:
        StartGame::instance().SetEnable(true);
        break;
    }
    Game::state = state;
}

GameState Game::GetGameState()
{
    return Game::state;
}