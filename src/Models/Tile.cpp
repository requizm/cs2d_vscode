#include "Tile.hpp"

Tile::Tile() : type(TileTypes::FLOOR), frame(-1), GameObject()
{

}

Tile::Tile(Vector2<float> pos, const Sprite &sprite, Vector2<float> size, TileTypes type, int frame) : GameObject(pos, sprite, size, (int)ObjectType::TILE), type(type), frame(frame)
{
	
}

Tile::Tile(Vector2<float> pos, const Sprite &sprite, Vector2<float> size) : GameObject(pos, sprite, size, (int)ObjectType::TILE), type(TileTypes::FLOOR), frame(-1)
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