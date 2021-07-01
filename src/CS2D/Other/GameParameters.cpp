#include "GameParameters.hpp"

#include "../../Core/Loader/JSONLoader.hpp"

int GameParameters::SCREEN_WIDTH;
int GameParameters::SCREEN_HEIGHT;
int GameParameters::SIZE_TILE;
std::string GameParameters::resDirectory;

GameParameters::GameParameters() {}

GameParameters::~GameParameters() = default;

void GameParameters::LoadParameters()
{
    JSONLoader loader;
    nlohmann::json data = loader.Load("config.json");

    GameParameters::SCREEN_WIDTH = data["options"]["width"].get<int>();
    GameParameters::SCREEN_HEIGHT = data["options"]["height"].get<int>();
    GameParameters::resDirectory = data["resDirectory"].get<std::string>();

    GameParameters::SIZE_TILE = static_cast<int>(
        (powf(((GameParameters::SCREEN_HEIGHT * GameParameters::SCREEN_WIDTH) /
               (26.5f * (float)15)),
              0.5f)));
}