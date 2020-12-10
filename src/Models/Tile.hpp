#ifndef TILE_H
#define TILE_H
#include "GameObject.hpp"

enum TileTypes
{
	WALL, OBSTACLE, FLOOR
};

class Tile :
	public GameObject
{
public:
	Tile();
	Tile(Vector2<float> pos, const Sprite& sprite, Vector2<float> size, TileTypes type, int frame = -1);
	Tile(Vector2<float> pos, const Sprite& sprite, Vector2<float> size);

	void setType(TileTypes type);
	TileTypes getType() const;

	int frame;

private:
	TileTypes type;

};

#endif