#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include "Renderers/SpriteRenderer.h"
#include "Models/GameObject.h"
#include "Models/Map.h"
#include "Models/Camera.h"
#include "Models/Player.h"
#include <memory>
#include "Scenes/StartGame.h"
#include "Managers/ResourceManager.h"
#include "Others/Game_Parameters.h"
//#include "Menu.h"
//#include "Editor.h"

class Game
{
public:

	Game(GLuint width, GLuint height);
	Game();
	virtual ~Game();

	void Init();
	void Update(const float dt) const;
	void Render(const float dt) const;
	void ProcessInput(const float dt);
	void NewGame();
	void initTextures() const;
	void initMaps();
	void initRenderers();
	void initShaders() const;

private:
	//std::unique_ptr<SpriteRenderer> renderer;

	std::shared_ptr<SpriteRenderer> spriteRenderer;
	std::shared_ptr<SpriteRenderer> textRenderer;
	//std::shared_ptr<TextRenderer> textRenderer;
	Camera camera;
	//Label *label;
	//std::shared_ptr<std::vector<Map>> maps;

	std::vector<Map> maps;
	std::vector<Weapon> weapons;

	//std::vector<GameObject*> gameobjects;

	//std::shared_ptr<std::vector<Weapon*>> weapons;
	//std::vector<std::shared_ptr<Weapon>> weapons;
	//std::vector<std::shared_ptr<Sprite>> pointers;
	Sprite mouseSprite;
	std::unique_ptr<StartGame> scene;
	//std::unique_ptr <Menu> menu;
	//std::unique_ptr <Editor> editor;
	GameState state;
	

	//std::map<std::string, Sprite> menuSprites;

	//Weapon *main1, *main2, *main3, *pistol1, *pistol2, *pistol3, *pistol4, *knife1, *knife2;
	void initMenuSprites();
};

#endif // GAME_H