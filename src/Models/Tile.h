#ifndef TILE_H
#define TILE_H
#include "GameObject.h"

enum TileTypes
{
	WALL, OBSTACLE, FLOOR
};

class Tile :
	public GameObject
{
public:
	Tile();
	Tile(glm::vec2 pos, const Sprite& sprite, glm::vec2 size, TileTypes type, int frame = -1);
	Tile(glm::vec2 pos, const Sprite& sprite, glm::vec2 size);

	void setType(TileTypes type);
	TileTypes getType() const;

	int frame;

private:
	TileTypes type;

};

#endif