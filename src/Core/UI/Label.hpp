#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "UIObject.hpp"
#include "../Manager/Input/InputStructs.hpp"

enum LabelType
{
    CLICKABLE,
    NOT_CLICKABLE
};

class Label : public UIObject
{
   public:
    Label() = default;

    /**
     * @brief Construct a new Label
     *
     * @param text
     * @param position
     * @param renderer
     * @param scale 1.0F
     * @param color Vector3<float>(1.0F)
     * @param type UIObjectType::LABEL
     */
    Label(const std::string &text, Vector2<int> position,
          TextRenderer &renderer, float scale = 1.0F,
          const Vector3<float> &color = Vector3<float>(1.0F),
          UIObjectType type = UIObjectType::LABEL,
          LabelType ltype = LabelType::CLICKABLE);

    /**
     * @brief Construct a new Label for TextBox
     *
     * @param position
     * @param renderer
     * @param scale 1.0F
     * @param color Vector3<float>(1.0F)
     * @param type UIObjectType::LABEL
     */
    Label(Vector2<int> position, TextRenderer &renderer, float scale = 1.0F,
          const Vector3<float> &color = Vector3<float>(1.0F),
          UIObjectType type = UIObjectType::LABEL);

    /**
     * @brief Construct a new Label for TileButton and SpriteButton
     *
     * @param position
     * @param size
     * @param scale 1.0F
     * @param type UIObjectType::LABEL
     */
    Label(Vector2<int> position, Vector2<int> size, float scale = 1.0F,
          UIObjectType type = UIObjectType::LABEL,
          LabelType ltype = LabelType::CLICKABLE);
    virtual ~Label();

    void Draw() override;

    void Update() override;
    void ProcessInput() override;

    virtual bool isMouseHover();
    virtual bool isMouseDown();
    virtual bool isMouseUp();
    virtual bool isMousePress();

    std::string getText() const;
    Vector2<int> getLabelSize() const;
    Vector3<float> getLabelColor() const;
    Vector3<float> getLabelMouseHoverColor() const;
    Vector3<float> getLabelClickColor() const;

    virtual void setText(const std::string &text);
    void setLabelColor(const Vector3<float> &color);
    void setLabelMouseHoverColor(const Vector3<float> &color);
    void setLabelClickColor(const Vector3<float> &color);

   protected:
    Vector2<int> labelSize = Vector2<int>(1);

    std::string text;
    Vector3<float> labelClickColor;
    Vector3<float> labelColor;
    Vector3<float> labelMouseHoverColor;
    Vector3<float> labelCurrentColor;

    void DrawForButton(const bool center);

    Vector2<int> getPositionForButton(const bool center);

    virtual bool isMouseHoverM();
    virtual bool isMouseDownM(MouseKeys key);
    virtual bool isMouseUpM(MouseKeys key);
    virtual bool isMousePressM(MouseKeys key);

    virtual void onMouseDown();
    virtual void onMouseUp();
    void addListenerDown(std::function<void()> func);
    void addListenerUp(std::function<void()> func);

    std::vector<std::function<void()>> listenersDown, listenersUp;

    bool downTrigger = false;
    bool upTrigger = false;

    std::function<void()> mDown;
    std::function<void()> mUp;

   private:
    void SetMouseState(bool &variable, bool value);

    bool isHover = false;

    LabelType labelType;
};

#endif  // LABEL_H