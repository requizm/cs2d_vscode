#include "StartGame.h"
#include "../Others/Game_Parameters.h"
#include "../Others/Logger.h"
#include "../Managers/InputManager.h"
#include "../Game.h"
#include "../Core/Math/Vector2.h"
#include "../Core/Math/Matrix4.h"

StartGame::StartGame() = default;

StartGame::StartGame(const Map &map, const SpriteRenderer &renderer)
{
	Logger::WriteLog("StartGame->StartGame()");
	//this->weapons = std::make_shared<std::vector<Weapon *>>(nullptr);
	this->map = map;
	this->renderer = renderer;
	//this->renderer = std::make_shared<SpriteRenderer>();,
	this->camera = std::make_shared<Camera>(static_cast<int>(Game_Parameters::SCREEN_WIDTH), static_cast<int>(Game_Parameters::SCREEN_HEIGHT));

	this->SetEnable(true);
}

StartGame::StartGame(const Map &map, const SpriteRenderer &renderer, const std::vector<Weapon> &weapons)
{
	Logger::WriteLog("StartGame->StartGame()");
	//this->weapons = std::make_shared<std::vector<Weapon *>>(nullptr);
	this->map = map;
	this->renderer = renderer;
	//this->renderer = std::make_shared<SpriteRenderer>();,
	this->camera = std::make_shared<Camera>(static_cast<int>(Game_Parameters::SCREEN_WIDTH), static_cast<int>(Game_Parameters::SCREEN_HEIGHT));
	this->weapons = weapons;

	this->SetEnable(true);
}

/*StartGame::StartGame(Map* map, std::vector<std::shared_ptr<Weapon>>* weapons, SpriteRenderer* renderer, std::vector<GameObject*> gameobjects)
{
	this->weapons = weapons;
	this->map = map;
	this->renderer = std::make_shared<SpriteRenderer>(*renderer);
	//this->renderer = std::make_shared<SpriteRenderer>();
	//for (std::vector<int>::size_type i = 0; i != weapons->size(); i++)
//	{
	//	Weapon *wp = &weapons->at(i);
		//this->weapons.push_back(wp);
//	}
	//this->weapons = std::make_shared<std::vector<Weapon*>>(&weapons);
	this->camera = std::make_shared<Camera>(static_cast<int>(InputManager::Width), static_cast<int>(InputManager::Height));
	this->gameobjects = std::make_shared<std::vector<GameObject*>>(gameobjects);
}*/

/*StartGame::StartGame(Map *map, std::vector<std::shared_ptr<Weapon>> *weapons, SpriteRenderer *renderer)
{
	this->weapons = weapons;
	this->map = map;
	this->renderer = std::make_shared<SpriteRenderer>(*renderer);
	//this->renderer = std::make_shared<SpriteRenderer>();
//	for (std::vector<int>::size_type i = 0; i != weapons->size(); i++)
	//{
		//Weapon *wp = &weapons->at(i);
		//this->weapons->push_back(std::make_shared<Weapon>(wp));
//	}
	//this->weapons = std::make_shared<std::vector<Weapon*>>(&weapons);
	this->camera = std::make_shared<Camera>(InputManager::Width, InputManager::Height, Vector3<float>(0.0f, 0.0f, 3.0f));
}*/

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
	player = std::make_unique<Player>(Vector2<float>(70.0F, 70.0F), sprites);

	//weapons.at(0).SetParent(player.get());
}

void StartGame::OnEnable()
{
	this->Start();

	player->SetTransform(Vector2<float>(Game_Parameters::SCREEN_WIDTH / 2, Game_Parameters::SCREEN_HEIGHT / 2),
						 Vector2<float>(Game_Parameters::SCREEN_HEIGHT / 18, Game_Parameters::SCREEN_HEIGHT / 18), 0.0F);
	player->setVelocity(500.0F);
	player->SetMap(&map);
}

void StartGame::OnDisable()
{
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

void StartGame::Update(const float dt)
{
	player->Update(dt);
	//player->DoCollision(weapons);
	//GameObject a = weapons->at(5);
	//Weapon b = a;
}

void StartGame::ProcessInput(const float dt)
{
	if (InputManager::isKeyDown(GLFW_KEY_ESCAPE))
	{
		Game::SetGameState(GameState::MENU);
	}
	if (InputManager::isKeyUp(GLFW_KEY_ESCAPE))
	{
	}
	if (InputManager::isKeyDown(GLFW_KEY_Q))
	{
		this->weapons.at(1).SetParent(player.get());
	}
	if (InputManager::isKeyDown(GLFW_KEY_E))
	{
		this->weapons.at(1).RemoveParent();
	}
	player->ProcessInput(dt);
}

void StartGame::Render(const float dt)
{
	camera->setPosition(Vector2(player->GetPositionOfCenter().x - Game_Parameters::SCREEN_WIDTH / 2, player->GetPositionOfCenter().y - Game_Parameters::SCREEN_HEIGHT / 2));

	renderer.SetProjection(camera->cameraMatrix);
	map.Draw(renderer);
	int temp = weapons.size();
	for (int i = 0; i < temp; i++)
	{
		this->weapons.at(i).DrawModel(this->renderer);
	}
	player->DrawModel(renderer);

	//label->Draw(*textRenderer);

	//button->Draw(*squareRenderer, *buttonRenderer, *textRenderer);
}

StartGame::~StartGame() = default;