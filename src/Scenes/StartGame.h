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
	StartGame(Map* map, SpriteRenderer* renderer);
	StartGame(Map* map, SpriteRenderer* renderer, std::vector<Weapon> weapons);
	//StartGame(Map* map, std::vector<std::shared_ptr<Weapon>>* weapons, SpriteRenderer* renderer, std::vector<GameObject*> gameobjects);
	//StartGame(Map* map, std::vector<std::shared_ptr<Weapon>>* weapons, SpriteRenderer* renderer);
	void Init();
	void Update(const float dt) const;
	void ProcessInput(const float dt);
	void Render(const float dt);
	~StartGame();

private:
	std::shared_ptr<Map> map;
	std::shared_ptr<Player> player;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<SpriteRenderer> renderer;
	std::vector<Weapon> weapons;
};

#endif //SCENE_H