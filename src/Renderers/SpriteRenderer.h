#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

//#include <GL/glew.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>

#include "../Models/Shader.h"
#include "../Models/Sprite.h"

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
 	* Does stuff
 	* @param {GLfloat} shineFactor : sadece editor'deki tile'larin parlamasi icin
	* @param {bool} isSelected : sadece editor'deki secili tile'larin parlamasi icin
 	*/
	void DrawSprite(const Sprite &sprite, Vector2<float> position, Vector2<float> size, GLfloat rotate = 0.0F, bool drawCenter = false,
	GLfloat shineFactor = 0.0F, bool isSelected = false, GLfloat time = 0.0F);
	
	void DrawSprite(const Sprite &sprite, Vector2<float> position, Vector2<float> size, Vector3<float> color, bool drawCenter = false, 
	GLfloat rotate = 0.0F, GLfloat shineFactor = 0.0F, bool isSelected = false, float time = 0.0F);

	void DrawSprite(const Sprite &sprite, Matrix4<float> model);
	void SetProjection(Matrix4<float> projection);

private:
	// Render state
	Shader shader;
	//GLuint quadVAO;
	//Texture2D quadTexture;

	//void initData(GLuint x = NULL, GLuint y = NULL, GLuint width = NULL, GLuint height = NULL);
};

#endif
