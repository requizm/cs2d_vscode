#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

//#include <GL/glew.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

#include "../Models/Shader.hpp"
#include "../Models/Sprite.hpp"

class SpriteRenderer
{
public:
	// Constructor (inits shaders/shapes)
	//SpriteRenderer(Shader shader, Texture2D texture, GLuint x, GLuint y, GLuint width, GLuint height);
	SpriteRenderer(Shader shader);
	SpriteRenderer();
	// Destructor
	~SpriteRenderer();
	// Renders a defined quad textured with given sprite
	//void DrawSprite(Texture2D texture, Vector2<float> position, Vector2<float> size = Vector2<float>(10, 10), GLfloat rotate = 0.0f);

	/**
	 * @brief Draw original sprite color, if you wanna shining object, you should change {isSelect=true} and {time=(system.time)}
	 * 
	 * @param sprite 
	 * @param position 
	 * @param size 
	 * @param rotate 0
	 * @param drawCenter false
	 * @param shineFactor 0.0F 
	 * @param isSelected false
	 * @param time 0.0F
	 */
	void DrawSprite(const Sprite &sprite, Vector2<int> position, Vector2<int> size, int rotate = 0.0F, bool drawCenter = false, GLfloat shineFactor = 0.0F, bool isSelected = false, GLfloat time = 0.0F);

	/**
	 * @brief Draw replaced sprite color, if you wanna shining object, you should change {isSelect=true} and {time=(system.time)}
	 * 
	 * @param sprite 
	 * @param position 
	 * @param size 
	 * @param color 
	 * @param drawCenter false
	 * @param rotate 0
	 * @param shineFactor 0.0F
	 * @param isSelected false
	 * @param time 0.0F
	 */
	void DrawSprite(const Sprite &sprite, Vector2<int> position, Vector2<int> size, Vector3<float> color, bool drawCenter = false, int rotate = 0, GLfloat shineFactor = 0.0F, bool isSelected = false, float time = 0.0F);

	void DrawSprite(const Sprite &sprite, Matrix4<float> model);
	void SetProjection(Matrix4<float> projection);

private:
	Shader shader;
};

#endif
