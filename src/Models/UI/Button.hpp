#ifndef BUTTON_H
#define BUTTON_H

#include "../../Renderers/SpriteRenderer.hpp"
#include "../../Renderers/SquareRenderer.hpp"
#include "Label.hpp"
#include "Square.hpp"
#include "../Sprite.hpp"
#include "../Tile.hpp"

//class ButtonRenderer;
//class TextRenderer;
//class SquareRenderer;

enum ButtonType
{
	DEFAULT, //standart buton
	TILE,	//editor'deki build tile'ları gibi
	SPRITE   //editor'deki save button'u gibi
};

class Button : public Label
{
public:
	Button();
	Button(const std::string &text, Vector2<float> position, Vector2<float> size, TextRenderer &renderer, Vector3<float> buttonColor = Vector3<float>(1.0F), Vector3<float> textColor = Vector3<float>(0.0F), float scale = 1.0F);
	Button(const Sprite &sprite, Vector2<float> position, Vector2<float> size, bool difColor = false, float scale = 1.0F);
	Button(Tile &tile, float scale = 1.0F);
	~Button();

	void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) override;

	/**
 	* Bu fonksiyon sadece editor'deki uiButton'lar icin kullanilacak!
 	*/
	void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer, float shine, bool selected, float time);
	void Draw() override;
	void Update() override;
	void ProcessInput() override;

	Vector2<float> getPosition() override;
	Vector2<float> getLocalPosition() override;
	Vector2<float> getSize() override;
	Tile *getTile();

	void setMouseHoverColor(const Vector3<float> color);
	void setButtonColor(const Vector3<float> color);
	void setMouseClickColor(const Vector3<float> color);
	void setOutlineColor(const Vector3<float> color);
	void setOutline(const bool value);

	void setMargin(const Vector2<float> value);

	void setPosition(const Vector2<float> position) override;
	void setPosition(const int x, const int y) override;

	bool isMouseHover() override;
	bool isMouseDown() override;
	bool isMouseUp() override;
	bool isMousePress() override;

	bool center = true;

protected:
	Sprite sprite;
	Square square;
	Tile tile;
	Vector3<float> buttonColor;
	Vector3<float> mouseHoverColor;
	Vector3<float> mouseclickColor;
	Vector3<float> currentColor;

	bool isMouseHoverM() override;
	bool isMouseDownM(const int key) override;
	bool isMouseUpM(const int key) override;
	bool isMousePressM(const int key) override;

private:
	//bool isDown = false;

	//bool haveTile;
	bool haveOutline = true;
	//bool haveSprite;

	bool difColor = false;

	Vector3<float> outlineColor;
	Vector2<float> margin;
	ButtonType type = ButtonType::DEFAULT;
};

#endif // BUTTON_H