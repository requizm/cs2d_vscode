#ifndef PANEL_H
#define PANEL_H

#include "UIObject.h"
#include "../../Renderers/SquareRenderer.h"
#include "../../Renderers/SpriteRenderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../Managers/InputManager.h"
#include "Button.h"

class Panel : public UIObject
{
public:
	Panel(glm::vec2 position, const std::string &title, glm::vec2 size, TextRenderer &renderer, bool isBackGround = false, bool opttitles = true, float scale = 1.0F, glm::vec3 color = glm::vec3(1.0F), float transp = 0.9F);
	Panel();
	~Panel();

	void Draw(SquareRenderer &squareRenderer, SpriteRenderer &spriteRenderer);
	void Update(const float dt) override;
	void OnEnable() override;
	void OnDisable() override;
	void ProcessInput() override;
	
	bool isMouseHover(bool drag);
	bool isMouseDown(bool drag);
	bool isMouseUp();
	bool isMousePress(bool drag);

	glm::vec3 getPanelColor() const;
	glm::vec3 getOutlineColor() const;
	bool isBackGround() const;
	bool isMovable() const;
	std::string getTitle() const;
	bool isOutline() const;

	void setPanelColor(const glm::vec3 color);
	void setBackGround(const bool value);
	void setMovable(const bool value);
	void setTitle(const std::string &text);
	void setOutlineColor(const glm::vec3 color);
	void setOutline(const bool value);

protected:
	glm::vec3 panelColor;
	glm::vec2 dragSize;
	glm::vec2 dragPos;
	Square square = Square(true);
	Button escapeButton;
	Label title;
	bool opttitles;
	bool backGround;
	bool movable;

private:
	bool isDownForDrag = false;

	float lineOffset = 20.0F;

	bool outline;
	glm::vec3 outlineColor;
	float trans;

	bool isMouseHoverForDrag();
	bool isMouseDownForDrag(const int key);
	bool isMouseUpM(const int key);
	bool isMousePressForDrag(const int key);

	bool isMouseHoverForMouse();
	bool isMouseDownForMouse(const int key);
	bool isMousePressForMouse(const int key);
};

#endif