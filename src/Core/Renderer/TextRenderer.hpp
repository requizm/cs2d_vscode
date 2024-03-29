#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <GL/glew.h>

#include <map>

#include "Shader.hpp"

/// Holds all state information relevant to a character as loaded using FreeType
struct Character
{
    GLuint TextureID;      // ID handle of the glyph texture
    Vector2<int> Size;     // Size of glyph
    Vector2<int> Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;        // Horizontal offset to advance to next glyph
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
    GLuint VAO = 0;
    GLuint VBO = 0;
    // Constructor
    TextRenderer(GLuint width, GLuint height);
    TextRenderer(GLuint width, GLuint height, const Matrix4<float> &camera);
    TextRenderer() = default;
    // Pre-compiles a list of characters from the given font
    void Load(const std::string &font, GLuint fontSize);
    // Renders a string of text using the precompiled list of characters
    void RenderText(const std::string &text, int x, int y, GLfloat scale,
                    const Vector3<float> &color = Vector3<float>(1.0f));
    void RenderText(const std::string &text, const Vector2<int> &position, GLfloat scale,
                    const Vector3<float> &color = Vector3<float>(1.0f));
    // void RenderLabel(Label *label);
    Vector2<int> CalculateSize(const std::string &text, GLfloat scale);
    // void RenderButton(Button *button);
   private:
    // Render state
};

#endif  // TEXT_RENDERER_H
