#ifndef BUTTON_H
#define BUTTON_H

#include "../../Renderers/SpriteRenderer.h"
//#include "SquareRenderer.h"
#include "Label.h"
#include "Square.h"
#include "../Sprite.h"
//#include "ButtonRenderer.h"
#include "../Tile.h"

//class ButtonRenderer;
//class TextRenderer;
//class SquareRenderer;

class Button : public Label
{
public:
	Button();
	//Button(Sprite sprite, std::string text, glm::vec2 position, float scale = 1.0F, glm::vec3 textColor = glm::vec3(0.0F));
	Button(const std::string &text, glm::vec2 position, TextRenderer &renderer, glm::vec3 buttonColor = glm::vec3(1.0F), glm::vec3 textColor = glm::vec3(0.0F), float scale = 1.0F);
	Button(const Sprite &sprite, glm::vec2 position, glm::vec2 size, bool difColor = false, float scale = 1.0F);
	Button(Tile tile, float scale = 1.0F);
	~Button();

	void Draw(SpriteRenderer &spriteRenderer);
	void Draw(/*SquareRenderer &squareRenderer */ /*ButtonRenderer &buttonRenderer,*/);
	void Update(const float dt) override;

	glm::vec2 getPosition() override;
	glm::vec2 getLocalPosition() override;
	glm::vec2 getSize() override;
	Tile getTile();

	void setMouseHoverColor(const glm::vec3 color);
	void setButtonColor(const glm::vec3 color);
	void setMouseClickColor(const glm::vec3 color);

	void setPosition(const glm::vec2 position) override;
	void setPosition(const int x, const int y) override;

	bool isMouseHover() override;
	bool isMouseDown(int key) override;
	bool isMouseUp(int key) override;
	bool isMousePress(int key) override;

protected:
	Sprite sprite;
	Square square;
	Tile tile;
	glm::vec3 buttonColor;
	glm::vec3 mouseHoverColor;
	glm::vec3 mouseclickColor;
	glm::vec3 currentColor;

	bool isMouseHoverM() override;
	bool isMouseDownM(int key) override;
	bool isMouseUpM(int key) override;
	bool isMousePressM(int key) override;

private:
	//bool isDown = false;
	bool haveTile = false;
	bool difColor = false;
};

#endif // BUTTON_H