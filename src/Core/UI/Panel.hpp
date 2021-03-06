#ifndef PANEL_H
#define PANEL_H

#include "../Manager/InputManager.hpp"
#include "../Manager/MemoryOverride/MemoryOverride.hpp"
#include "../Renderer/SpriteRenderer.hpp"
#include "../Renderer/SquareRenderer.hpp"
#include "Label.hpp"
#include "SpriteButton.hpp"



class Panel : public UIObject
{
   public:
    /**
     * @brief Construct a new Panel
     *
     * @param position
     * @param title
     * @param size
     * @param renderer
     * @param isBackGround false
     * @param opttitles true
     * @param scale 1.0F
     * @param color Vector3<int>(1)
     * @param transp 0.9F
     */
    Panel(Vector2<int> position, const std::string &title, Vector2<int> size,
          TextRenderer &renderer, bool isBackGround = false,
          bool opttitles = true, float scale = 1.0F,
          const Vector3<float> &color = Vector3<float>(1.0F),
          float transp = 0.9F);
    Panel();
    virtual ~Panel();

    void Draw(SpriteRenderer &spriteRenderer,
              SquareRenderer &squareRenderer) override;
    void Update() override;
    void OnEnable() override;
    void OnDisable() override;
    void ProcessInput() override;

    bool isMouseHover(bool drag);
    bool isMouseDown(bool drag);
    bool isMouseUp();
    bool isMousePress(bool drag);

    Vector3<float> getPanelColor() const;
    Vector3<float> getOutlineColor() const;
    bool isBackGround() const;
    bool isMovable() const;
    std::string getTitle() const;
    bool isOutline() const;

    void setPanelColor(const Vector3<float> &color);
    void setBackGround(const bool value);
    void setMovable(const bool value);
    void setTitle(const std::string &text);
    void setOutlineColor(const Vector3<float> &color);
    void setOutline(const bool value);

   protected:
    Vector3<float> panelColor;
    Vector2<int> dragSize;
    Vector2<int> dragPos;
    SpriteButton *escapeButton;
    Label title;
    bool opttitles;
    bool backGround;
    bool movable;

   private:
    bool isDownForDrag = false;

    int lineOffset = 20;

    bool outline;
    Vector3<float> outlineColor;
    float trans;

    bool isMouseHoverForDrag();
    bool isMouseDownForDrag(MouseKeys key);
    bool isMouseUpM(MouseKeys key);
    bool isMousePressForDrag(MouseKeys key);

    bool isMouseHoverForMouse();
    bool isMouseDownForMouse(MouseKeys key);
    bool isMousePressForMouse(MouseKeys key);

    std::function<void()> escapeDown;
    void escapeButtonClicked();
};

#endif