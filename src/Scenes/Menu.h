#ifndef MENU_H
#define MENU_H
#include <GL/glew.h>
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
#include "../Models/UI/Panel.h"

//#include "ButtonRenderer.h"

class Menu
{
public:
	Menu();
	Menu(const std::map<std::string, Sprite> &menuSprites, const SpriteRenderer &menuRenderer);
	virtual ~Menu();

	void OnEnable();
	void OnDisable();
	void Start();
	void Update(const float dt);
	void ProcessInput(const float dt);
	void Render(const float dt);

	void SetEnable(const bool value);

	std::map<std::string, Sprite> menuSprites;
	std::shared_ptr<TextRenderer> textRenderer;
	SpriteRenderer menuRenderer;
	SquareRenderer squareRenderer;

	/*	std::shared_ptr <Label> l_console;

	std::shared_ptr <Button> button;

	std::shared_ptr <Panel> panel;*/
	std::shared_ptr<Label> l_console, l_quickplay, l_newgame, l_options, l_editor;
	
	std::shared_ptr<TextBox> t_test;

	std::shared_ptr<Panel> panel;
	
	private:
	bool enable;
};

#endif // MENU_H