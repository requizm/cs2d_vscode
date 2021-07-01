#ifndef MENU_H
#define MENU_H

#include <string>

#include "../../Core/UI/ListItem.hpp"
#include "../../Core/UI/TextBox.hpp"
#include "../Model/Scene.hpp"

class Menu : public Scene
{
   public:
    Menu();
    ~Menu() = default;

    void Initialize(Sprite menuSprites[4]);

    void Unload() final;
    void Load() final;
    void Update() final;
    void ProcessInput() final;
    void Render() final;

    Sprite menuSprites[4];
    TextRenderer *textRenderer;

    SpriteRenderer *menuRenderer;
    SquareRenderer *squareRenderer;

    Label *l_console = nullptr;
    Label *l_quickplay = nullptr;
    Label *l_newgame = nullptr;
    Label *l_options = nullptr;
    Label *l_editor = nullptr;

    TextBox *t_test = nullptr;

    Panel *optionsPanel = nullptr;

    Panel *newPanel = nullptr;
    Panel *mapsPanel = nullptr;
    TextBox *t_mapName = nullptr;
    TextButton *b_newGame = nullptr;
    ListItem *mapNames = nullptr;

   private:
    void selectedMapChange(TextButton *old, TextButton *n);
    void newGameBtnClick();
};

#endif  // MENU_H