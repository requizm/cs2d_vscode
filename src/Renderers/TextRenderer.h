#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
//#include "Label.h"
#include "../Managers/ResourceManager.h"

//class Label;

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance;     // Horizontal offset to advance to next glyph
};

// A renderer class for rendering text displayed by a font loaded using the
// FreeType library. A single font is loaded, processed into a list of Character
// items for later rendering.
class TextRenderer
{
public:
	// Holds a list of pre-compiled Characters
	std::map<GLchar, Character> Characters;
	// Shader used for text rendering
	Shader TextShader;
	GLuint VAO, VBO;
	// Constructor
	TextRenderer(GLuint width, GLuint height);
	TextRenderer(GLuint width, GLuint height, glm::mat4 camera);
	TextRenderer();
	// Pre-compiles a list of characters from the given font
	void Load(std::string font, GLuint fontSize);
	// Renders a string of text using the precompiled list of characters
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));
	void RenderText(std::string text, glm::vec2 position, GLfloat scale, glm::vec3 color = glm::vec3(1.0f));
	//void RenderLabel(Label *label);
	glm::vec2 CalculateSize(const std::string &text, GLfloat scale);
	//void RenderButton(Button *button);
private:
	// Render state
};

#endif //TEXT_RENDERER_H
