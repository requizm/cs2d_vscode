#include "Game.hpp"
#if defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

#include "../Core/Manager/InputManager.hpp"
#include "../Core/Manager/ResourceManager.hpp"
#include "../Core/Math/Projection.hpp"
#include "Other/SceneManager.hpp"
#include "Scene/Editor/Editor.hpp"
#include "Scene/Menu.hpp"
#include "Scene/StartGame.hpp"


void Game::Init()
{
    initTextures();
    initShaders();
    initRenderers();
    initMaps();
    initMenuSprites();

    SceneManager::instance().scenes["Menu"] = []() { return new Menu(); };
    SceneManager::instance().scenes["StartGame"] = []() { return new StartGame(); };
    SceneManager::instance().scenes["Editor"] = []() { return new Editor(); };

    SceneManager::instance().LoadScene("Menu");
}

void Game::Update()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    SceneManager::instance().GetActiveScene<Scene>()->Update();
}

void Game::ProcessInput()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    SceneManager::instance().GetActiveScene<Scene>()->ProcessInput();
}

void Game::Render()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    SceneManager::instance().GetActiveScene<Scene>()->Render();
    Vector2<int> mouseSize = Vector2<int>(GameParameters::SCREEN_HEIGHT / 35,
                                          GameParameters::SCREEN_HEIGHT / 35);
    menuRenderer.DrawSprite(mouseSprite, InputManager::mousePos, mouseSize, 0, true);

    SceneManager::instance().LoadNextScene();
}

void Game::initTextures() const
{
    // tiles
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/tiles/cs2dnorm.png", GL_TRUE,
        "cs2dnorm");

    // weapons
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/player/ct1.png", GL_TRUE,
        "ct1");
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/weapons/awp.png", GL_TRUE,
        "awp");
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/weapons/awp_d.png", GL_TRUE,
        "awp_d");
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/weapons/famas.png", GL_TRUE,
        "famas");
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/weapons/famas_d.png", GL_TRUE,
        "famas_d");
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/bulb.png", GL_TRUE, "bulb");
    /*ResourceManager::LoadTexture(GameParameters::resDirectory +
    "textures/weapons/fiveseven.png", GL_TRUE, "fiveseven");
    ResourceManager::LoadTexture(GameParameters::resDirectory +
    "textures/weapons/fiveseven_d.png", GL_TRUE, "fiveseven_d");
    ResourceManager::LoadTexture(GameParameters::resDirectory +
    "textures/weapons/elite.png", GL_TRUE, "elite");
    ResourceManager::LoadTexture(GameParameters::resDirectory +
    "textures/weapons/elite_d.png", GL_TRUE, "elite_d");
    ResourceManager::LoadTexture(GameParameters::resDirectory +
    "textures/weapons/usp.png", GL_TRUE, "usp");
    ResourceManager::LoadTexture(GameParameters::resDirectory +
    "textures/weapons/usp_d.png", GL_TRUE, "usp_d");
    ResourceManager::LoadTexture(GameParameters::resDirectory +
    "textures/weapons/knife.png", GL_TRUE, "knife");
    ResourceManager::LoadTexture(GameParameters::resDirectory +
    "textures/weapons/machete.png", GL_TRUE, "machete");*/

    // menuitems
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/pointer.png", GL_TRUE,
        "pointer");
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/cs2d.png", GL_TRUE, "cs2d");
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/gametitle.png", GL_TRUE,
        "gametitle");
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/unrealsoftware.png", GL_TRUE,
        "unrealsoftware");
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/splash.png", GL_FALSE,
        "splash");
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/cursor-spec.png", GL_TRUE,
        "textcursor");

    // GUIIcons
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/gui_icons.png", GL_TRUE,
        "gui_icons");
}

void Game::initShaders()
{
    ResourceManager::LoadShader(
        GameParameters::resDirectory + "shaders/textVertex.txt",
        GameParameters::resDirectory + "shaders/textFragment.txt", "", "text");
    ResourceManager::LoadShader(
        GameParameters::resDirectory + "shaders/spriteVertex.txt",
        GameParameters::resDirectory + "shaders/spriteFragment.txt", "",
        "sprite");
    ResourceManager::LoadShader(
        GameParameters::resDirectory + "shaders/spriteVertex.txt",
        GameParameters::resDirectory + "shaders/spriteFragment.txt", "",
        "menu");

    ResourceManager::GetShader("sprite").Use();
    ResourceManager::GetShader("sprite").SetInteger("image", 0);
    ResourceManager::GetShader("sprite").UnUse();
    ResourceManager::GetShader("menu").Use();
    ResourceManager::GetShader("menu").SetMatrix4(
        "projection",
        Projection::ortho(
            0.0f, static_cast<float>(GameParameters::SCREEN_WIDTH),
            static_cast<float>(GameParameters::SCREEN_HEIGHT), 0.0f),
        GL_TRUE);
    ResourceManager::GetShader("menu").SetInteger("image", 0);
    ResourceManager::GetShader("menu").UnUse();
}

void Game::initMenuSprites()
{
    Sprite cs2d = Sprite(ResourceManager::GetTexture("cs2d"));
    Sprite unrealsoftware =
        Sprite(ResourceManager::GetTexture("unrealsoftware"));
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
    // maps = std::vector<Map>();
    // const Map test_map = Map(GameParameters::resDirectory +
    // "levels/hadiyav.xml", "test_one"); maps.push_back(test_map);
}

void Game::initRenderers()
{
    spriteRenderer = SpriteRenderer(ResourceManager::GetShader("sprite"));
    menuRenderer = SpriteRenderer(ResourceManager::GetShader("menu"));
}