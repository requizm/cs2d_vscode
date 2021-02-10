#include "Map.hpp"

Map::Map() = default;

Map::Map(const GLchar *file, const std::string &name)
{
	this->name = name;
	Load(file);
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
	JSONLoader jsonLoader;
	std::string str2("../../resources/content/weapons.json");
	nlohmann::json weaponsJ = jsonLoader.Load(str2);

	for (nlohmann::json::iterator it = weaponsJ.begin(); it != weaponsJ.end(); ++it)
	{
		std::string spritePath = "../../resources/textures/weapons/" + it->at("sprite").get<std::string>() + ".png";
		std::string floorSpritePath = "../../resources/textures/weapons/" + it->at("floorSprite").get<std::string>() + ".png";
		ResourceManager::LoadTexture(spritePath.c_str(), GL_TRUE, it->at("sprite").get<std::string>());
		ResourceManager::LoadTexture(floorSpritePath.c_str(), GL_TRUE, it->at("floorSprite").get<std::string>());
	}

	this->tiles.clear();
	std::string str(file);
	XMLLoader loader = XMLLoader(str);

	this->name = loader.GetDoc().first_node("info")->first_node("name")->value();
	char *mapx = loader.GetDoc().first_node("info")->first_node("mapLimitX")->value();
	char *mapy = loader.GetDoc().first_node("info")->first_node("mapLimitY")->value();
	this->mapLimit.x = atoi(mapx);
	this->mapLimit.y = atoi(mapy);
	rapidxml::xml_node<> *node = loader.GetDoc().first_node("map");
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
			Weapon *w;
			bool found = false;
			for (nlohmann::json::iterator it = weaponsJ.begin(); it != weaponsJ.end(); ++it)
			{
				if (itemId == it->at("id").get<int>())
				{
					std::string textureName = it->at("sprite").get<std::string>();
					std::string floorTextureName = it->at("floorSprite").get<std::string>();
					std::string name = it->at("name").get<std::string>();
					WeaponType type = (WeaponType)it->at("type").get<int>();
					int maxAmmo = it->at("maxAmmo").get<int>();
					int currentAmmo = it->at("currentAmmo").get<int>();
					int curAmmoInMag = it->at("curAmmoInMag").get<int>();
					int maxAmmoInMag = it->at("maxAmmoInMag").get<int>();
					w = new Weapon(pos, Sprite(ResourceManager::GetTexture(textureName)), Sprite(ResourceManager::GetTexture(floorTextureName)), name, type, maxAmmo, currentAmmo, curAmmoInMag, maxAmmoInMag);
					found = true;
					break;
				}
			}
			if (!found)
			{
				w = new Weapon(pos, Sprite(ResourceManager::GetTexture("awp")), Sprite(ResourceManager::GetTexture("awp_d")), "awp", WeaponType::MAIN, 90, 90, 30, 30);
			}
			weapons.push_back(w);
		}
	}
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
