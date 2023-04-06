#include "StartGame.hpp"

#include "../../Core/Manager/InputManager.hpp"
#include "../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../Core/Manager/ResourceManager.hpp"
#include "../../Core/Manager/Utils.hpp"
#include "../Other/GameParameters.hpp"
#include "../Other/SceneManager.hpp"


#if defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

StartGame::StartGame() : Scene("StartGame")
{
}

void StartGame::Initialize(const std::string &mapName)
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    this->map = std::make_unique<Map>(mapName, mapName);
    this->renderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
    this->camera = std::make_unique<Camera>(static_cast<int>(GameParameters::SCREEN_WIDTH),
                                            static_cast<int>(GameParameters::SCREEN_HEIGHT));
    this->textRenderer = std::make_unique<TextRenderer>(GameParameters::SCREEN_WIDTH,
                                                        GameParameters::SCREEN_HEIGHT);
    this->textRenderer->Load(
        GameParameters::resDirectory + "fonts/liberationsans.ttf", 20);
    this->squareRenderer = SquareRenderer(true);
}

void StartGame::Load()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    Initialize(SceneManager::instance().params.at(0));

    Sprite ct1_0 = Sprite(ResourceManager::GetTexture("ct1"), 0, 0, 32, 32);
    Sprite ct1_1 = Sprite(ResourceManager::GetTexture("ct1"), 0, 32, 32, 32);
    Sprite ct1_2 = Sprite(ResourceManager::GetTexture("ct1"), 0, 64, 32, 32);
    std::vector<Sprite> sprites;
    sprites.push_back(ct1_2);
    sprites.push_back(ct1_0);
    sprites.push_back(ct1_1);

    player = std::make_unique<Player>(Vector2<int>(70, 70), sprites);

    player->SetMap(map.get());
    player->SetPosition(Vector2<int>(GameParameters::SCREEN_WIDTH / 2,
                                     GameParameters::SCREEN_HEIGHT / 2));
    player->setVelocity(500);

    camera->setPosition(Vector2(
        player->GetPositionOfCenter().x - GameParameters::SCREEN_WIDTH / 2,
        player->GetPositionOfCenter().y - GameParameters::SCREEN_HEIGHT / 2));
    renderer->SetProjection(camera->cameraMatrix);
    squareRenderer.SetProjection(camera->cameraMatrix);
    player->Init();
}

void StartGame::Unload()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
}

void StartGame::Update()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    player->Update();
    // player->DoCollision(weapons);
}

void StartGame::ProcessInput()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    if (InputManager::isKeyDown(KeyboardKeys::KEY_ESCAPE))
    {
        SceneManager::instance().RequestLoadScene("Menu");
    }
    if (InputManager::isKeyDown(KeyboardKeys::KEY_Q))
    {
        // this->weapons.at(1).SetParent(player.get());
    }
    if (InputManager::isKeyDown(KeyboardKeys::KEY_E))
    {
        // this->weapons.at(1).RemoveParent();
    }
    player->ProcessInput();
}

void StartGame::Render()
{
#if defined(TRACY_ENABLE)
    ZoneScopedS(10);
#endif
    map->Draw(*renderer);
    player->DrawModel(*renderer);

    Vector2 p = Utils::ScreenToWorld(camera->view, InputManager::mousePos);
    this->textRenderer->RenderText(
        "mouse: " + std::to_string(p.x) + " - " + std::to_string(p.y),
        Vector2(700, 15), 1.0F, Vector3<float>(0.5F));
    this->textRenderer->RenderText(
        "player matrix: " + std::to_string(player->GetTransform().values[12]) +
            " - " + std::to_string(player->GetTransform().values[13]),
        Vector2(700, 45), 1.0F, Vector3<float>(0.5F));
    this->textRenderer->RenderText(
        "player pos: " + player->GetPosition().ToString(), Vector2(700, 75),
        1.0F, Vector3<float>(0.5F));
    this->textRenderer->RenderText(
        "player cell: " + player->GetCellPos().ToString(), Vector2(700, 105),
        1.0F, Vector3<float>(0.5F));
    this->textRenderer->RenderText(
        "fps: " + std::to_string(InputManager::m_fps), Vector2(700, 135), 1.0F,
        Vector3<float>(0.5F));

    squareRenderer.world_RenderEmptyCircle(
        player->collider.GetPosition(), Vector2<int>(player->collider.GetRadius()),
        Vector3<float>(0, 0, 0));
    // label->Draw(*textRenderer);

    // button->Draw(*squareRenderer, *buttonRenderer, *textRenderer);
}