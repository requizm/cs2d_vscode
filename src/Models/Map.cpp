#include "Map.h"
#include <fstream>
#include <sstream>
#include <math.h> // pow()
#include "rapidxml-1.13/rapidxml.hpp"
#include "../Managers/ResourceManager.h"
#include "../Others/Game_Parameters.h"
#include "../Others/Logger.h"

Map::Map() = default;

Map::Map(const GLchar *file, const std::string &name)
{
	this->name = name;
	Load(file);
	Logger::WriteLog("GameObject->Destroy()");
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
	for (rapidxml::xml_node<> *child = node->first_node(); child; child = child->next_sibling())
	{
		//std::cout << child->first_node("cellY")->value() << std::endl;
		//tile.SetSize(glm::vec2(Game::Width / 26.5, Game::Width / 26.5));
		char *x = child->first_node("cellX")->value();
		char *y = child->first_node("cellY")->value();
		char *tIndex = child->first_node("tileTexture")->value();
		char *tType = child->first_node("tileType")->value();
		int cellX = atoi(x);
		int cellY = atoi(y);
		int textureIndex = atoi(tIndex);
		int tileType = atoi(tType);
		const glm::vec2 pos(Game_Parameters::SIZE_TILE * cellX, Game_Parameters::SIZE_TILE * cellY);
		const glm::vec2 size(glm::vec2(Game_Parameters::SIZE_TILE, Game_Parameters::SIZE_TILE));
		const int xoffset = textureIndex % (ResourceManager::GetTexture("cs2dnorm").Width / 32);
		const int yoffset = textureIndex / (ResourceManager::GetTexture("cs2dnorm").Width / 32);
		const Sprite sprite = Sprite(ResourceManager::GetTexture("cs2dnorm"), (xoffset)*32, yoffset * 32, 32, 32);
		Tile tile(pos, sprite, size, TileTypes(tileType));
		Tiles.push_back(tile);
	}
}
void Map::Draw(SpriteRenderer &renderer)
{
	for (GameObject &tile : Tiles)
	{
		if (!tile.IsDestroyed())
			tile.DrawModel(renderer);
	}
}

/*
void Map::Load(const GLchar * file)
{
	this->Tiles.clear();
	// Load from file
	GLuint tileCode;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // Read each line from level file
		{
			std::istringstream sstream(line);
			std::vector<GLuint> row;
			while (sstream >> tileCode) // Read each word seperated by spaces
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (!tileData.empty())
			this->Init(tileData);
	}
}

void Map::Draw(SpriteRenderer & renderer)
{
	for (GameObject &tile : Sprites)
		if (!tile.IsDestroyed())
			tile.Draw(renderer);
}
*/
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

			const glm::vec2 pos(Game_Parameters::SCREEN_WIDTH / 26.5 * x, Game_Parameters::SCREEN_WIDTH / 26.5 * y);
			const glm::vec2 size(Game_Parameters::SCREEN_WIDTH / 26.5, Game_Parameters::SCREEN_WIDTH / 26.5);
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

Tile *Map::getTile(int cellX, int cellY)
{
	/*	bool result = false;
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

	return nullptr;*/
}
