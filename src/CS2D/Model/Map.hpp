#ifndef MAP_H
#define MAP_H

#include <GL/glew.h>

#include <cmath>  // pow()
#include <string>
#include <vector>

#include "../../Core/Renderer/SpriteRenderer.hpp"
#include "Tile.hpp"
#include "Weapon.hpp"


class Map
{
   public:
    std::vector<Tile *> tiles;
    std::vector<Weapon *> weapons;

    Map() = default;
    Map(const std::string &path, const std::string &name);
    ~Map();

    std::string GetName() const;

    void Draw(SpriteRenderer &renderer);

    Tile *GetTileByCell(int x, int y);
    Tile *GetTileByCell(Vector2<int> &cellPos);

    Tile *GetTileByPosition(int x, int y);
    Tile *GetTileByPosition(Vector2<int> &position);

   private:
    void Load(const std::string &file);
    std::string name;

    Vector2<int> mapLimit;
};

#endif  // MAP_H
