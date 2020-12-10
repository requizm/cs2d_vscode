#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "Label.hpp"
#include "../../Renderers/SquareRenderer.hpp"
#include "../../Renderers/SpriteRenderer.hpp"
#include "../Sprite.hpp"

//class SpriteRenderer;

class TextBox : public Label
{
public:
	TextBox();
	TextBox(Vector2<float> position, TextRenderer &renderer, Vector2<float> size, bool isBackGround = false, float scale = 1.0F, Vector3<float> color = Vector3<float>(1.0F));

	void Update() override;
	void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer);

	void OnEnable() override;
	void OnDisable() override;

	void setText(const std::string &text) override;

	bool isMouseHover() override;
	bool isMouseDown() override;
	bool isMouseUp() override;
	bool isMousePress() override;

	bool isMouseHoverM() override;
	bool isMouseDownM(const int key) override;
	bool isMouseUpM(const int key) override;
	bool isMousePressM(const int key) override;

	bool editable;
	bool editMode;
	bool isBackGround;

	Square square;


private:
	float time = 0.0F;
	Sprite cursor; //refactor: bunun optimize bir yol oldugundan emin degilim
	Vector3<float> currentBorderColor, hoverBorderColor, clickBorderColor, borderColor;
	bool click = false;

	void InputText();
};

#endif //TEXTBOX_H