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
	Label(const std::string &text, glm::vec2 position, TextRenderer &renderer, float scale = 1.0F, glm::vec3 color = glm::vec3(1.0F), UIObjectType type = UIObjectType::LABEL);
	Label(glm::vec2 position, TextRenderer &renderer, float scale = 1.0F, glm::vec3 color = glm::vec3(1.0F), UIObjectType type = UIObjectType::LABEL);
	Label(glm::vec2 position, glm::vec2 size, float scale = 1.0F, UIObjectType type = UIObjectType::LABEL);
	~Label();

	void Draw();

	
	

	void Update(const float dt) override;
	void ProcessInput() override;

	virtual bool isMouseHover();
	virtual bool isMouseDown();
	virtual bool isMouseUp();
	virtual bool isMousePress();

	
	std::string getText() const;
	glm::vec2 getLabelSize() const;
	glm::vec3 getLabelColor() const;
	glm::vec3 getLabelMouseHoverColor() const;
	glm::vec3 getLabelClickColor() const;

	virtual void setText(const std::string &text);
	void setLabelColor(const glm::vec3 color);
	void setLabelMouseHoverColor(const glm::vec3 color);
	void setLabelClickColor(const glm::vec3 color);

	/**
 	* MouseDown() fonksiyonu ile state'i degistirince, maalesef MouseUp() fonksiyonuna giremiyoruz. 
	* Bu sefer de tekrar eski state'e gelince, bir defaya mahsus MouseDown() fonksiyonu calismiyor. 
	* Cunku state ilk degisirken MouseUp() fonksiyonuna giremedigimiz icin durumu resetleyememistik.
	* Bu fonksiyon, state degisikliklerinden sonra kullanilmalidir.  
 	*/
	void SimulateUp();
protected:
	glm::vec2 labelSize;

	std::string text;
	glm::vec3 labelClickColor;
	glm::vec3 labelColor;
	glm::vec3 labelMouseHoverColor;
	glm::vec3 labelCurrentColor;
	
	/**
	*Button icindeki text'i render ederken kullanilacak
	*/
	void DrawForButton(const bool center);

	/**
	*Button icindeki text'in pozisyonunu alirken kullanilacak
	*/
	glm::vec2 getPositionForButton(const bool center);

	virtual bool isMouseHoverM();
	virtual bool isMouseDownM(const int key);
	virtual bool isMouseUpM(const int key);
	virtual bool isMousePressM(const int key);

private:
	void SetMouseState(bool &variable, bool value);
	
	bool isHover = false;
};

#endif // LABEL_H