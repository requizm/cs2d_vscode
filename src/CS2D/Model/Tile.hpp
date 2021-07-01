#ifndef TILE_H
#define TILE_H

#include "../../Core/Collider/RectangleCollider.hpp"
#include "../../Core/Model/GameObject.hpp"

enum TileTypes
{
    WALL,
    OBSTACLE,
    FLOOR
};

class Tile : public GameObject
{
   public:
    Tile();
    Tile(Vector2<int> pos, const Sprite &sprite, Vector2<int> size,
         TileTypes type = TileTypes::WALL, int frame = -1);

    void setType(TileTypes type);
    TileTypes getType() const;

    RectangleCollider &getCollider();

    int frame;

   private:
    TileTypes type;
    RectangleCollider collider;

    SpriteRenderer spriteRenderer;
};

#endif