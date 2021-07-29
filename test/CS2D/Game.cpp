#include "Game.hpp"
#if defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

#include "../../src/CS2D/Other/GameParameters.hpp"
#include "../../src/CS2D/Other/SceneManager.hpp"
#include "../../src/Core/Manager/InputManager.hpp"
#include "../../src/Core/Manager/ResourceManager.hpp"
#include "../../src/Core/Math/Projection.hpp"
#include "Scene/TestScene.hpp"


void Game::Init()
{
    initTextures();
    initShaders();
    initRenderers();
    initMaps();
    initMenuSprites();

    TestScene *testScene = new TestScene();
    testScene->Initialize();
    SceneManager::instance().AddScene(testScene);

    SceneManager::instance().LoadScene("TestScene");
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

    // menuitems
    ResourceManager::LoadTexture(
        GameParameters::resDirectory + "textures/pointer.png", GL_TRUE,
        "pointer");
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
    mouseSprite = Sprite(ResourceManager::GetTexture("pointer"), 0, 0, 46, 46);
}

void Game::initMaps()
{
}

void Game::initRenderers()
{
    spriteRenderer = SpriteRenderer(ResourceManager::GetShader("sprite"));
    menuRenderer = SpriteRenderer(ResourceManager::GetShader("menu"));
}