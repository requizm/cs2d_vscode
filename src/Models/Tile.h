#ifndef TILE_H
#define TILE_H
#include "GameObject.h"

enum TileTypes
{
	FLOOR, SOLID_FLOOR, WALL, TRENCH
};

class Tile :
	public GameObject
{
public:
	Tile();
	Tile(glm::vec2 pos, Sprite sprite, glm::vec2 size, TileTypes type);
	Tile(glm::vec2 pos, Sprite sprite, glm::vec2 size);

	void setType(TileTypes type);
	TileTypes getType() const;

private:
	TileTypes type;
};

#endif