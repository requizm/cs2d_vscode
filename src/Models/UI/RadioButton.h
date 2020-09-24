#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "Label.h"
#include <functional>

class RadioButtonElement : public Label
{
public:
    RadioButtonElement();
    RadioButtonElement(const std::string &text, glm::vec2 position, TextRenderer &textRenderer, glm::vec3 buttonColor = glm::vec3(1.0F), glm::vec3 textColor = glm::vec3(0.0F), float scale = 1.0F);
    ~RadioButtonElement();

    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer);
    void Update(const float dt) override;
    void ProcessInput() override;

    glm::vec2 getPosition() override;
    glm::vec2 getLocalPosition() override;
    glm::vec2 getSize() override;

    void setMouseHoverColor(const glm::vec3 color);
    void setButtonColor(const glm::vec3 color);
    void setMouseHoverOutlineColor(const glm::vec3 color);
    void setOutlineColor(const glm::vec3 color);

    void OnEnable() override;
    void OnDisable() override;

    void setPosition(const glm::vec2 position) override;
    void setPosition(const int x, const int y) override;

    bool isMouseHover() override;
    bool isMouseDown() override;
    bool isMouseUp() override;
    bool isMousePress() override;

    bool selected;

    int index;

private:
    glm::vec3 buttonColor; //secili oldugunu belli eden daire'nin rengi
    glm::vec3 mouseHoverColor;
    glm::vec3 outlineColor;
    glm::vec3 mouseHoverOutlineColor;
    glm::vec3 currentColor;
    glm::vec3 currentOutlineColor;

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

    std::vector<std::function<void()>> listeners;

public:
    RadioButton();
    RadioButton(TextRenderer &renderer, glm::vec2 position, int y_sep);
    ~RadioButton();

    void AddListener(std::function<void()> func);

    void Clear();
    void AddElement(const std::string &text, glm::vec3 buttonColor = glm::vec3(1.0F), glm::vec3 textColor = glm::vec3(0.0F), float scale = 1.0F);

    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer);
    void Update(const float dt);
    void ProcessInput();

    void Select(int index);
    RadioButtonElement *GetSelectedElement();

    int selectedIndex = -1;
};

#endif