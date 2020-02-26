#include "Menu.h"
#include "../Game.h"
#include "../Others/Logger.h"

Menu::Menu() = default;

Menu::Menu(Sprite menuSprites[4], const SpriteRenderer &menuRenderer)
{
	Logger::WriteLog("Menu::Menu(menuSprites[4], menuRenderer)");
	for (int i = 0; i < 4; i++)
	{
		this->menuSprites[i] = menuSprites[i];
	}
	this->menuRenderer = menuRenderer;
	this->SetEnable(true);
}

Menu::~Menu() = default;

void Menu::Start()
{
	Logger::WriteLog("Menu::Start()");
	this->textRenderer = std::make_shared<TextRenderer>(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	this->textRenderer->Load("../resources/fonts/liberationsans.ttf", 16);
	squareRenderer = SquareRenderer(true);
	//buttonRenderer = std::make_shared<ButtonRenderer>();
	this->l_console = std::make_shared<Label>("Console", glm::vec2(10.0F, Game_Parameters::SCREEN_HEIGHT / 2 - 50.0F), *textRenderer, 0.8F, glm::vec3(0.55F));
	this->l_newgame = std::make_shared<Label>("New Game", glm::vec2(10.0F, Game_Parameters::SCREEN_HEIGHT / 2 - 20.0F), *textRenderer, 1.0F, glm::vec3(0.58F));
	this->l_options = std::make_shared<Label>("Options", glm::vec2(10.0F, Game_Parameters::SCREEN_HEIGHT / 2), *textRenderer, 1.0F, glm::vec3(0.58F));
	this->l_editor = std::make_shared<Label>("Editor", glm::vec2(10.0F, Game_Parameters::SCREEN_HEIGHT / 2 + 20.0F), *textRenderer, 1.0F, glm::vec3(0.58F));
	//button = Button("hehehefs", glm::vec2(700.0F), textRenderer, glm::vec3(1.0F), glm::vec3(0.57F));
	this->t_test = std::make_shared<TextBox>(glm::vec2(20.0F, 20.0F), *textRenderer, glm::vec2(100.0F, 20.0F), true, 1.0F, glm::vec3(0.58F));
	//panel = Panel(glm::vec2(Game_Parameters::SCREEN_WIDTH / 2 - 210.0F, Game_Parameters::SCREEN_HEIGHT / 2 - 225.0F), "Options", glm::vec2(420.0F, 450.0F), textRenderer, true, true, 1.0F, glm::vec3(0.21F));
	this->panel = std::make_shared<Panel>(glm::vec2(Game_Parameters::SCREEN_WIDTH / 2 - 210.0F, Game_Parameters::SCREEN_HEIGHT / 2 - 225.0F), "Options", glm::vec2(420.0F, 450.0F), *textRenderer, true, true, 1.0F, glm::vec3(0.21F));
	this->t_test->setParent(panel.get());
	this->t_test->setParentCenterPos();
	this->panel->setMovable(true);
}

void Menu::OnEnable()
{
	this->Start();
	panel->setEnable(false);
}

void Menu::OnDisable()
{
}

void Menu::SetEnable(const bool value)
{
	if (this->enable == value)
		return;
	this->enable = value;
	if (this->enable)
		OnEnable();
	else
		OnDisable();
}

void Menu::Update(const float dt)
{
	l_options->Update(dt);
	l_console->Update(dt);
	l_editor->Update(dt);
	l_newgame->Update(dt);
	//button->Update(dt);
	t_test->Update(dt);
	panel->Update(dt);
}

void Menu::ProcessInput(const float dt)
{
	l_options->ProcessInput();
	l_console->ProcessInput();
	l_editor->ProcessInput();
	l_newgame->ProcessInput();
	panel->ProcessInput();

	if (l_editor->isMouseDown())
	{
		Game::SetGameState(GameState::EDITOR);
		//l_editor->SimulateUp();
	}

	if (l_newgame->isMouseDown())
	{
		Game::SetGameState(GameState::INGAME);
		//l_newgame->SimulateUp();
	}

	if (l_options->isMouseDown())
	{
		panel->setEnable(true);
	}
}

void Menu::Render(const float dt)
{
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			menuRenderer.DrawSprite(menuSprites[3], glm::vec2(0.0F), glm::vec2(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT));
			break;
		}
	}

	/*for (std::map<std::string, Sprite>::iterator iter = menuSprites->begin(); iter != menuSprites->end(); ++iter)
	{
		std::string name = iter->first;
		Sprite sprite = iter->second;
		if (name == "splash")
		{
			menuRenderer.DrawSprite(sprite, glm::vec2(0.0F), glm::vec2(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT));
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
	}*/
	//menuRenderer.DrawSprite(menuSprites["mouseSprite"], glm::vec2(InputManager::mousePos.x, InputManager::mousePos.y), glm::vec2(Game_Parameters::SCREEN_HEIGHT / 35, Game_Parameters::SCREEN_HEIGHT / 35), 0.0F, true);
	l_console->Draw();
	l_options->Draw();
	l_editor->Draw();
	l_console->Draw();
	l_newgame->Draw();
	//button->Draw(*squareRenderer);
	panel->Draw(squareRenderer, menuRenderer);
	t_test->Draw(squareRenderer, menuRenderer);
}