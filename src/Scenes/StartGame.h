#ifndef SCENE_H
#define SCENE_H
#include <memory>
#include "../Models/Camera.h"
#include "../Renderers/SpriteRenderer.h"
#include "../Models/Player.h"
#include "../Managers/ResourceManager.h"

class StartGame
{
public:
	StartGame();
	StartGame(const Map &map, const SpriteRenderer &renderer);
	StartGame(const Map &map, const SpriteRenderer &renderer, const std::vector<Weapon> &weapons);
	//StartGame(Map* map, std::vector<std::shared_ptr<Weapon>>* weapons, SpriteRenderer* renderer, std::vector<GameObject*> gameobjects);
	//StartGame(Map* map, std::vector<std::shared_ptr<Weapon>>* weapons, SpriteRenderer* renderer);
	~StartGame();
	void Start();
	void OnEnable();
	void OnDisable();
	void Update(const float dt);
	void ProcessInput(const float dt);
	void Render(const float dt);
	
	void SetEnable(const bool value);
private:
	Map map;
	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera;
	SpriteRenderer renderer;
	std::vector<Weapon> weapons;
	bool enable;
};

#endif //SCENE_H