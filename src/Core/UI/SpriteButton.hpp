#ifndef SPRITEBUTTON_H
#define SPRITEBUTTON_H

#include "../Renderer/Sprite.hpp"
#include "UIObject.hpp"


class SpriteButton : public UIObject
{
   public:
    SpriteButton(const Sprite &sprite, const Vector2<int> &position, const Vector2<int> &size, bool listenerEnabled = false, bool difColor = false, float scale = 1.0F);
    ~SpriteButton();

    void Update() final;
    void ProcessInput() final;
    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) final;

    bool IsMouseDown();
    bool IsMousePress();

    Vector2<int> getSize() final;

    void setPosition(const Vector2<int> &position) final;

    void setButtonCurrentColor(const Vector3<float> &value);

    void setButtonColor(const Vector3<float> &value);

    void setButtonHoverColor(const Vector3<float> &value);

    void setButtonClickColor(const Vector3<float> &value);

    void setOutlineColor(const Vector3<float> &value);

    void setMargin(const Vector2<int> &value);

    void setSprite(const Sprite &value);

    void setHaveOutline(bool value);

    void addListenerDown(std::function<void()> func);
    void addListenerUp(std::function<void()> func);


   private:
    Vector3<float> buttonCurrentColor = Vector3<float>(1.0F);
    Vector3<float> buttonColor = Vector3<float>(1.0F);
    Vector3<float> buttonHoverColor = Vector3<float>(1.0F);
    Vector3<float> buttonClickColor = Vector3<float>(1.0F);
    Vector3<float> outlineColor = Vector3<float>(1.0F);

    Sprite sprite;
    Vector2<int> margin = Vector2<int>(0);

    Vector2<int> spritePos = Vector2<int>(1);

    bool haveOutline = true;

    bool listenerEnabled;
    std::vector<std::function<void()>> listenersDown, listenersUp;
    std::function<void()> mDown;
    std::function<void()> mUp;

    bool isMouseHover();

    void onMouseDown();
    void onMouseUp();
};


#endif  // SPRITEBUTTON_H