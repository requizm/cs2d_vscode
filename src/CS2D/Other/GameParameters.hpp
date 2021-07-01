#ifndef GAME_PARAMETERS_H
#define GAME_PARAMETERS_H

#include <cmath>  // pow()
#include <fstream>
#include <string>


class GameParameters
{
   public:
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;
    static int SIZE_TILE;
    static std::string resDirectory;

    GameParameters();
    ~GameParameters();

    static void LoadParameters();
};

#endif