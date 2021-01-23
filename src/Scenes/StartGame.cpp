#include "StartGame.hpp"
#include "../Others/Game_Parameters.hpp"
#include "../Others/Logger.hpp"
#include "../Others/Utils.hpp"
#include "../Managers/InputManager.hpp"
#include "../Game.hpp"
#include "../Core/Math/Vector2.hpp"
#include "../Core/Math/Matrix4.hpp"

StartGame::StartGame() = default;

void StartGame::Initialize(const std::string &mapName)
{
	Logger::WriteLog("StartGame->StartGame()");
	this->map = new Map(mapName.c_str(), mapName.c_str());
	this->renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	this->camera = new Camera(static_cast<int>(Game_Parameters::SCREEN_WIDTH), static_cast<int>(Game_Parameters::SCREEN_HEIGHT));
	this->textRenderer = new TextRenderer(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	this->textRenderer->Load("../../resources/fonts/liberationsans.ttf", 20);

	this->SetEnable(true);
}

void StartGame::Start()
{
	Logger::WriteLog("StartGame->Start()");
	Sprite ct1_0 = Sprite(ResourceManager::GetTexture("ct1"), 0, 0, 32, 32);
	Sprite ct1_1 = Sprite(ResourceManager::GetTexture("ct1"), 0, 32, 32, 32);
	Sprite ct1_2 = Sprite(ResourceManager::GetTexture("ct1"), 0, 64, 32, 32);
	std::vector<Sprite> sprites;
	sprites.push_back(ct1_2);
	sprites.push_back(ct1_0);
	sprites.push_back(ct1_1);
	player = new Player(Vector2<int>(70, 70), sprites);
}

void StartGame::OnEnable()
{
	this->Start();

	player->SetTransform(Vector2<int>(Game_Parameters::SCREEN_WIDTH / 2, Game_Parameters::SCREEN_HEIGHT / 2),
						 Vector2<int>(Game_Parameters::SCREEN_HEIGHT / 18, Game_Parameters::SCREEN_HEIGHT / 18), 0.0F);
	player->setVelocity(500.0F);
	player->SetMap(map);
}

void StartGame::OnDisable()
{
	delete renderer;
	delete textRenderer;
	delete map;
	delete player;
	delete camera;
}

void StartGame::SetEnable(const bool value)
{
	if (this->enable == value)
		return;
	this->enable = value;
	if (this->enable)
		OnEnable();
	else
		OnDisable();
}

void StartGame::Update()
{
	player->Update();
	//player->DoCollision(weapons);
}

void StartGame::ProcessInput()
{
	if (InputManager::isKeyDown(GLFW_KEY_ESCAPE))
	{
		Game::SetGameState(GameState::MENU);
		return;
	}
	if (InputManager::isKeyDown(GLFW_KEY_Q))
	{
		//this->weapons.at(1).SetParent(player.get());
	}
	if (InputManager::isKeyDown(GLFW_KEY_E))
	{
		//this->weapons.at(1).RemoveParent();
	}
	player->ProcessInput();
}

void StartGame::Render()
{
	camera->setPosition(Vector2(player->GetPositionOfCenter().x - Game_Parameters::SCREEN_WIDTH / 2, player->GetPositionOfCenter().y - Game_Parameters::SCREEN_HEIGHT / 2));
	renderer->SetProjection(camera->cameraMatrix);
	map->Draw(*renderer);
	/*int temp = weapons.size();
	for (int i = 0; i < temp; i++)
	{
		this->weapons.at(i).DrawModel(this->renderer);
	}*/
	player->DrawModel(*renderer);

	Vector2 p = Utils::ScreenToWorld(camera->view, InputManager::mousePos);
	this->textRenderer->RenderText("mouse: " + std::to_string(p.x) + " - " + std::to_string(p.y), Vector2(700, 15), 1.0F, 0.5F);
	this->textRenderer->RenderText("player matrix: " + std::to_string(player->GetTransform().values[12]) + " - " + std::to_string(player->GetTransform().values[13]), Vector2(700, 45), 1.0F, 0.5F);
	this->textRenderer->RenderText("player pos: " + player->GetPosition().ToString(), Vector2(700, 75), 1.0F, 0.5F);
	this->textRenderer->RenderText("player cell: " + Utils::PositionToCell(player->GetPositionOfCenter()).ToString(), Vector2(700, 105), 1.0F, 0.5F);

	//label->Draw(*textRenderer);

	//button->Draw(*squareRenderer, *buttonRenderer, *textRenderer);
}

StartGame::~StartGame() = default;