#ifndef MENU_H
#define MENU_H
#include <GLFW/glfw3.h>
#include <map>
#include <string.h>
#include <memory>
#include <iostream>

#include "../Models/Sprite.h"
#include "../Renderers/SpriteRenderer.h"
#include "../Renderers/TextRenderer.h"
#include "../Managers/InputManager.h"
#include "../Others/Game_Parameters.h"

#include "../Models/UI/Label.h"
#include "../Models/UI/TextBox.h"

/*#include "ButtonRenderer.h"
#include "Panel.h"*/

class Menu
{
public:
	Menu();
	Menu(const std::map<std::string, Sprite> &menuSprites, const SpriteRenderer &menuRenderer);
	~Menu();

	void Init();
	void Update(const float dt);
	void ProcessInput(const float dt);
	void Render(const float dt);

	std::map<std::string, Sprite> menuSprites;
	TextRenderer textRenderer;
	SpriteRenderer menuRenderer;
	SquareRenderer squareRenderer;
	//std::shared_ptr<ButtonRenderer> buttonRenderer;

	/*	std::shared_ptr <Label> l_console;
	

	std::shared_ptr <Button> button;

	

	std::shared_ptr <Panel> panel;*/
	Label l_console;
	Label l_quickplay;
	Label l_newgame;
	Label l_options;
	Label l_editor;

	TextBox textbox;
};

#endif // MENU_H