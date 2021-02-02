#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include "Renderers/SpriteRenderer.hpp"
#include "Models/GameObject.hpp"
#include "Models/Map.hpp"
#include "Models/Camera.hpp"
#include "Models/Player.hpp"
#include <memory>
#include "Scenes/StartGame.hpp"
#include "Managers/ResourceManager.hpp"
#include "Others/Game_Parameters.hpp"
#include "Scenes/Menu.hpp"
#include "Scenes/Editor/Editor.hpp"

class Game
{
public:
	Game();
	~Game();

	void Init();
	void Update();
	void Render();
	void ProcessInput();
	void NewGame();

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