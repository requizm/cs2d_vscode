#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>

#include <memory>

#include "../Core/Manager/ResourceManager.hpp"
#include "../Core/Model/Camera.hpp"
#include "../Core/Model/GameObject.hpp"
#include "../Core/Renderer/SpriteRenderer.hpp"
#include "Model/Map.hpp"
#include "Model/Player.hpp"
#include "Other/GameParameters.hpp"
#include "Scene/Editor/Editor.hpp"
#include "Scene/Menu.hpp"
#include "Scene/StartGame.hpp"


enum GameState { MENU, INGAME, EDITOR };

class Game {
   public:
    Game();
    ~Game();

    void Init();
    void Update();
    void Render();
    void ProcessInput();

    static void SetGameState(GameState state);
    static GameState GetGameState();

    static GameState state;

   private:
    SpriteRenderer spriteRenderer, menuRenderer;
    Camera camera;

    std::vector<Map> maps;
    std::vector<Weapon> weapons;

    Sprite mouseSprite;

    Sprite menuSprites[4];

    void initTextures() const;
    void initMaps();
    void initRenderers();
    void initShaders();
    void initMenuSprites();
};

#endif  // GAME_H