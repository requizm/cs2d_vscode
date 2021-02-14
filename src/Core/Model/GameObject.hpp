#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>

#include "../Renderer/SpriteRenderer.hpp"
#include "../Manager/Logger.hpp"
#include "../../CS2D/Other/GameParameters.hpp"
#include "../Manager/Utils.hpp"

enum class ObjectType
{
	PLAYER,
	WEAPON,
	GAMEOBJECT,
	TILE
};

class GameObject
{
public:
	GameObject();

	/**
	 * @brief Construct a new Game Object object
	 * 
	 * @param pos 
	 * @param sprite 
	 * @param size 
	 * @param objType 2(ObjectType::GAMEOBJECT)
	 */
	GameObject(Vector2<int> pos, const Sprite &sprite, Vector2<int> size, int objType = 2);
	virtual ~GameObject();

	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);
	virtual void DrawModel(SpriteRenderer &renderer);

	virtual void SetParent(GameObject *go);
	virtual void RemoveParent();

	void SetTransform(const Matrix4<float> &transform);

	void SetTransform(Vector2<int> pos, Vector2<int> size, int rot = 0);
	virtual void SetPosition(Vector2<int> pos, bool changeCell = true);
	virtual void SetPosition(const int x, const int y, bool changeCell = true);
	void SetSize(Vector2<int> size);
	void SetRotation(int rot);
	void setCellPosition(int x, int y, bool changeCell = true);
	void setCellPosition(Vector2<int> pos, bool changeCell = true);
	void setID(int id);

	virtual void Destroy();
	virtual void OnDestroy();

	GameObject *GetParent();
	int GetObjectType();
	Matrix4<float> GetTransform();
	Vector2<int> GetPosition();
	Vector2<int> GetPositionOfCenter();
	int GetRotation();
	Vector2<int> GetSize();
	int GetID() const;
	virtual Vector2<int> GetCellPos();

	void BuildTransform();

	GLboolean IsCollision() const;
	GLboolean IsDestroyed() const;
	bool IsParent();

	Sprite sprite;

protected:
	Vector2<int> cellPos;

	Vector2<int> localPosition, localSize, Velocity2d;
	int localRotation;

	Vector2<int> globalPosition, globalSize;
	int globalRotation;

	Matrix4<float> localTransform = Matrix4(1.0f);
	Matrix4<float> globalTransform = Matrix4(1.0f);

	GameObject *parent = nullptr;

	GLboolean isCollision;
	GLboolean isDestroyed;

	ObjectType objType;

	Vector2<int> parentPositionDelta;

	int id;

private:
	std::string GetObjectTypeString();
};

#endif