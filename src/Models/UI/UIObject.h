#ifndef UIOBJECT_H
#define UIOBJECT_H

#include <glm/glm.hpp>
#include "../../Renderers/TextRenderer.h"
#include "../../Renderers/SquareRenderer.h"
#include "../../Renderers/SpriteRenderer.h"
#include "../../Others/Logger.h"
#include <memory>

enum class UIObjectType
{
	UIOBJECT,
	LABEL,
	TEXTBOX,
	BUTTON,
	PANEL,
	RADIOBUTTON
};
//class TextRenderer;

class UIObject
{
public:
	UIObject();
	UIObject(Vector2<float> position, Vector2<float> size, float scale, TextRenderer &renderer);
	UIObject(Vector2<float> position, Vector2<float> size, float scale, TextRenderer &renderer, UIObjectType type);
	UIObject(Vector2<float> position, Vector2<float> size, float scale);
	UIObject(Vector2<float> position, Vector2<float> size, float scale, UIObjectType type);
	UIObject(Vector2<float> position, float scale, TextRenderer &renderer);
	UIObject(Vector2<float> position, float scale, TextRenderer &renderer, UIObjectType type);
	UIObject(Vector2<float> position, float scale, UIObjectType type);
	virtual ~UIObject();

	virtual void Update(const float dt);
	virtual void OnEnable();
	virtual void OnDisable();
	virtual void ProcessInput();
	virtual void Draw();
	virtual void Draw(SpriteRenderer &spriteRenderer, SquareRenderer &squareRenderer);

	virtual Vector2<float> getPosition();
	virtual Vector2<float> getSize();
	virtual Vector2<float> getCenterPosition() const;
	virtual Vector2<float> getLocalPosition();
	UIObject *getParent() const;
	float getScale() const;
	bool isParent() const;
	bool isVisible() const;
	bool isEnable() const;
	bool isMouseEvents() const;
	bool isDependParent() const;
	int getID() const;
	bool isRenderable(); //scroll'dan dolayi
	bool isScrollable() const;

	virtual void setPosition(const Vector2<float> position);
	virtual void setPosition(const int x, const int y);
	virtual void setParentCenterPos();
	virtual void setSize(const Vector2<float> size);
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

	/**
	* update, processinput, draw gibi fonksiyonlar, parent içinde gerceklesmeyecek
	*/
	bool independent = false;

	std::vector<UIObject *> childs;

protected:
	Vector2<float> position;
	float scale;
	Vector2<float> size;
	UIObjectType objType;
	UIObject *parent = nullptr;

	TextRenderer *rend = nullptr;
	int id = 0;

	/**
	* visible, enable ve mouseEvent degiskenleri parent'a bagli olsun
	*/
	bool dependParent;

	bool visible;
	bool enable;
	bool mouseEvents;

	bool scrollable;

	bool isDown = false;
	bool isUp = false;

private:
};

#endif // UIOBJECT_H