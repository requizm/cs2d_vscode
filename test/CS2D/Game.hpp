#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>

#include <memory>

#include "../../src/Core/Model/Camera.hpp"
#include "../../src/Core/Renderer/SpriteRenderer.hpp"


class Game
{
   public:
    Game() = default;
    ~Game() = default;

    void Init();
    void Update();
    void Render();
    void ProcessInput();

   private:
    SpriteRenderer spriteRenderer, menuRenderer;
    Camera camera;

    Sprite mouseSprite;

    Sprite menuSprites[4];

    void initTextures() const;
    void initMaps();
    void initRenderers();
    void initShaders();
    void initMenuSprites();
};

#endif  // GAME_H