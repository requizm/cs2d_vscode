#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "../Renderers/SpriteRenderer.h"

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
	GameObject(Vector2<float> pos, const Sprite &sprite, Vector2<float> size, int objType = 2);
	virtual ~GameObject();

	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);
	virtual void DrawModel(SpriteRenderer &renderer);

	virtual void SetParent(GameObject *go);
	virtual void RemoveParent();

	void SetTransform(Matrix4<float> transform);

	void SetTransform(Vector2<float> pos, Vector2<float> size, GLfloat rot = 0.0f);
	void SetPosition(Vector2<float> pos);
	void SetPosition(const float x, const float y);
	void SetSize(Vector2<float> size);
	void SetRotation(GLfloat rot);
	void setCellPosition(int x, int y);
	void setCellPosition(Vector2<float> pos);
	void setID(int id);

	virtual void Destroy();
	virtual void OnDestroy();

	GameObject GetParentObject();
	int GetObjectType();
	Matrix4<float> GetTransform();
	Vector2<float> GetPosition();
	Vector2<float> GetPositionOfCenter();
	GLfloat GetRotation();
	Vector2<float> GetSize();
	int GetID() const;

	void BuildTransform();

	GLboolean IsCollision() const;
	GLboolean IsDestroyed() const;
	bool IsParent();

	Vector2<int> PositionToCell(Vector2<float> pos);
	Vector2<int> PositionToCell(float x, float y);

	Sprite sprite;

protected:
	// Object state
	Vector2<float> localPosition, localSize, Velocity2d;
	GLfloat localRotation;

	Vector2<float> globalPosition, globalSize;
	GLfloat globalRotation;

	glm::vec2 cellPos;

	Matrix4<float> localTransform = Matrix4(1.0f);
	Matrix4<float> globalTransform = Matrix4(1.0f);

	GameObject *parent = nullptr;

	GLboolean isCollision;
	GLboolean isDestroyed;

	ObjectType objType;

	Vector2<float> parentPositionDelta;

	int id;

private:
	std::string GetObjectTypeString();
};

#endif