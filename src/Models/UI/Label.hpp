#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "../../Managers/InputManager.hpp"
#include "../../Others/Logger.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "UIObject.hpp"

//class TextRenderer;

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
	Label(const std::string &text, Vector2<int> position, TextRenderer &renderer, float scale = 1.0F, const Vector3<float> &color = Vector3<float>(1.0F), UIObjectType type = UIObjectType::LABEL);

	/**
	 * @brief Construct a new Label for TextBox
	 * 
	 * @param position 
	 * @param renderer 
	 * @param scale 1.0F
	 * @param color Vector3<float>(1.0F)
	 * @param type UIObjectType::LABEL
	 */
	Label(Vector2<int> position, TextRenderer &renderer, float scale = 1.0F, const Vector3<float> &color = Vector3<float>(1.0F), UIObjectType type = UIObjectType::LABEL);

	/**
	 * @brief Construct a new Label for TileButton and SpriteButton
	 * 
	 * @param position 
	 * @param size 
	 * @param scale 1.0F
	 * @param type UIObjectType::LABEL
	 */
	Label(Vector2<int> position, Vector2<int> size, float scale = 1.0F, UIObjectType type = UIObjectType::LABEL);
	~Label();

	virtual void Draw() override;

	virtual void Update() override;
	virtual void ProcessInput() override;

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
	Vector2<int> labelSize;

	std::string text;
	Vector3<float> labelClickColor;
	Vector3<float> labelColor;
	Vector3<float> labelMouseHoverColor;
	Vector3<float> labelCurrentColor;

	void DrawForButton(const bool center);

	Vector2<int> getPositionForButton(const bool center);

	virtual bool isMouseHoverM();
	virtual bool isMouseDownM(const int key);
	virtual bool isMouseUpM(const int key);
	virtual bool isMousePressM(const int key);

	virtual void onMouseDown();
	virtual void onMouseUp();
	void addListenerDown(std::function<void()> func);
	void addListenerUp(std::function<void()> func);

	std::vector<std::function<void()>> listenersDown, listenersUp;

	bool downTrigger = false;
	bool upTrigger = false;

private:
	void SetMouseState(bool &variable, bool value);

	bool isHover = false;

	std::function<void()> mDown;
	std::function<void()> mUp;
};

#endif // LABEL_H