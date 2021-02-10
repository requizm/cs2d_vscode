#include "StartGame.hpp"

StartGame::StartGame() = default;

void StartGame::Initialize(const std::string &mapName)
{
	this->map = new Map(mapName.c_str(), mapName.c_str());
	this->renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	this->camera = new Camera(static_cast<int>(Game_Parameters::SCREEN_WIDTH), static_cast<int>(Game_Parameters::SCREEN_HEIGHT));
	this->textRenderer = new TextRenderer(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	this->textRenderer->Load("../../resources/fonts/liberationsans.ttf", 20);
	this->squareRenderer = SquareRenderer(true);

	this->SetEnable(true);
}

void StartGame::Start()
{
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
	player->SetMap(map);
	player->SetPosition(Vector2<int>(Game_Parameters::SCREEN_WIDTH / 2, Game_Parameters::SCREEN_HEIGHT / 2));
	player->setVelocity(500);

	camera->setPosition(Vector2(player->GetPositionOfCenter().x - Game_Parameters::SCREEN_WIDTH / 2, player->GetPositionOfCenter().y - Game_Parameters::SCREEN_HEIGHT / 2));
	renderer->SetProjection(camera->cameraMatrix);
	squareRenderer.SetProjection(camera->cameraMatrix);

	for (auto &weapon : map->weapons)
	{
		weapon->camera = this->camera;
	}
}

void StartGame::OnDisable()
{
	if (renderer != nullptr)
		delete renderer;
	renderer = nullptr;
	if (textRenderer != nullptr)
		delete textRenderer;
	textRenderer = nullptr;
	if (map != nullptr)
		delete map;
	map = nullptr;
	if (player != nullptr)
		delete player;
	player = nullptr;
	if (camera != nullptr)
		delete camera;
	camera = nullptr;
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
	if (InputManager::isKeyDown(KeyboardKeys::KEY_ESCAPE))
	{
		Game::SetGameState(GameState::MENU);
		return;
	}
	if (InputManager::isKeyDown(KeyboardKeys::KEY_Q))
	{
		//this->weapons.at(1).SetParent(player.get());
	}
	if (InputManager::isKeyDown(KeyboardKeys::KEY_E))
	{
		//this->weapons.at(1).RemoveParent();
	}
	player->ProcessInput();
}

void StartGame::Render()
{
	map->Draw(*renderer);
	player->DrawModel(*renderer);

	Vector2 p = Utils::ScreenToWorld(camera->view, InputManager::mousePos);
	this->textRenderer->RenderText("mouse: " + std::to_string(p.x) + " - " + std::to_string(p.y), Vector2(700, 15), 1.0F, 0.5F);
	this->textRenderer->RenderText("player matrix: " + std::to_string(player->GetTransform().values[12]) + " - " + std::to_string(player->GetTransform().values[13]), Vector2(700, 45), 1.0F, 0.5F);
	this->textRenderer->RenderText("player pos: " + player->GetPosition().ToString(), Vector2(700, 75), 1.0F, 0.5F);
	this->textRenderer->RenderText("player cell: " + player->GetCellPos().ToString(), Vector2(700, 105), 1.0F, 0.5F);
	this->textRenderer->RenderText("fps: " + std::to_string(InputManager::m_fps), Vector2(700, 135), 1.0F, 0.5F);

	squareRenderer.world_RenderEmptyCircle(player->collider.GetPosition(), Vector2<int>(player->collider.radius), Vector3<float>(0, 0, 0));
	//label->Draw(*textRenderer);

	//button->Draw(*squareRenderer, *buttonRenderer, *textRenderer);
}

StartGame::~StartGame()
{
	OnDisable();
}