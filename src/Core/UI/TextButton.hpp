#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include <functional>

#include "UIObject.hpp"

class TextButton : public UIObject
{
   public:
    TextButton(const std::string &text, const Vector2<int> &position, const Vector2<int> &size, TextRenderer &renderer,
               const Vector3<float> &buttonColor = Vector3<float>(1.0F),
               const Vector3<float> &textColor = Vector3<float>(0.0F),
               float scale = 1.0F, bool listenerEnabled = false, UIObjectType type = UIObjectType::TEXTBUTTON);
    ~TextButton();

    void Update() final;
    void ProcessInput() final;
    void Draw(SquareRenderer &squareRenderer) final;

    bool IsMouseDown();
    bool IsMousePress();

    void setPosition(const Vector2<int> &position) final;
    void setLocalPosition(const Vector2<int> value) final;

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

    void setDrawCenter(bool value);

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
    bool drawCenter = true;

    Vector2<int> textSize = Vector2<int>(1);
    Vector2<int> textPos = Vector2<int>(1);

    bool listenerEnabled;
    std::vector<std::function<void()>> listenersDown, listenersUp;
    std::function<void()> mDown;
    std::function<void()> mUp;

    virtual bool isMouseHover();

    virtual void onMouseDown();
    virtual void onMouseUp();
};


#endif  // TEXTBUTTON_H