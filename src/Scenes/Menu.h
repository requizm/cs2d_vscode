#ifndef MENU_H
#define MENU_H
#include <map>
#include "../Models/Sprite.h"
#include <string.h>
#include <memory>
#include "../Renderers/SpriteRenderer.h"
#include "../Managers/InputManager.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../Renderers/TextRenderer.h"
/*#include "ButtonRenderer.h"
#include "Enums.h"
#include "TextBox.h"
#include "Panel.h"*/

class Menu
{
public:
	Menu();
	Menu(std::map<std::string, Sprite> *menuSprites, SpriteRenderer *menuRenderer);
	~Menu();

	void Init();
	void Update(const float dt) const;
	void ProcessInput(const float dt) const;
	void Render(const float dt) const;

	//std::map<std::string, Sprite>* menuSprites;
	std::shared_ptr<TextRenderer> textRenderer;
	SpriteRenderer menuRenderer;
	//std::shared_ptr<SquareRenderer> squareRenderer;
	//std::shared_ptr<ButtonRenderer> buttonRenderer;

	/*	std::shared_ptr <Label> l_console;
	std::shared_ptr <Label> l_quickplay;
	std::shared_ptr <Label> l_newgame;
	std::shared_ptr <Label> l_options;
	std::shared_ptr <Label> l_editor;

	std::shared_ptr <Button> button;

	std::shared_ptr <TextBox> textbox;

	std::shared_ptr <Panel> panel;*/
};

#endif // MENU_H