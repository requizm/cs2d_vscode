#ifndef GAME_PARAMETERS_H
#define GAME_PARAMETERS_H

enum GameState
{
    MENU,
    INGAME,
    EDITOR
};

class Game_Parameters
{
public:
    static int SCREEN_WIDTH;
    static int SCREEN_HEIGHT;

    Game_Parameters();
    ~Game_Parameters();

    static void LoadParameters();
};

#endif