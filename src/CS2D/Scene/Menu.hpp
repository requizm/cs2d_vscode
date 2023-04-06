#ifndef MENU_H
#define MENU_H

#include <memory>
#include <string>

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
    std::shared_ptr<TextRenderer> textRenderer;

    std::shared_ptr<SpriteRenderer> menuRenderer;
    std::shared_ptr<SquareRenderer> squareRenderer;

    std::shared_ptr<Label> l_console;
    std::shared_ptr<Label> l_quickplay;
    std::shared_ptr<Label> l_newgame;
    std::shared_ptr<Label> l_options;
    std::shared_ptr<Label> l_editor;

    std::shared_ptr<TextBox> t_test;

    std::shared_ptr<Panel> optionsPanel;

    std::shared_ptr<Panel> newPanel;
    std::shared_ptr<Panel> mapsPanel;
    std::shared_ptr<TextBox> t_mapName;
    std::shared_ptr<TextButton> b_newGame;
    std::shared_ptr<ListItem> mapNames;

   private:
    void selectedMapChange(TextButton *old, TextButton *n);
    void newGameBtnClick();
};

#endif  // MENU_H