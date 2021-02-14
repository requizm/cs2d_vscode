#ifndef MAP_H
#define MAP_H

#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <math.h> // pow()

#include "../../Core/Renderer/SpriteRenderer.hpp"
#include "../../Core/Model/Tile.hpp"
#include "Weapon.hpp"
#include "../../Core/Manager/ResourceManager.hpp"
#include "../Other/GameParameters.hpp"
#include "../../Core/Manager/Logger.hpp"
#include "../../Core/Loader/XMLLoader.hpp"
#include "../../Core/Loader/JSONLoader.hpp"

class Map
{
public:
	std::vector<Tile *> tiles;
	std::vector<Weapon *> weapons;

	Map();
	Map(std::string file, const std::string &name);
	~Map();

	std::string GetName() const;

	void Draw(SpriteRenderer &renderer);

	Tile *GetTileByCell(int x, int y);
	Tile *GetTileByCell(Vector2<int> cellPos);

	Tile *GetTileByPosition(int x, int y);
	Tile *GetTileByPosition(Vector2<int> position);

private:
	void Load(std::string file);
	std::string name;

	Vector2<int> mapLimit;
};

#endif // MAP_H
