#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <functional>

#include "Label.hpp"

class RadioButtonElement : public Label
{
public:
    RadioButtonElement();

    /**
     * @brief Construct a new Radio Button Element object
     * 
     * @param text 
     * @param position 
     * @param textRenderer 
     * @param index 
     * @param buttonColor Vector3<float>(1.0F)
     * @param textColor Vector3<float>(0.0F)
     * @param scale 1.0F
     */
    RadioButtonElement(const std::string &text, Vector2<int> position, TextRenderer &textRenderer, int index, const Vector3<float> &buttonColor = Vector3<float>(1.0F), const Vector3<float> &textColor = Vector3<float>(0.0F), float scale = 1.0F);
    ~RadioButtonElement();

    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) override;
    void Update() override;
    void ProcessInput() override;

    Vector2<int> getPosition() override;
    Vector2<int> getLocalPosition() override;
    Vector2<int> getSize() override;
    int getIndex();

    void setMouseHoverColor(const Vector3<float> &color);
    void setButtonColor(const Vector3<float> &color);
    void setMouseHoverOutlineColor(const Vector3<float> &color);
    void setOutlineColor(const Vector3<float> &color);

    void OnEnable() override;
    void OnDisable() override;

    void setPosition(const Vector2<int> position) override;
    void setPosition(const int x, const int y) override;

    bool isMouseHover() override;
    bool isMouseDown() override;
    bool isMouseUp() override;
    bool isMousePress() override;

    bool selected;

private:
    Vector3<float> buttonColor; //secili oldugunu belli eden daire'nin rengi
    Vector3<float> mouseHoverColor;
    Vector3<float> outlineColor;
    Vector3<float> mouseHoverOutlineColor;
    Vector3<float> currentColor;
    Vector3<float> currentOutlineColor;
    int index;

    bool isMouseHoverM() override;
    bool isMouseDownM(const int key) override;
    bool isMouseUpM(const int key) override;
    bool isMousePressM(const int key) override;
};

class RadioButton : public UIObject
{
private:
    std::vector<RadioButtonElement *> elements;
    int i = 0;
    int y_sep; //aradaki bosluklar

    std::vector<std::function<void(RadioButtonElement *, RadioButtonElement *)>> listeners;

public:
    RadioButton();
    RadioButton(TextRenderer &renderer, Vector2<int> position, int y_sep);
    ~RadioButton();

    void AddListener(std::function<void(RadioButtonElement *, RadioButtonElement *)> func);

    void Clear();
    void AddElement(const std::string &text, const Vector3<float> &buttonColor = Vector3<float>(1.0F), const Vector3<float> &textColor = Vector3<float>(0.0F), float scale = 1.0F);

    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) override;
    void Update() override;
    void ProcessInput() override;

    void Select(int index);
    RadioButtonElement *GetSelectedElement();

    int selectedIndex = -1;
};

#endif