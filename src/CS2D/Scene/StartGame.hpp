#ifndef STARTGAME_H
#define STARTGAME_H

#include <memory>

#include "../../Core/Model/Camera.hpp"
#include "../../Core/Renderer/SquareRenderer.hpp"
#include "../../Core/Renderer/TextRenderer.hpp"
#include "../Model/Player.hpp"
#include "../Model/Scene.hpp"

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

    std::unique_ptr<Camera> camera;

    SquareRenderer squareRenderer;
    std::unique_ptr<SpriteRenderer> renderer;

   private:
    std::unique_ptr<Map> map;
    std::unique_ptr<Player> player;

    std::unique_ptr<TextRenderer> textRenderer;
    std::vector<Weapon> weapons;
};

#endif  // STARTGAME_H