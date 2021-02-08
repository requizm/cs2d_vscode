#include "Game_Parameters.hpp"

int Game_Parameters::SCREEN_WIDTH;
int Game_Parameters::SCREEN_HEIGHT;
int Game_Parameters::SIZE_TILE;

Game_Parameters::Game_Parameters()
{
}

Game_Parameters::~Game_Parameters() = default;

void Game_Parameters::LoadParameters()
{
    std::ifstream file("../../resources/content/gameparameters.txt");

    if (!file)
    {
        perror("Error open gameparameters.txt");
        //exit(EXIT_FAILURE);
    }
    std::string line;
    int i = 0;
    while (std::getline(file, line))
    {
        switch (i)
        {
        case 0:
            Game_Parameters::SCREEN_WIDTH = atoi(line.c_str());
            i++;
            break;
        case 1:
            Game_Parameters::SCREEN_HEIGHT = atoi(line.c_str());
            i++;
            break;
        }
    }

    Game_Parameters::SIZE_TILE = static_cast<int>((powf(((Game_Parameters::SCREEN_HEIGHT * Game_Parameters::SCREEN_WIDTH) / (26.5f * (float)15)), 0.5f)));
}