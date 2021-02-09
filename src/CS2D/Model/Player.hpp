#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../../Core/Manager/InputManager.hpp"
#include "../../Core/Manager/Logger.hpp"
#include "../../Core/Manager/Timer.hpp"
#include "../../Core/Model/GameObject.hpp"
#include "../../Core/Collider/CircleCollider.hpp"
#include "../../Core/Model/Camera.hpp"
#include "../../Core/Renderer/SquareRenderer.hpp"
#include "Tile.hpp"
#include "Map.hpp"
#include "Weapon.hpp"

#include "../Other/Game_Parameters.hpp"

enum MoveDirection
{
	TOP,
	BOTTOM,
	RIGHT,
	LEFT
};

class Player : public GameObject
{
public:
	Player() : health(0), maxHealth(0), map(nullptr), velocity(0)
	{
		this->objType = ObjectType::PLAYER;

		this->lastMousePos = Vector2(0, 0);
	}

	Player(const Vector2<int> pos, const std::vector<Sprite> &sprites, const Vector2<int> size = Vector2<int>(Game_Parameters::SIZE_TILE), int maxHealth = 100) : GameObject(pos, sprites[0], size, (int)ObjectType::PLAYER), map(nullptr), velocity(0.0F), collider(CircleCollider(this->GetPositionOfCenter(), static_cast<int>(static_cast<float>(Game_Parameters::SIZE_TILE / 2) * 0.8F)))
	{
		this->maxHealth = maxHealth;
		this->health = maxHealth;
		this->sprites = sprites;

		this->lastMousePos = Vector2(0, 0);
	}

	~Player();

	void setIndex(int index);
	void Draw(SpriteRenderer &renderer) override;
	void DrawModel(SpriteRenderer &renderer) override;
	void Update();
	void ProcessInput(Camera &cam, SpriteRenderer &r, SquareRenderer &s);
	void SetPosition(Vector2<int> pos) override;
	void SetPosition(Vector2<int> pos, Camera &cam, SpriteRenderer &r, SquareRenderer &s);
	void SetMap(Map *map);
	void setSelectFalse();
	void setVelocity(const int velocity);
	void takeDamage(const int value);

	void OnDestroy() override;
	void Destroy() override;

	int getVelocity() const;
	int getHealth() const;
	int getMaxHealth() const;

	CircleCollider collider; //FIXME: private olacak

private:
	int health;
	int maxHealth;
	int velocity;

	Map *map;

	Vector2<int> lastMousePos;

	int currentIndex = 0;
	std::vector<Sprite> sprites;

	void SlotInput();
	void ControllerInput(Camera &cam, SpriteRenderer &r, SquareRenderer &s);

	bool CheckCollision(Vector2<int> pos, MoveDirection direction);
};

#endif // PLAYER_H