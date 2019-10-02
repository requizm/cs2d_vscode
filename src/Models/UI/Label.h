#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "../../Managers/InputManager.h"
#include "../../Others/Logger.h"
#include <GLFW/glfw3.h>
#include "UIObject.h"

//class TextRenderer;

class Label : public UIObject
{
public:
	Label();
	Label(const std::string &text, glm::vec2 position, TextRenderer &renderer, float scale = 1.0F, glm::vec3 color = glm::vec3(1.0F), UIObjectType type = UIObjectType::LABEL);
	Label(glm::vec2 position, TextRenderer &renderer, float scale = 1.0F, glm::vec3 color = glm::vec3(1.0F), UIObjectType type = UIObjectType::LABEL);
	Label(glm::vec2 position, glm::vec2 size, float scale = 1.0F, UIObjectType type = UIObjectType::LABEL);
	~Label();

	void Draw();
	void Update(const float dt) override;

	virtual bool isMouseHover();
	virtual bool isMouseDown(int key);
	virtual bool isMouseUp(int key);
	virtual bool isMousePress(int key);

	std::string getText() const;
	glm::vec2 getLabelSize() const;
	glm::vec3 getLabelColor() const;
	glm::vec3 getLabelMouseHoverColor() const;
	glm::vec3 getLabelClickColor() const;

	void setText(const std::string &text);
	void setLabelColor(const glm::vec3 color);
	void setLabelMouseHoverColor(const glm::vec3 color);
	void setLabelClickColor(const glm::vec3 color);

protected:
	glm::vec2 labelSize;

	std::string text;
	glm::vec3 labelClickColor;
	glm::vec3 labelColor;
	glm::vec3 labelMouseHoverColor;
	glm::vec3 labelCurrentColor;

	bool isDown = false;
	bool isUp = false;
	bool isPress = false;
	bool isHover = false;

	virtual bool isMouseHoverM();
	virtual bool isMouseDownM(int key);
	virtual bool isMouseUpM(int key);
	virtual bool isMousePressM(int key);

private:
	void SetMouseState(bool &variable, bool value);
};

#endif // LABEL_H