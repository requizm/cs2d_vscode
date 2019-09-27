#include "Game.h"
#include "Others/Logger.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Game::Game(const GLuint width, const GLuint height)
{
	//camera = std::make_unique<Camera>(width, height);
	//camera = Camera(static_cast<int>(width), static_cast<int>(height));
	//camera = Camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f));
	//InputManager::Width = width;
	//InputManager::Height = height;
	Logger::WriteLog("Game->Game()");
	Game_Parameters::LoadParameters();
	state = GameState::MENU;
}

Game::Game()
{
	Logger::WriteLog("Game->Game()");
	Game_Parameters::LoadParameters();
	state = GameState::MENU;
}

Game::~Game()
{
}

void Game::Init()
{
	Logger::WriteLog("Game->Init()");
	initTextures();
	initShaders();
	initRenderers();
	initMaps();
	initMenuSprites();
	//weapons = std::vector<std::shared_ptr<Weapon>>();
	//menu = std::make_unique<Menu>(&menuSprites, textRenderer.get());
	//menu->Init();
	//editor = std::make_unique<Editor>(textRenderer.get());
	//editor->Init();
	NewGame();
	//GameObject *asd = new Player();
	//	Player *p = (Player*)asd;
}

void Game::Update(float dt) const
{
	scene->Update(dt);
	/*for (std::vector<int>::size_type i = 0; i != weapons.size(); i++)
	{
		const GameObject *a = &weapons[0];
		const Tile *pt = dynamic_cast<const Tile *>(a);
		if (pt == NULL)
		{
			std::cout << "NULL" << std::endl;
		}
		const Weapon *pt1 = dynamic_cast<const Weapon *>(a);
		if (pt1 == NULL)
		{
		}
		//std::cout << typeid(pt1).name() << std::endl;
	}*/

	//player->Update(dt);
	/*main1->Update(dt);
	main2->Update(dt);
	main3->Update(dt);
	pistol1->Update(dt);
	pistol2->Update(dt);
	pistol3->Update(dt);
	pistol4->Update(dt);
	knife1->Update(dt);
	knife2->Update(dt);*/
	//menu->Update(dt);
	//editor->Update(dt);
}

void Game::ProcessInput(float dt)
{
	//player->ProcessInput(dt); //also docollider
	scene->ProcessInput(dt);
	//menu->ProcessInput(dt);
	//editor->ProcessInput(dt);
}

void Game::NewGame()
{
	Logger::WriteLog("Game->NewGame()");
	Sprite awp = Sprite(ResourceManager::GetTexture("awp"));
	Sprite awp_d = Sprite(ResourceManager::GetTexture("awp_d"));
	Sprite famas = Sprite(ResourceManager::GetTexture("famas"));
	Sprite famas_d = Sprite(ResourceManager::GetTexture("famas_d"));
	Sprite ak47 = Sprite(ResourceManager::GetTexture("ak47"));
	Sprite ak47_d = Sprite(ResourceManager::GetTexture("ak47_d"));
	/*Sprite deagle = Sprite(ResourceManager::GetTexture("deagle"));
	Sprite deagle_d = Sprite(ResourceManager::GetTexture("deagle_d"));
	Sprite usp = Sprite(ResourceManager::GetTexture("usp"));
	Sprite usp_d = Sprite(ResourceManager::GetTexture("usp_d"));
	Sprite fiveseven = Sprite(ResourceManager::GetTexture("fiveseven"));
	Sprite fiveseven_d = Sprite(ResourceManager::GetTexture("fiveseven_d"));
	Sprite glock = Sprite(ResourceManager::GetTexture("glock"));
	Sprite glock_d = Sprite(ResourceManager::GetTexture("glock_d"));
	Sprite knife = Sprite(ResourceManager::GetTexture("knife"));
	Sprite machete = Sprite(ResourceManager::GetTexture("machete"));*/

	std::shared_ptr<Weapon> main1 = std::make_shared<Weapon>(
		glm::vec2(20.0f, 30.0f), awp, awp_d, "awp", WeaponType::MAIN, 30, 20, 10, 10);
	std::shared_ptr<Weapon> main2 = std::make_shared<Weapon>(
		glm::vec2(80.0f, 30.0f), famas, famas_d, "famas", WeaponType::MAIN, 30, 20, 10, 10);
	std::shared_ptr<Weapon> main3 = std::make_shared<Weapon>(
		glm::vec2(120.0f, 30.0f), ak47, ak47_d, "ak47", WeaponType::MAIN, 30, 20, 10, 10);
	/*Weapon* pistol1 = new Weapon(
		glm::vec2(170.0f, 30.0f), deagle, deagle_d, "deagle", WeaponType::PISTOL, 30, 20, 10, 10
	);
	Weapon* pistol2 = new Weapon(
		glm::vec2(260.0f, 30.0f), usp, usp_d, "usp", WeaponType::PISTOL, 30, 20, 10, 10
	);
	Weapon* pistol3 = new Weapon(
		glm::vec2(320.0f, 30.0f), fiveseven, fiveseven_d, "fiveseven", WeaponType::PISTOL, 30, 20, 10, 10
	);
	Weapon* pistol4 = new Weapon(
		glm::vec2(20.0f, 90.0f), glock, glock_d, "glock", WeaponType::PISTOL, 30, 20, 10, 10
	);

	Weapon* knife1 = new Weapon(
		glm::vec2(20.0f, 150.0f), knife, knife, "knife", WeaponType::KNIFE, 30, 20, 10, 10
	);
	Weapon* knife2 = new Weapon(
		glm::vec2(20.0f, 210.0f), machete, machete, "machete", WeaponType::KNIFE, 30, 20, 10, 10
	);*/
	/*weapons.push_back(main1);
	weapons.push_back(main2);
	weapons.push_back(main3);*/
	/*weapons.push_back(std::make_shared<Weapon>(*pistol1));
	weapons.push_back(std::make_shared<Weapon>(*pistol2));
	weapons.push_back(std::make_shared<Weapon>(*pistol3));
	weapons.push_back(std::make_shared<Weapon>(*pistol4));
	weapons.push_back(std::make_shared<Weapon>(*knife1));
	weapons.push_back(std::make_shared<Weapon>(*knife1));*/
	weapons.push_back(*main1.get());
	weapons.push_back(*main2.get());
	weapons.push_back(*main3.get());

	/*gameobjects.push_back(main1.get());
	gameobjects.push_back(main2.get());
	gameobjects.push_back(main3.get());*/
	/*gameobjects.push_back(&pistol1);
	gameobjects.push_back(&pistol2);
	gameobjects.push_back(&pistol3);
	gameobjects.push_back(&pistol4);
	gameobjects.push_back(&knife1);
	gameobjects.push_back(&knife2);*/

	//scene = std::make_unique<StartGame>(&maps[0], &weapons, spriteRenderer.get());
	scene = std::make_unique<StartGame>(&maps[0], spriteRenderer.get(), weapons);
	scene->Init();

	//label = new Label("denememesaj", glm::vec2(0.0f));
	//label->setColor(glm::vec3(0.5F, 0.5F, 0.5F));

	/*player->addWeapon(*main1);
	player->addWeapon(*main2);
	player->addWeapon(*main3);
	player->addWeapon(*pistol1);
	player->addWeapon(*pistol2);
	player->addWeapon(*pistol3);
	player->addWeapon(*pistol4);
	player->addWeapon(*knife1);
	player->addWeapon(*knife2);*/
}

void Game::Render(const float dt) const
{
	//renderer->DrawSprite(Sprite(ResourceManager::GetTexture("buildings"), false, 32, 0, 32, 32), glm::vec2(700, 700), glm::vec2(55.0f, 55.0f), 0.0);
	//renderer->DrawSprite(ResourceManager::GetTexture("uc"), glm::vec2(101, 218), glm::vec2(28, 55), 40.0f);

	//player->DrawModel(*renderer);
	/*main1->DrawModel(*renderer);
	main2->DrawModel(*renderer);
	main3->DrawModel(*renderer);
	pistol1->DrawModel(*renderer);
	pistol2->DrawModel(*renderer);
	pistol3->DrawModel(*renderer);
	pistol4->DrawModel(*renderer);
	knife1->DrawModel(*renderer);
	knife2->DrawModel(*renderer);*/

	//menu->Render(dt);
	//editor->Render(dt);
	scene->Render(dt);
	textRenderer->DrawSprite(mouseSprite, glm::vec2(InputManager::mouseX, InputManager::mouseY), glm::vec2(Game_Parameters::SCREEN_HEIGHT / 35, Game_Parameters::SCREEN_HEIGHT / 35), true);
	//label->Draw(*textRenderer);
}

void Game::initTextures() const
{
	Logger::WriteLog("Game->initTextures()");
	//tiles
	ResourceManager::LoadTexture("../resources/textures/tiles/cs2dnorm.png", GL_TRUE, "cs2dnorm");

	//weapons
	ResourceManager::LoadTexture("../resources/textures/player/ct1.png", GL_TRUE, "ct1");
	ResourceManager::LoadTexture("../resources/textures/weapons/awp.png", GL_TRUE, "awp");
	ResourceManager::LoadTexture("../resources/textures/weapons/awp_d.png", GL_TRUE, "awp_d");
	ResourceManager::LoadTexture("../resources/textures/weapons/ak47.png", GL_TRUE, "ak47");
	ResourceManager::LoadTexture("../resources/textures/weapons/ak47_d.png", GL_TRUE, "ak47_d");
	ResourceManager::LoadTexture("../resources/textures/weapons/famas.png", GL_TRUE, "famas");
	ResourceManager::LoadTexture("../resources/textures/weapons/famas_d.png", GL_TRUE, "famas_d");
	/*ResourceManager::LoadTexture("../resources/textures/weapons/deagle.png", GL_TRUE, "deagle");
	ResourceManager::LoadTexture("../resources/textures/weapons/deagle_d.png", GL_TRUE, "deagle_d");
	ResourceManager::LoadTexture("../resources/textures/weapons/fiveseven.png", GL_TRUE, "fiveseven");
	ResourceManager::LoadTexture("../resources/textures/weapons/fiveseven_d.png", GL_TRUE, "fiveseven_d");
	ResourceManager::LoadTexture("../resources/textures/weapons/elite.png", GL_TRUE, "elite");
	ResourceManager::LoadTexture("../resources/textures/weapons/elite_d.png", GL_TRUE, "elite_d");
	ResourceManager::LoadTexture("../resources/textures/weapons/usp.png", GL_TRUE, "usp");
	ResourceManager::LoadTexture("../resources/textures/weapons/usp_d.png", GL_TRUE, "usp_d");
	ResourceManager::LoadTexture("../resources/textures/weapons/knife.png", GL_TRUE, "knife");
	ResourceManager::LoadTexture("../resources/textures/weapons/machete.png", GL_TRUE, "machete");*/

	//menuitems
	ResourceManager::LoadTexture("../resources/textures/pointer.png", GL_TRUE, "pointer");
	/*ResourceManager::LoadTexture("../resources/textures/cs2d.png", GL_TRUE, "cs2d");
	ResourceManager::LoadTexture("../resources/textures/gametitle.png", GL_TRUE, "gametitle");
	ResourceManager::LoadTexture("../resources/textures/unrealsoftware.png", GL_TRUE, "unrealsoftware");
	ResourceManager::LoadTexture("../resources/textures/splash.png", GL_FALSE, "splash");
	ResourceManager::LoadTexture("../resources/textures/cursor-spec.png", GL_TRUE, "textcursor");

	//GUIIcons
	ResourceManager::LoadTexture("../resources/textures/gui_icons.png", GL_TRUE, "gui_icons");*/
}

void Game::initShaders() const
{
	Logger::WriteLog("Game->initShaders()");
	//ResourceManager::LoadShader("../resources/shaders/textVertex.txt", "../resources/shaders/textFragment.txt", nullptr, "text");
	ResourceManager::LoadShader("../resources/shaders/spriteVertex.txt", "../resources/shaders/spriteFragment.txt", nullptr, "sprite");
	ResourceManager::LoadShader("../resources/shaders/spriteVertex.txt", "../resources/shaders/spriteFragment.txt", nullptr, "menu");
	//ResourceManager::LoadShader("../resources/shaders/spriteVertex.txt", "../resources/shaders/spriteFragment.txt", nullptr, "outline");
	ResourceManager::GetShader("sprite").Use();
	ResourceManager::GetShader("sprite").SetInteger("image", 0);
	ResourceManager::GetShader("sprite").UnUse();
	ResourceManager::GetShader("menu").Use();
	ResourceManager::GetShader("menu").SetMatrix4("projection", glm::ortho(0.0f, static_cast<GLfloat>(Game_Parameters::SCREEN_WIDTH), static_cast<GLfloat>(Game_Parameters::SCREEN_HEIGHT), 0.0f), GL_TRUE);
	ResourceManager::GetShader("menu").SetInteger("image", 0);
	ResourceManager::GetShader("menu").UnUse();
}

void Game::initMenuSprites()
{
	Logger::WriteLog("Game->initMenuSprites()");
	/*Sprite cs2d = Sprite(ResourceManager::GetTexture("cs2d"));
	Sprite unrealsoftware = Sprite(ResourceManager::GetTexture("unrealsoftware"));
	Sprite splash = Sprite(ResourceManager::GetTexture("splash"));
	//Sprite mouseSprite = Sprite(ResourceManager::GetTexture("pointer"), 0, 0, 46, 46);
	Sprite gametitle = Sprite(ResourceManager::GetTexture("gametitle"));*/
	mouseSprite = Sprite(ResourceManager::GetTexture("pointer"), 0, 0, 46, 46);

	/*menuSprites.insert(std::pair<std::string, Sprite>("unrealsoftware", unrealsoftware));
	menuSprites.insert(std::pair<std::string, Sprite>("cs2d", cs2d));
	menuSprites.insert(std::pair<std::string, Sprite>("gametitle", gametitle));
	//menuSprites.insert(std::pair<std::string, Sprite>("mouseSprite", mouseSprite));
	menuSprites.insert(std::pair<std::string, Sprite>("splash", splash));*/
}

void Game::initMaps()
{
	Logger::WriteLog("Game->initMaps()");
	maps = std::vector<Map>();
	const Map test_map = Map("../resources/levels/one.xml", "test_one");
	maps.push_back(test_map);
}

void Game::initRenderers()
{
	Logger::WriteLog("Game->initRenderers()");
	spriteRenderer = std::make_shared<SpriteRenderer>(ResourceManager::GetShader("sprite"));
	textRenderer = std::make_shared<SpriteRenderer>(ResourceManager::GetShader("menu"));
}