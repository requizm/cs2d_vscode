#include "Map.hpp"
#include <fstream>
#include <sstream>
#include <cstring>
#include <math.h> // pow()
#include "rapidxml-1.13/rapidxml.hpp"
#include "../Managers/ResourceManager.hpp"
#include "../Others/Game_Parameters.hpp"
#include "../Others/Logger.hpp"

Map::Map() = default;

Map::Map(const GLchar *file, const std::string &name)
{
	this->name = name;
	Load(file);
	//Logger::WriteLog("GameObject->Destroy()");
}

Map::~Map()
{
	for (auto &tile : tiles)
	{
		delete tile;
	}
	tiles.clear();
	for (auto &weapon : weapons)
	{
		delete weapon;
	}
	weapons.clear();
}

void Map::Load(const GLchar *file)
{
	std::string codeString;
	this->tiles.clear();
	std::ifstream fileC(file);
	if (!fileC)
	{
		std::string str = "dosya acilamadi: ";
		str += file;
		Logger::DebugLog(str);
		Logger::WriteLog(str);
		exit(EXIT_FAILURE);
	}

	std::stringstream fileStream;
	fileStream << fileC.rdbuf();
	fileC.close();
	codeString = fileStream.str();
	rapidxml::xml_document<> doc;
	char *codeChar = new char[codeString.length() + 1];
	strcpy(codeChar, codeString.c_str());
	doc.parse<0>(codeChar);
	this->name = doc.first_node("info")->first_node("name")->value();
	char *mapx = doc.first_node("info")->first_node("mapLimitX")->value();
	char *mapy = doc.first_node("info")->first_node("mapLimitY")->value();
	this->mapLimit.x = atoi(mapx);
	this->mapLimit.y = atoi(mapy);
	rapidxml::xml_node<> *node = doc.first_node("map");
	//std::cout << node->first_node("tile")->first_node("cellX")->next_sibling()->name() << std::endl;
	int i = 0;
	for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
	{
		//std::cout << child->first_node("cellY")->value() << std::endl;
		//tile.SetSize(Vector2<float>(Game::Width / 26.5, Game::Width / 26.5));
		char *x = child->first_node("cellX")->value();
		char *y = child->first_node("cellY")->value();
		char *tIndex = child->first_node("tileTexture")->value();
		char *tType = child->first_node("tileType")->value();
		char *iNo = child->first_node("itemID")->value();
		int cellX = atoi(x);
		int cellY = atoi(y);
		int textureIndex = atoi(tIndex);
		int tileType = atoi(tType);
		int itemId = atoi(iNo);
		const Vector2<int> pos(Game_Parameters::SIZE_TILE * cellX, Game_Parameters::SIZE_TILE * cellY);
		const Vector2<int> size(Vector2<int>(Game_Parameters::SIZE_TILE, Game_Parameters::SIZE_TILE));
		const int xoffset = textureIndex % (ResourceManager::GetTexture("cs2dnorm").Width / 32);
		const int yoffset = textureIndex / (ResourceManager::GetTexture("cs2dnorm").Width / 32);
		const Sprite sprite = Sprite(ResourceManager::GetTexture("cs2dnorm"), (xoffset)*32, yoffset * 32, 32, 32);
		Tile *tile = new Tile(pos, sprite, size, TileTypes(tileType));
		tiles.push_back(tile);
		if (itemId != 0)
		{
			Weapon *w = new Weapon(pos, ResourceManager::GetTexture("ak47"), ResourceManager::GetTexture("ak47_d"), "ak47", WeaponType::MAIN, 90, 90, 30, 30);
			weapons.push_back(w);
		}
	}
	delete[] codeChar;
}
void Map::Draw(SpriteRenderer &renderer)
{
	for (auto &tile : tiles)
	{
		if (!tile->IsDestroyed())
			tile->DrawModel(renderer);
	}
	for (auto &weapon : weapons)
	{
		weapon->DrawModel(renderer);
	}
}

Tile *Map::GetTileByCell(int x, int y)
{
	if (x < 0 || y < 0 || x >= mapLimit.x || y >= mapLimit.y)
	{
		return nullptr;
	}
	int tileIndex = (x * this->mapLimit.x) + y;
	return tiles.at(tileIndex);
}

Tile *Map::GetTileByCell(Vector2<int> cellPos)
{
	if (cellPos.x < 0 || cellPos.y < 0 || cellPos.x >= mapLimit.x || cellPos.y >= mapLimit.y)
	{
		return nullptr;
	}
	int tileIndex = (cellPos.x * this->mapLimit.x) + cellPos.y;
	return tiles.at(tileIndex);
}

Tile *Map::GetTileByPosition(int x, int y)
{
	Vector2<int> cell = Utils::PositionToCell(Vector2<int>(x, y));
	return GetTileByCell(cell);
}

Tile *Map::GetTileByPosition(Vector2<int> position)
{
	Vector2<int> cell = Utils::PositionToCell(position);

	return GetTileByCell(cell);
}

std::string Map::GetName() const
{
	return name;
}
