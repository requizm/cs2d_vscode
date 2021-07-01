#ifndef STARTGAME_H
#define STARTGAME_H

#include "../../Core/Model/Camera.hpp"
#include "../../Core/Renderer/SquareRenderer.hpp"
#include "../../Core/Renderer/TextRenderer.hpp"
#include "../Model/Player.hpp"


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