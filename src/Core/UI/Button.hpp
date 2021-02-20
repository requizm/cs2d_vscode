#ifndef BUTTON_H
#define BUTTON_H

#include "../../CS2D/Other/GameParameters.hpp"
#include "../Manager/ObjectManager.hpp"
#include "../Model/Tile.hpp"
#include "../Renderer/Sprite.hpp"
#include "../Renderer/SpriteRenderer.hpp"
#include "../Renderer/SquareRenderer.hpp"
#include "Label.hpp"


enum ButtonType
{
    DEFAULT,  // standart button
    TILE,     // editor'deki build tile'ları gibi
    SPRITE,   // editor'deki save button'ı gibi
    ENV_OBJ   // editor'deki env objesi gibi
};

class Button : public Label
{
   public:
    Button();

    /**
     * @brief Construct a new Default Button also RadioButton and ListItem
     * elements
     *
     * @param text
     * @param position
     * @param size
     * @param renderer
     * @param buttonColor Vector3<float>(1.0F)
     * @param textColor Vector3<float>(0.0F)
     * @param scale 1.0F
     * @param type UIObjectType::TEXTBUTTON
     */
    Button(const std::string &text, Vector2<int> position, Vector2<int> size,
           TextRenderer &renderer,
           const Vector3<float> &buttonColor = Vector3<float>(1.0F),
           const Vector3<float> &textColor = Vector3<float>(0.0F),
           float scale = 1.0F, UIObjectType type = UIObjectType::TEXTBUTTON);

    /**
     * @brief Construct a new Sprite Button
     *
     * @param sprite
     * @param position
     * @param size
     * @param difColor false
     * @param scale 1.0F
     * @param type UIObjectType::TEXTBUTTON
     */
    Button(const Sprite &sprite, Vector2<int> position, Vector2<int> size,
           bool difColor = false, float scale = 1.0F,
           UIObjectType type = UIObjectType::TEXTBUTTON);

    /**
     * @brief Construct a new Tile Button for tile objects
     *
     * @param tile
     * @param scale 1.0F
     * @param type UIObjectType::TEXTBUTTON
     */
    Button(Tile &tile, float scale = 1.0F,
           UIObjectType type = UIObjectType::TEXTBUTTON);
    virtual ~Button();

    void Draw(SpriteRenderer &spriteRenderer,
              SquareRenderer &squareRenderer) override;

    /**
     * Bu fonksiyon sadece editor'deki uiButton'lar icin kullanilacak!
     */
    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer,
              float shine, bool selected, float time);
    void Draw() override;
    virtual void Update() override;
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

    void setPosition(const Vector2<int> &position) override;

    bool isMouseHover() override;
    bool isMouseDown() override;
    bool isMouseUp() override;
    bool isMousePress() override;

    void setType(ButtonType type);
    void setTile(Tile tile);

    bool center = true;

   protected:
    Sprite sprite;
    Tile tile;
    Vector3<float> buttonColor;
    Vector3<float> mouseHoverColor;
    Vector3<float> mouseclickColor;
    Vector3<float> currentColor;

    bool isMouseHoverM() override;
    bool isMouseDownM(MouseKeys key) override;
    bool isMouseUpM(MouseKeys key) override;
    bool isMousePressM(MouseKeys key) override;

    virtual void onMouseDown() override;
    virtual void onMouseUp() override;

    ButtonType btn_type = ButtonType::DEFAULT;

   private:
    // bool isDown = false;

    // bool haveTile;
    bool haveOutline = true;
    // bool haveSprite;

    bool difColor = false;

    Vector3<float> outlineColor;
    Vector2<int> margin;
    int a = 9988;
};

#endif  // BUTTON_H