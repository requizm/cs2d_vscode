#ifndef LABEL_H
#define LABEL_H

#include <string>

#include "../../Managers/InputManager.h"
#include "../../Others/Logger.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "UIObject.h"

//class TextRenderer;

class Label : public UIObject
{
public:
	Label();
	Label(const std::string &text, Vector2<float> position, float scale = 1.0F, Vector3<float> color = Vector3<float>(1.0F), UIObjectType type = UIObjectType::LABEL);
	Label(const std::string &text, Vector2<float> position, TextRenderer &renderer, float scale = 1.0F, Vector3<float> color = Vector3<float>(1.0F), UIObjectType type = UIObjectType::LABEL);
	Label(Vector2<float> position, TextRenderer &renderer, float scale = 1.0F, Vector3<float> color = Vector3<float>(1.0F), UIObjectType type = UIObjectType::LABEL);
	Label(Vector2<float> position, Vector2<float> size, float scale = 1.0F, UIObjectType type = UIObjectType::LABEL);
	~Label();

	virtual void Draw();

	virtual void Update();
	virtual void ProcessInput();

	virtual bool isMouseHover();
	virtual bool isMouseDown();
	virtual bool isMouseUp();
	virtual bool isMousePress();

	
	std::string getText() const;
	Vector2<float> getLabelSize() const;
	Vector3<float> getLabelColor() const;
	Vector3<float> getLabelMouseHoverColor() const;
	Vector3<float> getLabelClickColor() const;

	virtual void setText(const std::string &text);
	void setLabelColor(const Vector3<float> color);
	void setLabelMouseHoverColor(const Vector3<float> color);
	void setLabelClickColor(const Vector3<float> color);

	/**
 	* MouseDown() fonksiyonu ile state'i degistirince, maalesef MouseUp() fonksiyonuna giremiyoruz. 
	* Bu sefer de tekrar eski state'e gelince, bir defaya mahsus MouseDown() fonksiyonu calismiyor. 
	* Cunku state ilk degisirken MouseUp() fonksiyonuna giremedigimiz icin durumu resetleyememistik.
	* Bu fonksiyon, state degisikliklerinden sonra kullanilmalidir.  
 	*/
	void SimulateUp();
protected:
	Vector2<float> labelSize;

	std::string text;
	Vector3<float> labelClickColor;
	Vector3<float> labelColor;
	Vector3<float> labelMouseHoverColor;
	Vector3<float> labelCurrentColor;
	
	/**
	*Button icindeki text'i render ederken kullanilacak
	*/
	void DrawForButton(const bool center);

	/**
	*Button icindeki text'in pozisyonunu alirken kullanilacak
	*/
	Vector2<float> getPositionForButton(const bool center);

	virtual bool isMouseHoverM();
	virtual bool isMouseDownM(const int key);
	virtual bool isMouseUpM(const int key);
	virtual bool isMousePressM(const int key);

private:
	void SetMouseState(bool &variable, bool value);
	
	bool isHover = false;
};

#endif // LABEL_H