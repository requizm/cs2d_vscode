#ifndef BUTTON_H
#define BUTTON_H

#include "../../Renderers/SpriteRenderer.h"
#include "../../Renderers/SquareRenderer.h"
#include "Label.h"
#include "Square.h"
#include "../Sprite.h"
#include "../Tile.h"

//class ButtonRenderer;
//class TextRenderer;
//class SquareRenderer;

class Button : public Label
{
public:
	Button();
	Button(const std::string &text, glm::vec2 position, TextRenderer &renderer, glm::vec3 buttonColor = glm::vec3(1.0F), glm::vec3 textColor = glm::vec3(0.0F), float scale = 1.0F);
	Button(const Sprite &sprite, glm::vec2 position, glm::vec2 size, bool difColor = false, float scale = 1.0F);
	Button(Tile &tile, float scale = 1.0F);
	~Button();

	void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer);

	/**
 	* Bu fonksiyon sadece editor'deki uiButton'lar icin kullanilacak!
 	*/ 
	void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer, float shine, float dt, bool selected);
	void Draw();
	void Update(const float dt) override;
	void ProcessInput() override;

	glm::vec2 getPosition() override;
	glm::vec2 getLocalPosition() override;
	glm::vec2 getSize() override;
	Tile getTile();

	void setMouseHoverColor(const glm::vec3 color);
	void setButtonColor(const glm::vec3 color);
	void setMouseClickColor(const glm::vec3 color);
	void setOutlineColor(const glm::vec3 color);
	void setOutline(const bool value);

	void setMargin(const glm::vec2 value);

	void setPosition(const glm::vec2 position) override;
	void setPosition(const int x, const int y) override;

	bool isMouseHover() override;
	bool isMouseDown() override;
	bool isMouseUp() override;
	bool isMousePress() override;

protected:
	Sprite sprite;
	Square square;
	Tile tile;
	glm::vec3 buttonColor;
	glm::vec3 mouseHoverColor;
	glm::vec3 mouseclickColor;
	glm::vec3 currentColor;

	bool isMouseHoverM() override;
	bool isMouseDownM(const int key) override;
	bool isMouseUpM(const int key) override;
	bool isMousePressM(const int key) override;

private:
	//bool isDown = false;
	bool haveTile;
	bool haveOutline;
	bool haveSprite;
	bool difColor;

	glm::vec3 outlineColor;
	glm::vec2 margin;
};

#endif // BUTTON_H