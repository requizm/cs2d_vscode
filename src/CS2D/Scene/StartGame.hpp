#ifndef SCENE_H
#define SCENE_H

#include <memory>

#include "../../Core/Model/Camera.hpp"
#include "../../Core/Renderer/SpriteRenderer.hpp"
#include "../../Core/Renderer/SquareRenderer.hpp"
#include "../../Core/Renderer/TextRenderer.hpp"
#include "../Model/Player.hpp"
#include "../../Core/Manager/ResourceManager.hpp"
#include "../Other/GameParameters.hpp"
#include "../../Core/Manager/Logger.hpp"
#include "../../Core/Manager/Utils.hpp"
#include "../../Core/Manager/InputManager.hpp"
#include "../Game.hpp"
#include "../../Core/Math/Vector2.hpp"
#include "../../Core/Math/Matrix4.hpp"

class StartGame
{
public:
	StartGame();
	~StartGame();

	void Initialize(const std::string &mapName);

	static StartGame &instance()
	{
		static StartGame INSTANCE;
		return INSTANCE;
	}

	void Start();
	void OnEnable();
	void OnDisable();
	void Update();
	void ProcessInput();
	void Render();

	void SetEnable(const bool value);

	Camera *camera;

	SquareRenderer squareRenderer;
	SpriteRenderer *renderer;

private:
	Map *map;
	Player *player;

	TextRenderer *textRenderer;
	std::vector<Weapon> weapons;
	bool enable = false;
};

#endif //SCENE_H