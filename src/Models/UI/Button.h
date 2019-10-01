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
	Button(const Sprite &sprite, glm::vec2 position, glm::vec2 size, float scale = 1.0F);
	Button(Tile tile, float scale = 1.0F);
	~Button();

	void Draw(SpriteRenderer &spriteRenderer) const;
	void Draw(/*SquareRenderer &squareRenderer */ /*ButtonRenderer &buttonRenderer,*/) const;
	void Update(const float dt) override;

	glm::vec2 getPosition() const override;
	glm::vec2 getSize() const override;
	bool isMouseHover() override;
	bool isMouseDown(int key) override;
	bool isMouseUp(int key) override;
	bool isMousePress(int key) override;

	void setMouseHoverColor(const glm::vec3 color);
	void setButtonColor(const glm::vec3 color);
	void setMouseClickColor(const glm::vec3 color);

protected:
	Sprite sprite;
	Square square = Square();
	Tile tile;
	glm::vec3 buttonColor;
	glm::vec3 mouseHoverColor;
	glm::vec3 mouseclickColor;
	glm::vec3 currentColor;

private:
	//bool isDown = false;
	bool haveTile = false;
};

#endif // BUTTON_H