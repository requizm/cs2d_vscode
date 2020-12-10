#ifndef MENU_H
#define MENU_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include <string.h>
#include <memory>
#include <iostream>

#include "../Models/Sprite.hpp"
#include "../Renderers/SpriteRenderer.hpp"
#include "../Renderers/TextRenderer.hpp"
#include "../Managers/InputManager.hpp"
#include "../Others/Game_Parameters.hpp"

#include "../Models/UI/Label.hpp"
#include "../Models/UI/TextBox.hpp"
#include "../Models/UI/Panel.hpp"

//#include "ButtonRenderer.hpp"

class Menu
{
public:
	Menu();
	Menu(Sprite menuSprites[4], const SpriteRenderer &menuRenderer);
	virtual ~Menu();

	void OnEnable();
	void OnDisable();
	void Start();
	void Update();
	void ProcessInput();
	void Render();

	void SetEnable(const bool value);

	Sprite menuSprites[4];
	std::shared_ptr<TextRenderer> textRenderer;

	SpriteRenderer menuRenderer;
	SquareRenderer squareRenderer;

	std::shared_ptr<Label> l_console, l_quickplay, l_newgame, l_options, l_editor;
	
	std::shared_ptr<TextBox> t_test;

	std::shared_ptr<Panel> panel;

private:
	bool enable =false;
};

#endif // MENU_H