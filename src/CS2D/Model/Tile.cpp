#include "Tile.hpp"

Tile::Tile() : type(TileTypes::FLOOR), frame(-1), GameObject() {}

Tile::Tile(const Vector2<int> &pos, const Sprite &sprite, const Vector2<int> &size,
           TileTypes type, int frame)
    : GameObject(pos, sprite, size, ObjectType::TILE),
      type(type),
      frame(frame),
      collider(RectangleCollider(pos, size))
{
}

void Tile::setType(const TileTypes type) { this->type = type; }

TileTypes Tile::getType() const { return this->type; }

RectangleCollider &Tile::getCollider() { return this->collider; }