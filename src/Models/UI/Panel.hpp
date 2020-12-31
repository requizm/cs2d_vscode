#ifndef PANEL_H
#define PANEL_H

#include "UIObject.hpp"
#include "../../Renderers/SquareRenderer.hpp"
#include "../../Renderers/SpriteRenderer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../Managers/InputManager.hpp"
#include "Button.hpp"

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
	Panel(Vector2<int> position, const std::string &title, Vector2<int> size, TextRenderer &renderer, bool isBackGround = false, bool opttitles = true, float scale = 1.0F, const Vector3<float> &color = Vector3<float>(1.0F), float transp = 0.9F);
	Panel();
	~Panel();

	void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer) override;
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
	Button escapeButton;
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
	bool isMouseDownForDrag(const int key);
	bool isMouseUpM(const int key);
	bool isMousePressForDrag(const int key);

	bool isMouseHoverForMouse();
	bool isMouseDownForMouse(const int key);
	bool isMousePressForMouse(const int key);
};

#endif