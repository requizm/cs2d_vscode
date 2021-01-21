#ifndef SCENE_H
#define SCENE_H
#include <memory>
#include "../Models/Camera.hpp"
#include "../Renderers/SpriteRenderer.hpp"
#include "../Renderers/TextRenderer.hpp"
#include "../Models/Player.hpp"
#include "../Managers/ResourceManager.hpp"

class StartGame
{
public:
	StartGame();
	~StartGame();

	void Initialize(const Map &map);

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

private:
	Map map;
	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera;
	SpriteRenderer renderer;
	std::shared_ptr<TextRenderer> textRenderer;
	std::vector<Weapon> weapons;
	bool enable = false;
};

#endif //SCENE_H