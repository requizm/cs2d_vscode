#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "../Manager/Timer.hpp"
#include "../Renderer/Sprite.hpp"
#include "../Renderer/SpriteRenderer.hpp"
#include "../Renderer/SquareRenderer.hpp"
#include "Label.hpp"

class TextBox : public Label
{
   public:
    TextBox();

    /**
     * @brief Construct a new TextBox
     *
     * @param position
     * @param renderer
     * @param size
     * @param isBackGround false
     * @param scale 1.0F
     * @param color Vector3<float>(1.0F)
     */
    TextBox(Vector2<int> position, TextRenderer &renderer, Vector2<int> size,
            bool isBackGround = false, float scale = 1.0F,
            const Vector3<float> &color = Vector3<float>(1.0F));

    ~TextBox() final;

    void Update() override;
    void Draw(SpriteRenderer &spriteRenderer,
              SquareRenderer &squareRenderer) override;

    void OnEnable() override;
    void OnDisable() override;

    void setText(const std::string &text) override;

    bool isMouseHover() override;
    bool isMouseDown() override;
    bool isMouseUp() override;
    bool isMousePress() override;

    bool isMouseHoverM() override;
    bool isMouseDownM(MouseKeys key) override;
    bool isMouseUpM(MouseKeys key) override;
    bool isMousePressM(MouseKeys key) override;

    bool editable;
    bool editMode;
    bool isBackGround;

   private:
    float time = 0.0F;
    Sprite cursor;  // refactor: bunun optimize bir yol oldugundan emin degilim
    Vector3<float> currentBorderColor, hoverBorderColor, clickBorderColor,
        borderColor;
    bool click = false;

    void InputText();
};

#endif  // TEXTBOX_H