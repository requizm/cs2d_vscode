#ifndef MAP_H
#define MAP_H

#include <GL/glew.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#include <math.h> // pow()

#include "../Renderers/SpriteRenderer.hpp"
#include "../Models/Tile.hpp"
#include "../Models/Weapon.hpp"
#include "../Managers/ResourceManager.hpp"
#include "../Others/Game_Parameters.hpp"
#include "../Others/Logger.hpp"
#include "../Core/Loader/XMLLoader.hpp"

class Map
{
public:
	std::vector<Tile *> tiles;
	std::vector<Weapon *> weapons;

	Map();
	Map(const GLchar *file, const std::string &name);
	~Map();

	std::string GetName() const;

	void Draw(SpriteRenderer &renderer);

	Tile *GetTileByCell(int x, int y);
	Tile *GetTileByCell(Vector2<int> cellPos);

	Tile *GetTileByPosition(int x, int y);
	Tile *GetTileByPosition(Vector2<int> position);

private:
	void Load(const GLchar *file);
	std::string name;

	Vector2<int> mapLimit;
};

#endif // MAP_H
