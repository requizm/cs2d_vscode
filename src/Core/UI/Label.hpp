#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "../Manager/InputManager.hpp"
#include "../Manager/Logger.hpp"
#include "../Manager/ObjectManager.hpp"
#include "UIObject.hpp"


enum LabelType
{
    CLICKABLE,
    NOT_CLICKABLE
};

class Label : public UIObject
{
   public:
    Label();

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

    Label(const std::string &text, Vector2<int> position,
          TextRenderer &renderer, Object *par, float scale = 1.0F,
          const Vector3<float> &color = Vector3<float>(1.0F),
          UIObjectType type = UIObjectType::LABEL,
          LabelType ltype = LabelType::CLICKABLE);

    /**
     * @brief Construct a new Label for TextBox
     *
     * @param position
     * @param size
     * @param renderer
     * @param scale 1.0F
     * @param color Vector3<float>(1.0F)
     * @param type UIObjectType::LABEL
     */
    Label(Vector2<int> position, const Vector2<int> &size, TextRenderer &renderer, float scale = 1.0F,
          const Vector3<float> &color = Vector3<float>(1.0F),
          UIObjectType type = UIObjectType::LABEL);

    Label(Vector2<int> position, const Vector2<int> &size, TextRenderer &renderer, Object *par, float scale = 1.0F,
          const Vector3<float> &color = Vector3<float>(1.0F),
          UIObjectType type = UIObjectType::LABEL);
    ~Label() override;

    void Draw() override;

    void Update() override;
    void ProcessInput() override;

    virtual bool isMouseHover();

    std::string getText() const;
    virtual void setText(const std::string &text);
    void setTextColor(const Vector3<float> &color);
    void setTextHoverColor(const Vector3<float> &color);
    void setTextClickColor(const Vector3<float> &color);

    void addListenerDown(std::function<void()> func);
    void addListenerUp(std::function<void()> func);

   protected:
    Vector2<int> labelSize = Vector2<int>(1);

    std::string text;
    Vector3<float> textClickColor;
    Vector3<float> textColor;
    Vector3<float> textHoverColor;
    Vector3<float> textCurrentColor;

    void onMouseDown();
    void onMouseUp();


    std::vector<std::function<void()>> listenersDown, listenersUp;

    std::function<void()> mDown;
    std::function<void()> mUp;

   private:
    void SetMouseState(bool &variable, bool value);

    bool isHover = false;

    LabelType labelType;
};

#endif  // LABEL_H