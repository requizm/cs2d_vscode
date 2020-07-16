#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "Label.h"

class RadioButton : public Label
{
public:
    RadioButton();
    RadioButton(const std::string &text, glm::vec2 position, TextRenderer &renderer, glm::vec3 buttonColor = glm::vec3(1.0F), glm::vec3 textColor = glm::vec3(0.0F), float scale = 1.0F);
    ~RadioButton();

    void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) override;
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
    
private:
    bool selected;

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


#endif