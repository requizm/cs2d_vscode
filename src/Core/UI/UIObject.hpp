#ifndef UIOBJECT_H
#define UIOBJECT_H

#include <algorithm>
#include <iostream>
#include <memory>

#include "../Manager/Logger.hpp"
#include "../Manager/Utils.hpp"
#include "../Model/Object.hpp"
#include "../Renderer/SpriteRenderer.hpp"
#include "../Renderer/SquareRenderer.hpp"
#include "../Renderer/TextRenderer.hpp"


enum class UIObjectType
{
    UIOBJECT,
    LABEL,
    TEXTBOX,
    TEXTBUTTON,
    SPRITEBUTTON,
    TILEBUTTON,
    PANEL,
    RADIOBUTTON,
    LISTITEM,
    LISTITEMELEMENT,
    ENV_ITEM
};
// class TextRenderer;

class UIObject : public Object
{
   public:
    UIObject();
    UIObject(UIObjectType type);
    UIObject(UIObjectType type, Object *par);
    UIObject(Vector2<int> position, Vector2<int> size, float scale,
             TextRenderer &renderer);
    UIObject(Vector2<int> position, Vector2<int> size, float scale,
             TextRenderer &renderer, Object *par);
    UIObject(Vector2<int> position, Vector2<int> size, float scale,
             TextRenderer &renderer, UIObjectType type);
    UIObject(Vector2<int> position, Vector2<int> size, float scale,
             TextRenderer &renderer, UIObjectType type, Object *par);
    UIObject(Vector2<int> position, Vector2<int> size, float scale);
    UIObject(Vector2<int> position, Vector2<int> size, float scale, Object *par);
    UIObject(Vector2<int> position, Vector2<int> size, float scale,
             UIObjectType type);
    UIObject(Vector2<int> position, Vector2<int> size, float scale,
             UIObjectType type, Object *par);
    virtual ~UIObject();

    virtual void Update();
    virtual void OnEnable();
    virtual void OnDisable();
    virtual void ProcessInput();
    virtual void Draw();
    virtual void Draw(SquareRenderer &squareRenderer);
    virtual void Draw(SpriteRenderer &spriteRenderer,
                      SquareRenderer &squareRenderer);

    void SetPosition(const Vector2<int> &value) override;
    void SetSize(const Vector2<int> &value) override;
    void SetLocalPosition(const Vector2<int> &value) override;
    void SetParent(Object *value) final;
    void SetTransform(const Matrix4<float> &value) override;

    float GetScale() const;
    bool IsEnable() const;
    bool IsMouseEvents() const;
    bool IsRenderable();  // scroll'dan dolayi
    bool IsScrollable() const;

    virtual void SetParentCenterPos();
    void SetScale(const float value);
    void SetEnable(const bool value);
    void SetMouseEvent(const bool value);
    void SetScrollable(const bool value);

    std::string GetObjectTypeString();

    bool isPressed = false;

    /**
     * update, processinput, draw gibi fonksiyonlar, parent içinde
     * gerceklesmeyecek
     */
    bool independent = false;

    TextRenderer *rend = nullptr;

   protected:
    float scale = 1.0F;
    UIObjectType objType = UIObjectType::UIOBJECT;

    /**
     * visible, enable ve mouseEvent degiskenleri parent'a bagli olsun
     */
    bool dependParent = false;

    bool visible = true;
    bool enable = true;
    bool mouseEvents = true;

    bool scrollable = false;

    bool isDown = false;
    bool isUp = false;
};

#endif  // UIOBJECT_H