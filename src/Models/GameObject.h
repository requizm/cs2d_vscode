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
	GameObject(glm::vec2 pos, const Sprite &sprite, glm::vec2 size, int objType = 2);
	virtual ~GameObject();

	// Draw sprite
	virtual void Draw(SpriteRenderer &renderer);
	virtual void DrawModel(SpriteRenderer &renderer);

	virtual void SetParent(GameObject *go);
	virtual void RemoveParent();

	void SetTransform(glm::mat4 transform);

	void SetTransform(glm::vec2 pos, glm::vec2 size, GLfloat rot = 0.0f);
	void SetPosition(glm::vec2 pos);
	void SetPosition(const float x, const float y);
	void SetSize(glm::vec2 size);
	void SetRotation(GLfloat rot);
	void setCellPosition(int x, int y);
	void setCellPosition(glm::vec2 pos);

	virtual void Destroy();
	virtual void OnDestroy();

	GameObject GetParentObject();
	int GetObjectType();
	glm::mat4 GetTransform();
	glm::vec2 GetPosition();
	GLfloat GetRotation();
	glm::vec2 GetSize();

	void BuildTransform();

	GLboolean IsCollision() const;
	GLboolean IsDestroyed() const;
	bool IsParent();

	Sprite sprite;

protected:
	// Object state
	glm::vec2 localPosition, localSize, Velocity2d;
	GLfloat localRotation;

	glm::vec2 globalPosition, globalSize;
	GLfloat globalRotation;

	glm::vec2 cellPos;

	glm::mat4 localTransform = glm::mat4(1.0f);
	glm::mat4 globalTransform = glm::mat4(1.0f);

	GameObject *parent = nullptr;

	GLboolean isCollision;
	GLboolean isDestroyed;

	ObjectType objType;

	glm::vec2 parentPositionDelta;

private:
	std::string GetObjectTypeString();
};

#endif