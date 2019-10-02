#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Label.h"
#include "../../Renderers/SquareRenderer.h"
#include "../../Renderers/SpriteRenderer.h"
#include "../Sprite.h"

//class SpriteRenderer;

class TextBox : public Label
{
public:
	TextBox();
	TextBox(glm::vec2 position, TextRenderer &renderer, glm::vec2 size, bool isBackGround = false, float scale = 1.0F, glm::vec3 color = glm::vec3(1.0F));

	void Update(const float dt) override;
	void Draw(SquareRenderer &squareRenderer, SpriteRenderer &spriteRenderer);

	bool isMouseHover() override;
	bool isMouseDown(const int key) override;
	bool isMouseUp(const int key) override;
	bool isMousePress(const int key) override;

	bool isMouseHoverM() override;
	bool isMouseDownM(const int key) override;
	bool isMouseUpM(const int key) override;
	bool isMousePressM(const int key) override;

	bool editable;
	bool editMode;
	bool isBackGround;

	Square square;


private:
	std::string tempText;
	glm::vec2 tempTextSize;
	float time = 0.0F;
	Sprite cursor; //refactor: bunun optimize bir yol oldugundan emin degilim
	glm::vec3 currentBorderColor, hoverBorderColor, clickBorderColor, borderColor;

	void InputText(const float dt);
};

#endif //TEXTBOX_H