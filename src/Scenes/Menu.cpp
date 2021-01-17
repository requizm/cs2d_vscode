#include "Menu.hpp"
#include "../Game.hpp"
#include "../Others/Logger.hpp"

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
	this->textRenderer->Load("../../resources/fonts/liberationsans.ttf", 16);
	squareRenderer = SquareRenderer(true);

	this->l_console = std::make_shared<Label>("Console", Vector2<int>(10, Game_Parameters::SCREEN_HEIGHT / 2 - 50), *textRenderer, 0.8F, Vector3<float>(0.55F));
	this->l_newgame = std::make_shared<Label>("New Game", Vector2<int>(10, Game_Parameters::SCREEN_HEIGHT / 2 - 20), *textRenderer, 1.0F, Vector3<float>(0.58F));
	this->l_options = std::make_shared<Label>("Options", Vector2<int>(10, Game_Parameters::SCREEN_HEIGHT / 2), *textRenderer, 1.0F, Vector3<float>(0.58F));
	this->l_editor = std::make_shared<Label>("Editor", Vector2<int>(10, Game_Parameters::SCREEN_HEIGHT / 2 + 20), *textRenderer, 1.0F, Vector3<float>(0.58F));

	this->panel = std::make_shared<Panel>(Vector2<int>(Game_Parameters::SCREEN_WIDTH / 2 - 210.0F, Game_Parameters::SCREEN_HEIGHT / 2 - 225.0F), "Options", Vector2<int>(420, 450), *textRenderer, true, true, 1.0F, Vector3<float>(0.21F));
	this->panel->setMovable(true);

	this->t_test = std::make_shared<TextBox>(Vector2<int>(20, 20), *textRenderer, Vector2<int>(100, 20), true, 1.0F, Vector3<float>(0.58F));
	this->t_test->setParent(panel.get());
	this->t_test->setParentCenterPos();
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

void Menu::Update()
{
	l_options->Update();
	l_console->Update();
	l_editor->Update();
	l_newgame->Update();
	panel->Update();
}

void Menu::ProcessInput()
{
	l_options->ProcessInput();
	l_console->ProcessInput();
	l_editor->ProcessInput();
	l_newgame->ProcessInput();
	panel->ProcessInput();

	if (l_editor->isMouseDown())
	{
		Game::SetGameState(GameState::EDITOR);
		return;
	}

	if (l_newgame->isMouseDown())
	{
		Game::SetGameState(GameState::INGAME);
		return;
	}

	if (l_options->isMouseDown())
	{
		panel->setEnable(true);
	}
}

void Menu::Render()
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
			menuRenderer.DrawSprite(menuSprites[3], Vector2<int>(0), Vector2<int>(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT));
			break;
		}
	}
	//menuRenderer.DrawSprite(menuSprites["mouseSprite"], Vector2<int>(InputManager::mousePos.x, InputManager::mousePos.y), Vector2<int>(Game_Parameters::SCREEN_HEIGHT / 35, Game_Parameters::SCREEN_HEIGHT / 35), 0.0F, true);
	l_options->Draw();
	l_editor->Draw();
	l_console->Draw();
	l_newgame->Draw();
	//button->Draw(*squareRenderer);
	panel->Draw(menuRenderer, squareRenderer);
	//t_test->Draw(menuRenderer, squareRenderer);
}