#include "Tile.h"

Tile::Tile() : type(TileTypes::FLOOR), frame(-1)
{

}

Tile::Tile(glm::vec2 pos, const Sprite &sprite, glm::vec2 size, TileTypes type, int frame) : GameObject(pos, sprite, size, (int)ObjectType::TILE), type(type), frame(frame)
{
	
}

Tile::Tile(glm::vec2 pos, const Sprite &sprite, glm::vec2 size) : GameObject(pos, sprite, size, (int)ObjectType::TILE), type(TileTypes::FLOOR), frame(-1)
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