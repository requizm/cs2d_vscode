#ifndef BUTTON_H
#define BUTTON_H

#include "../../Renderers/SpriteRenderer.hpp"
#include "../../Renderers/SquareRenderer.hpp"
#include "Label.hpp"
#include "../Sprite.hpp"
#include "../Tile.hpp"

enum ButtonType
{
	DEFAULT, //standart button
	TILE,	 //editor'deki build tile'ları gibi
	SPRITE,	 //editor'deki save button'ı gibi
	ENV_OBJ	 //editor'deki env objesi gibi
};

class Button : public Label
{
public:
	Button();

	/**
	 * @brief Construct a new Default Button also RadioButton and ListItem elements
	 * 
	 * @param text 
	 * @param position 
	 * @param size 
	 * @param renderer 
	 * @param buttonColor Vector3<float>(1.0F)
	 * @param textColor Vector3<float>(0.0F)
	 * @param scale 1.0F
	 * @param type UIObjectType::BUTTON
	 */
	Button(const std::string &text, Vector2<int> position, Vector2<int> size, TextRenderer &renderer, const Vector3<float> &buttonColor = Vector3<float>(1.0F), const Vector3<float> &textColor = Vector3<float>(0.0F), float scale = 1.0F, UIObjectType type = UIObjectType::BUTTON);

	/**
	 * @brief Construct a new Sprite Button
	 * 
	 * @param sprite 
	 * @param position 
	 * @param size 
	 * @param difColor false
	 * @param scale 1.0F
	 * @param type UIObjectType::BUTTON
	 */
	Button(const Sprite &sprite, Vector2<int> position, Vector2<int> size, bool difColor = false, float scale = 1.0F, UIObjectType type = UIObjectType::BUTTON);

	/**
	 * @brief Construct a new Tile Button for tile objects
	 * 
	 * @param tile 
	 * @param scale 1.0F
	 */
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

	Vector2<int> getPosition() override;
	Vector2<int> getLocalPosition() override;
	Vector2<int> getSize() override;
	Tile *getTile();

	void setMouseHoverColor(const Vector3<float> &color);
	void setButtonColor(const Vector3<float> &color);
	void setMouseClickColor(const Vector3<float> &color);
	void setOutlineColor(const Vector3<float> &color);
	void setOutline(const bool value);

	void setMargin(const Vector2<int> value);

	void setPosition(const Vector2<int> position) override;
	void setPosition(const int x, const int y) override;

	bool isMouseHover() override;
	bool isMouseDown() override;
	bool isMouseUp() override;
	bool isMousePress() override;

	void setType(ButtonType type);

	bool center = true;

protected:
	Sprite sprite;
	Tile tile;
	Vector3<float> buttonColor;
	Vector3<float> mouseHoverColor;
	Vector3<float> mouseclickColor;
	Vector3<float> currentColor;

	bool isMouseHoverM() override;
	bool isMouseDownM(const int key) override;
	bool isMouseUpM(const int key) override;
	bool isMousePressM(const int key) override;

	void onMouseDown() override;
	void onMouseUp() override;

private:
	//bool isDown = false;

	//bool haveTile;
	bool haveOutline = true;
	//bool haveSprite;

	bool difColor = false;

	Vector3<float> outlineColor;
	Vector2<int> margin;
	ButtonType type = ButtonType::DEFAULT;
};

#endif // BUTTON_H