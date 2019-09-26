#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Tile.h"
#include "Map.h"
#include "Weapon.h"
#include "../Others/Game_Parameters.h"
#include <GLFW/glfw3.h>
#include <iostream>

class Player : public GameObject
{
public:
	Player() : health(0), maxHealth(0), map(nullptr), velocity(0)
	{
		this->objType = ObjectType::PLAYER;
	}

	Player(const glm::vec2 pos, const std::vector<Sprite> &sprites, const glm::vec2 size = glm::vec2(Game_Parameters::SCREEN_HEIGHT / 15, Game_Parameters::SCREEN_HEIGHT / 15), int maxHealth = 100) : GameObject(pos, sprites[0], size, (int)ObjectType::PLAYER), map(nullptr), velocity(0)
	{
		this->maxHealth = maxHealth;
		this->health = maxHealth;
		this->sprites = sprites;
	}

	~Player();

	void setIndex(int index);
	void Draw(SpriteRenderer &renderer) override;
	void DrawModel(SpriteRenderer &renderer) override;
	void Update(float dt);
	void ProcessInput(float dt);
	void SetMap(Map *map);
	void setSelectFalse();
	void setVelocity(const float velocity);
	void takeDamage(const int value);

	void OnDestroy() override;
	void Destroy() override;

	float getVelocity() const;
	int getHealth() const;
	int getMaxHealth() const;

private:
	int health;
	int maxHealth;
	float velocity;

	Map *map;

	int currentIndex = 0;
	std::vector<Sprite> sprites;

	void SlotInput();
	void ControllerInput(float dt);
};

#endif // !PLAYER_H