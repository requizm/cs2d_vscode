#ifndef UIOBJECT_H
#define UIOBJECT_H

#include <algorithm>
#include <memory>

#include "../Manager/Logger.hpp"
#include "../Manager/Utils.hpp"
#include "../Renderer/SpriteRenderer.hpp"
#include "../Renderer/SquareRenderer.hpp"
#include "../Renderer/TextRenderer.hpp"


enum class UIObjectType
{
    UIOBJECT,
    LABEL,
    TEXTBOX,
    BUTTON,
    PANEL,
    RADIOBUTTON,
    LISTITEM,
    ENV_ITEM
};
// class TextRenderer;

class UIObject
{
   public:
    UIObject();
    UIObject(Vector2<int> position, Vector2<int> size, float scale,
             TextRenderer &renderer);
    UIObject(Vector2<int> position, Vector2<int> size, float scale,
             TextRenderer &renderer, UIObjectType type);
    UIObject(Vector2<int> position, Vector2<int> size, float scale);
    UIObject(Vector2<int> position, Vector2<int> size, float scale,
             UIObjectType type);
    UIObject(Vector2<int> position, float scale, TextRenderer &renderer);
    UIObject(Vector2<int> position, float scale, TextRenderer &renderer,
             UIObjectType type);
    UIObject(Vector2<int> position, float scale, UIObjectType type);
    virtual ~UIObject();

    virtual void Update();
    virtual void OnEnable();
    virtual void OnDisable();
    virtual void ProcessInput();
    virtual void Draw();
    virtual void Draw(SpriteRenderer &spriteRenderer,
                      SquareRenderer &squareRenderer);

    virtual Vector2<int> getPosition();
    virtual Vector2<int> getSize();
    virtual Vector2<int> getCenterPosition() const;
    virtual Vector2<int> getLocalPosition();
    UIObject *getParent() const;
    float getScale() const;
    bool isParent() const;
    bool isVisible() const;
    bool isEnable() const;
    bool isMouseEvents() const;
    bool isDependParent() const;
    int getID() const;
    bool isRenderable();  // scroll'dan dolayi
    bool isScrollable() const;

    virtual void setPosition(const Vector2<int> position);
    virtual void setPosition(const int x, const int y);
    virtual void setParentCenterPos();
    virtual void setSize(const Vector2<int> size);
    virtual void setSize(const int x, const int y);
    void setScale(const float scale);
    void setParent(UIObject *uiobject, bool dependParent = true);
    void removeParent();
    void setVisible(const bool value);
    void setEnable(const bool value);
    void setMouseEvent(const bool value);
    void setDependParent(const bool value);
    void setID(const int value);
    void setScrollable(const bool value);

    std::string GetObjectTypeString();

    bool isPressed = false;

    /**
     * update, processinput, draw gibi fonksiyonlar, parent içinde
     * gerceklesmeyecek
     */
    bool independent = false;

    std::vector<UIObject *> childs;

    TextRenderer *rend = nullptr;

   protected:
    Vector2<int> position;
    float scale;
    Vector2<int> size;
    UIObjectType objType;
    UIObject *parent = nullptr;

    int id = 0;

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