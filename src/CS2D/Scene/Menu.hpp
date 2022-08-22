#ifndef MENU_H
#define MENU_H

#include <string>
#include <memory>

#include "../../Core/UI/ListItem.hpp"
#include "../../Core/UI/TextBox.hpp"
#include "../Model/Scene.hpp"

class Menu : public Scene
{
   public:
    Menu();
    ~Menu() = default;

    void Initialize();

    void Unload() final;
    void Load() final;
    void Update() final;
    void ProcessInput() final;
    void Render() final;

    Sprite menuSprites[4];
    std::unique_ptr<TextRenderer> textRenderer;

    std::unique_ptr<SpriteRenderer> menuRenderer;
    std::unique_ptr<SquareRenderer> squareRenderer;

    std::unique_ptr<Label> l_console;
    std::unique_ptr<Label> l_quickplay;
    std::unique_ptr<Label> l_newgame;
    std::unique_ptr<Label> l_options;
    std::unique_ptr<Label> l_editor;

    std::unique_ptr<TextBox> t_test;

    std::unique_ptr<Panel> optionsPanel;

    std::unique_ptr<Panel> newPanel;
    std::unique_ptr<Panel> mapsPanel;
    std::unique_ptr<TextBox> t_mapName;
    std::unique_ptr<TextButton> b_newGame;
    std::unique_ptr<ListItem> mapNames;

   private:
    void selectedMapChange(TextButton *old, TextButton *n);
    void newGameBtnClick();
};

#endif  // MENU_H