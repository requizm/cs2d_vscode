#include "Tile.hpp"

Tile::Tile() : type(TileTypes::FLOOR), frame(-1), GameObject() {}

Tile::Tile(Vector2<int> pos, const Sprite &sprite, Vector2<int> size,
           TileTypes type, int frame)
    : GameObject(pos, sprite, size, (int)ObjectType::TILE),
      type(type),
      frame(frame),
      collider(RectangleCollider(pos, size)) {}

Tile::Tile(Vector2<int> pos, const Sprite &sprite, Vector2<int> size)
    : GameObject(pos, sprite, size, (int)ObjectType::TILE),
      type(TileTypes::FLOOR),
      frame(-1) {}

void Tile::setType(const TileTypes type) { this->type = type; }

TileTypes Tile::getType() const { return this->type; }

RectangleCollider &Tile::getCollider() { return this->collider; }