#include "TestScene.hpp"

#include "../../../src/CS2D/Other/GameParameters.hpp"
#include "../../../src/CS2D/Other/SceneManager.hpp"
#include "../../../src/Core/Manager/InputManager.hpp"
#include "../../../src/Core/Manager/Logger.hpp"
#include "../../../src/Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../../src/Core/Manager/ResourceManager.hpp"
#include "../../../src/Core/Manager/Utils.hpp"


#if defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

TestScene::TestScene() : Scene("TestScene")
{
}

TestScene::~TestScene()
{
    Unload();
}

void TestScene::Load()
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

    this->batchRenderer = new BatchRenderer(true);

    this->batchRenderer->AddRectangle(Vector3<int>(100, 100, -0.7), Vector2<int>(50, 50), Vector3<float>(1.0F, 0.0F, 0.0F), 1.0F, 0);
    this->batchRenderer->AddRectangle(Vector3<int>(200, 200, -0.3), Vector2<int>(50, 50), Vector3<float>(0.0F, 1.0F, 0.0F), 1.0F, 0);
    this->batchRenderer->AddRectangle(Vector3<int>(300, 300, 0.3), Vector2<int>(50, 50), Vector3<float>(0.0F, 0.0F, 1.0F), 1.0F, 0);
    this->batchRenderer->AddRectangle(Vector3<int>(400, 400, 0.7), Vector2<int>(50, 50), Vector3<float>(1.0F, 1.0F, 1.0F), 1.0F, 0);
}

void TestScene::Initialize()
{
}

void TestScene::Unload()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif

    if (textRenderer != nullptr) delete textRenderer;
    textRenderer = nullptr;
    if (menuRenderer != nullptr) delete menuRenderer;
    menuRenderer = nullptr;
    if (squareRenderer != nullptr) delete squareRenderer;
    squareRenderer = nullptr;
    if (batchRenderer != nullptr) delete batchRenderer;
    batchRenderer = nullptr;
}

void TestScene::Update()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
}

void TestScene::ProcessInput()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
}

void TestScene::Render()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif

    squareRenderer->ui_RenderEmptySquare(Vector2<int>(300, 300), Vector2<int>(60, 20), Vector3<float>(1.0F), 1.0F, 0, 1.0F);
    this->batchRenderer->Draw();
}