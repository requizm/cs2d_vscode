#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Tile.h"
#include "Map.h"
#include "Weapon.h"
#include "../Others/Game_Parameters.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Player : public GameObject
{
public:
	Player() : health(0), maxHealth(0), map(nullptr), velocity(0.0F)
	{
		this->objType = ObjectType::PLAYER;

		this->lastMousePos = Vector2(0.0F, 0.0F);
	}

	Player(const Vector2<float> pos, const std::vector<Sprite> &sprites, const Vector2<float> size = Vector2<float>(Game_Parameters::SCREEN_HEIGHT / 15, Game_Parameters::SCREEN_HEIGHT / 15), int maxHealth = 100) : GameObject(pos, sprites[0], size, (int)ObjectType::PLAYER), map(nullptr), velocity(0.0F)
	{
		this->maxHealth = maxHealth;
		this->health = maxHealth;
		this->sprites = sprites;

		this->lastMousePos = Vector2(0.0F, 0.0F);
	}

	~Player();

	void setIndex(int index);
	void Draw(SpriteRenderer &renderer) override;
	void DrawModel(SpriteRenderer &renderer) override;
	void Update();
	void ProcessInput();
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

	Vector2<float> lastMousePos;

	int currentIndex = 0;
	std::vector<Sprite> sprites;

	void SlotInput();
	void ControllerInput();
};

#endif // !PLAYER_H