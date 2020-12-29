#include "Map.hpp"
#include <fstream>
#include <sstream>
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

Map::Map(const GLchar *file)
{
	Load(file);
}

Map::~Map() = default;

void Map::Load(const GLchar *file)
{
	std::string codeString;
	this->Tiles.clear();
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
		int cellX = atoi(x);
		int cellY = atoi(y);
		int textureIndex = atoi(tIndex);
		int tileType = atoi(tType);
		const Vector2<int> pos(Game_Parameters::SIZE_TILE * cellX, Game_Parameters::SIZE_TILE * cellY);
		const Vector2<int> size(Vector2<int>(Game_Parameters::SIZE_TILE, Game_Parameters::SIZE_TILE));
		const int xoffset = textureIndex % (ResourceManager::GetTexture("cs2dnorm").Width / 32);
		const int yoffset = textureIndex / (ResourceManager::GetTexture("cs2dnorm").Width / 32);
		const Sprite sprite = Sprite(ResourceManager::GetTexture("cs2dnorm"), (xoffset)*32, yoffset * 32, 32, 32);
		Tile tile = Tile(pos, sprite, size, TileTypes(tileType));
		Tiles.push_back(tile);
	}

	delete[] codeChar;
}
void Map::Draw(SpriteRenderer &renderer)
{
	for (GameObject &tile : Tiles)
	{
		if (!tile.IsDestroyed())
			tile.DrawModel(renderer);
	}
}

void Map::Init(std::vector<std::vector<GLuint>> tileData) const
{
	Logger::WriteLog("Map->Init() " + this->name + "");
	// Calculate dimensions
	GLuint height = tileData.size();

	// Initialize level tiles based on tileData
	for (GLuint y = 0; y < height; y++)
	{
		for (GLuint x = 0; x < tileData[y].size(); x++)
		{
			const Vector2<int> pos(Game_Parameters::SCREEN_WIDTH / 26 * x, Game_Parameters::SCREEN_WIDTH / 26 * y);
			const Vector2<int> size(Game_Parameters::SCREEN_WIDTH / 26, Game_Parameters::SCREEN_WIDTH / 26);
			const int yoffset = tileData[y][x] / 17;
			const Sprite sprite = Sprite(ResourceManager::GetTexture("tile"), tileData[y][x] * 32, yoffset * 32, 32, 32);
			GameObject go = GameObject(pos, sprite, size);
			//this->Sprites.push_back(go);
		}
	}
}
std::string Map::GetName() const
{
	return name;
}

/*Tile *Map::getTile(int cellX, int cellY)
{
		bool result = false;
	int index = 0;
	for (std::vector<int>::size_type i = 0; i != Tiles.size(); i++)
	{
			if (static_cast<int>(Tiles.at(i).getCellPosition().x) == cellX && static_cast<int>(Tiles.at(i).getCellPosition().y) == cellY)
		{
			result = true;
			index = i;
			break;
		}
	}

	if (result)
		return &Tiles.at(index);

	return nullptr;
}*/
