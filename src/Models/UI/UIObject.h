#ifndef UIOBJECT_H
#define UIOBJECT_H

#include <glm/glm.hpp>
#include "../../Renderers/TextRenderer.h"
#include "../../Others/Logger.h"
#include <memory>

enum class UIObjectType
{
	UIOBJECT,
	LABEL,
	TEXTBOX,
	BUTTON,
	PANEL
};
//class TextRenderer;

class UIObject
{
public:
	UIObject();
	UIObject(glm::vec2 position, glm::vec2 size, float scale, TextRenderer &renderer);
	UIObject(glm::vec2 position, glm::vec2 size, float scale, TextRenderer &renderer, UIObjectType type);
	UIObject(glm::vec2 position, glm::vec2 size, float scale);
	UIObject(glm::vec2 position, glm::vec2 size, float scale, UIObjectType type);
	UIObject(glm::vec2 position, float scale, TextRenderer &renderer);
	UIObject(glm::vec2 position, float scale, TextRenderer &renderer, UIObjectType type);
	virtual ~UIObject();

	virtual void Update(const float dt);
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void ProcessInput();

	virtual glm::vec2 getPosition();
	virtual glm::vec2 getSize();
	virtual glm::vec2 getCenterPosition() const;
	virtual glm::vec2 getLocalPosition();
	UIObject getParent() const;
	float getScale() const;
	bool isParent() const;
	bool isVisible() const;
	bool isEnable() const;
	bool isMouseEvents() const;
	bool isDependParent() const;
	int getID() const;
	bool isRenderable(); //scroll'dan dolayi
	bool isScrollable() const;

	virtual void setPosition(const glm::vec2 position);
	virtual void setPosition(const int x, const int y);
	virtual void setParentCenterPos();
	virtual void setSize(const glm::vec2 size);
	virtual void setSize(const int x, const int y);
	void setScale(const float scale);
	void setParent(UIObject *uiobject, bool dependParent = true);
	void removeParent();
	void setVisible(const bool value);
	void setEnable(const bool value);
	void setMouseEvent(const bool value);
	void setDependParent(const bool value);
	void setID(const int value);
	void setScrollable(const bool value);

	std::string GetObjectTypeString();

	bool isPressed = false;
protected:
	glm::vec2 position;
	float scale;
	glm::vec2 size;
	UIObjectType objType;
	UIObject *parent = nullptr;
	
	TextRenderer *rend = nullptr;
	int id = 0;

	bool dependParent; //visible, enable ve mouseEvent degiskenleri parent'a bagli olsun veya olmasin

	bool visible;
	bool enable;
	bool mouseEvents;

	bool scrollable;

	bool isDown = false;
	bool isUp = false;

private:
	
};

#endif // UIOBJECT_H