#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>

#include "../../CS2D/Other/GameParameters.hpp"
#include "../Manager/Logger.hpp"
#include "../Manager/Utils.hpp"
#include "../Renderer/SpriteRenderer.hpp"
#include "Object.hpp"


enum class ObjectType
{
    PLAYER,
    WEAPON,
    GAMEOBJECT,
    TILE
};

class GameObject : public Object
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
    GameObject(const Vector2<int> &pos, const Sprite &spr, const Vector2<int> &size,
               ObjectType type = ObjectType::GAMEOBJECT);
    virtual ~GameObject();

    virtual void DrawModel(SpriteRenderer &renderer);

    virtual void SetParent(GameObject *go);
    virtual void RemoveParent();


    void SetTransform(const Vector2<int> &pos, const Vector2<int> &size, int rot = 0);
    virtual void SetPosition(const Vector2<int> &pos, bool changeCell = true);
    void setCellPosition(const Vector2<int> &pos, bool changeCell = true);


    ObjectType GetObjectType();
    
    virtual Vector2<int> GetCellPos();

    GLboolean IsCollision() const;
    bool IsParent();

    Sprite sprite;

   protected:
    Vector2<int> cellPos;
    GLboolean isCollision;
    ObjectType objType;

   private:
    std::string GetObjectTypeString();
};

#endif