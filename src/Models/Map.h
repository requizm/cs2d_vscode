#ifndef MAP_H
#define MAP_H

#include <vector>
#include <GL/glew.h>
#include "../Renderers/SpriteRenderer.h"
#include "../Models/Tile.h"
//#include "InputManager.h"

class Map
{
public:
	std::vector<Tile> Tiles;

	Map();
	Map(const GLchar* file, const std::string& name);
	Map(const GLchar* file);
	~Map();

	std::string GetName() const;
	Tile* getTile(int cellX, int cellY);

	// Render level
	void Draw(SpriteRenderer& renderer);

private:
	void Init(std::vector<std::vector<GLuint>> tileData) const;
	void Load(const GLchar* file);
	std::string name;
};

#endif // MAP_H
