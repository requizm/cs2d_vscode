#include "Tile.h"

Tile::Tile() = default;

Tile::Tile(glm::vec2 pos, const Sprite &sprite, glm::vec2 size, TileTypes type) : GameObject(pos, sprite, size, (int)ObjectType::TILE)
{
	this->type = type;
}

Tile::Tile(glm::vec2 pos, const Sprite &sprite, glm::vec2 size) : GameObject(pos, sprite, size, (int)ObjectType::TILE), type(TileTypes::FLOOR)
{
}

void Tile::setType(const TileTypes type)
{
	this->type = type;
}

TileTypes Tile::getType() const
{
	return this->type;
}