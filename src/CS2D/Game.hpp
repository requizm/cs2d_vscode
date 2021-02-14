#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <memory>

#include "../Core/Renderer/SpriteRenderer.hpp"
#include "../Core/Model/GameObject.hpp"
#include "Model/Map.hpp"
#include "../Core/Model/Camera.hpp"
#include "Model/Player.hpp"
#include "Scene/StartGame.hpp"
#include "../Core/Manager/ResourceManager.hpp"
#include "Other/GameParameters.hpp"
#include "Scene/Menu.hpp"
#include "Scene/Editor/Editor.hpp"

enum GameState
{
    MENU,
    INGAME,
    EDITOR
};

class Game
{
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

#endif // GAME_H