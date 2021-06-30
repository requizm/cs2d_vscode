#ifndef STARTGAME_H
#define STARTGAME_H

#include <memory>

#include "../../Core/Manager/InputManager.hpp"
#include "../../Core/Manager/Logger.hpp"
#include "../../Core/Manager/MemoryOverride/MemoryOverride.hpp"
#include "../../Core/Manager/ResourceManager.hpp"
#include "../../Core/Manager/Utils.hpp"
#include "../../Core/Math/Matrix4.hpp"
#include "../../Core/Math/Vector2.hpp"
#include "../../Core/Model/Camera.hpp"
#include "../../Core/Renderer/SpriteRenderer.hpp"
#include "../../Core/Renderer/SquareRenderer.hpp"
#include "../../Core/Renderer/TextRenderer.hpp"

#include "../Model/Player.hpp"
#include "../Other/SceneManager.hpp"
#include "../Model/Scene.hpp"
#include "../Other/GameParameters.hpp"


class StartGame : public Scene
{
   public:
    StartGame();
    ~StartGame() = default;

    void Initialize(const std::string &mapName);

    void Load() final;
    void Unload() final;
    void Update() final;
    void ProcessInput() final;
    void Render() final;

    Camera *camera;

    SquareRenderer squareRenderer;
    SpriteRenderer *renderer;

   private:
    Map *map;
    Player *player;

    TextRenderer *textRenderer;
    std::vector<Weapon> weapons;
};

#endif  // STARTGAME_H