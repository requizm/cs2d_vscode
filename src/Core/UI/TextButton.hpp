#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "UIObject.hpp"

enum TextAlign
{
    T_LEFT,
    T_CENTER,
    T_RIGHT
};

class TextButton : public UIObject
{
   public:
    TextButton(const std::string &text, const Vector2<int> &position, const Vector2<int> &size, TextRenderer &renderer,
               const Vector3<float> &buttonColor = Vector3<float>(1.0F),
               const Vector3<float> &textColor = Vector3<float>(0.0F),
               float scale = 1.0F, UIObjectType type = UIObjectType::TEXTBUTTON);
    TextButton(const std::string &text, const Vector2<int> &position, const Vector2<int> &size, TextRenderer &renderer, Object *par, const Vector3<float> &buttonColor = Vector3<float>(1.0F), const Vector3<float> &textColor = Vector3<float>(0.0F), float scale = 1.0F, UIObjectType type = UIObjectType::TEXTBUTTON);
    ~TextButton();

    void Update() final;
    void ProcessInput() final;
    void Draw(SquareRenderer &squareRenderer) final;
    void SetTransform(const Matrix4<float> &value) final;

    void SetPosition(const Vector2<int> &position) final;

    void setButtonColor(const Vector3<float> &value);

    void setButtonHoverColor(const Vector3<float> &value);

    void setButtonClickColor(const Vector3<float> &value);

    void setTextColor(const Vector3<float> &value);

    void setTextHoverColor(const Vector3<float> &value);

    void setTextClickColor(const Vector3<float> &value);

    void setOutlineColor(const Vector3<float> &value);


    std::string getText() const;
    void setText(const std::string &value);

    void setHaveOutline(bool value);

    void setTextAlign(TextAlign value);

    Vector2<int> getTextSize() const;

    Vector2<int> getTextPos() const;

    void addListenerDown(std::function<void()> func);
    void addListenerUp(std::function<void()> func);


   protected:
    Vector3<float> buttonCurrentColor = Vector3<float>(1.0F);
    Vector3<float> buttonColor = Vector3<float>(1.0F);
    Vector3<float> buttonHoverColor = Vector3<float>(1.0F);
    Vector3<float> buttonClickColor = Vector3<float>(1.0F);
    Vector3<float> outlineColor = Vector3<float>(1.0F);

    Vector3<float> textCurrentColor = Vector3<float>(1.0F);
    Vector3<float> textColor = Vector3<float>(1.0F);
    Vector3<float> textHoverColor = Vector3<float>(1.0F);
    Vector3<float> textClickColor = Vector3<float>(1.0F);

    std::string text;
    bool haveOutline = true;
    TextAlign textAlign = TextAlign::T_CENTER;

    Vector2<int> textSize = Vector2<int>(1);
    Vector2<int> textPos = Vector2<int>(1);

    std::vector<std::function<void()>> listenersDown, listenersUp;
    std::function<void()> mDown;
    std::function<void()> mUp;

    bool isMouseHover();

    void onMouseDown();
    void onMouseUp();
};


#endif  // TEXTBUTTON_H