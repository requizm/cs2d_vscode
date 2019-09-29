#include "Menu.h"

Menu::Menu() = default;

Menu::Menu(const std::map<std::string, Sprite> &menuSprites, const SpriteRenderer &menuRenderer)
{
	this->menuSprites = menuSprites;
	this->menuRenderer = menuRenderer;
}

Menu::~Menu()
{
	/*delete l_options;
	delete l_console;
	delete l_editor;
	delete l_newgame;
	delete button;
	delete textbox;
	delete panel;*/
}

void Menu::Init()
{
	textRenderer = TextRenderer(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	textRenderer.Load("../resources/fonts/liberationsans.ttf", 16);
	//squareRenderer = std::make_shared<SquareRenderer>();
	//buttonRenderer = std::make_shared<ButtonRenderer>();
	l_console = Label("Console", glm::vec2(10.0F, Game_Parameters::SCREEN_HEIGHT / 2 - 50.0F), textRenderer, 0.8F, glm::vec3(0.55F));
	l_newgame = Label("New Game", glm::vec2(10.0F, Game_Parameters::SCREEN_HEIGHT / 2 - 20.0F), textRenderer, 1.0F, glm::vec3(0.58F));
	l_options = Label("Options", glm::vec2(10.0F, Game_Parameters::SCREEN_HEIGHT / 2), textRenderer, 1.0F, glm::vec3(0.58F));
	l_editor = Label("Editor", glm::vec2(10.0F, Game_Parameters::SCREEN_HEIGHT / 2 + 20.0F), textRenderer, 1.0F, glm::vec3(0.58F));
	//button = new Button("hehehefs", glm::vec2(700.0F), *textRenderer, glm::vec3(1.0F), glm::vec3(0.57F));
	//textbox = std::make_shared<TextBox>(glm::vec2(5.0F, 5.0F), *textRenderer, glm::vec2(100.0F, 20.0F), true, 1.0F, glm::vec3(0.58F));
	//panel = std::make_shared<Panel>(glm::vec2(InputManager::Width / 2 - 210.0F, Game_Parameters::SCREEN_HEIGHT / 2 - 225.0F), "Options", glm::vec2(420.0F, 450.0F), *textRenderer, true, true, 1.0F, glm::vec3(0.21F));
	//textbox->setParent(panel.get());
	//textbox->setParentCenterPos();
}

void Menu::Update(const float dt)
{
	l_console.Update(dt);
	l_options.Update(dt);
	l_editor.Update(dt);
	l_newgame.Update(dt);
	//button->Update(dt);
	//textbox.Update(dt);
	//panel->Update(dt);
	//wchar_t ad = 97;
	//std::wcout << ad << std::endl;*/
}

void Menu::ProcessInput(const float dt) const
{
	/*	if (l_editor->isMouseDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		state = GameState::EDITOR;
	}

	if (l_newgame->isMouseDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		state = GameState::INGAME;
	}

	if (l_options->isMouseDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		panel->setEnable(true);
	}

	//std::cout << state << std::endl;*/
}

void Menu::Render(const float dt)
{
	for (std::map<std::string, Sprite>::iterator iter = menuSprites.begin(); iter != menuSprites.end(); ++iter)
	{
		std::string name = iter->first;
		Sprite sprite = iter->second;
		if (name == "splash")
		{
			menuRenderer.DrawSprite(sprite, glm::vec2(0.0F, 0.0F), glm::vec2(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT));
		}
		else if (name == "unrealsoftware")
		{
			//textRenderer->DrawSprite(sprite, glm::vec2(0.0F, 0.0F), glm::vec2(339.0F, 69.0F));
		}
		else if (name == "gametitle")
		{
		}
		else if (name == "cs2d")
		{
		}
	}
	//menuRenderer.DrawSprite(menuSprites["mouseSprite"], glm::vec2(InputManager::mouseX, InputManager::mouseY), glm::vec2(Game_Parameters::SCREEN_HEIGHT / 35, Game_Parameters::SCREEN_HEIGHT / 35), 0.0F, true);
	l_console.Draw();
	l_options.Draw();
	l_editor.Draw();
	l_console.Draw();
	l_newgame.Draw();
	//button->Draw(*squareRenderer);
	//panel->Draw(*squareRenderer.get(), *menuRenderer.get());
	//textbox->Draw(*squareRenderer.get(), *menuRenderer.get());
}