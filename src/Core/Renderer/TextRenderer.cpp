#include "TextRenderer.hpp"

#include <ft2build.h>
#include <iostream>

#include "../../CS2D/Other/GameParameters.hpp"
#include "../Manager/Logger.hpp"
#include "../Manager/ResourceManager.hpp"
#include "../Math/Projection.hpp"

#include FT_FREETYPE_H

TextRenderer::TextRenderer(GLuint width, GLuint height)
{
    // Load and configure shader
    this->TextShader = ResourceManager::GetShader("text");
    this->TextShader.Use();
    Matrix4<float> proj = Projection::ortho(0.0f, static_cast<float>(width),
                                            static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    this->TextShader.SetMatrix4("projection", proj);
    this->TextShader.SetInteger("text", 0);
    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL,
                 GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    this->TextShader.UnUse();
}

TextRenderer::TextRenderer(GLuint width, GLuint height, const Matrix4<float> &camera)
{
    // Load and configure shader
    this->TextShader = ResourceManager::LoadShader(
        GameParameters::resDirectory + "shaders/textVertex.txt",
        GameParameters::resDirectory + "shaders/textFragment.txt", "", "text");
    this->TextShader.Use();
    this->TextShader.SetMatrix4("projection", camera, GL_TRUE);
    this->TextShader.SetInteger("text", 0);
    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL,
                 GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    this->TextShader.UnUse();
}

void TextRenderer::Load(const std::string &font, GLuint fontSize)
{
    // First clear the previously loaded Characters
    this->Characters.clear();
    // Then initialize and load the FreeType library
    FT_Library ft;
    ASSERTM_ERROR(FT_Init_FreeType(&ft) == 0, "FREETYPE: Could not init FreeType Library");

    // Load font as face
    FT_Face face;
    ASSERTM_ERROR(FT_New_Face(ft, font.c_str(), 0, &face) == 0, "FREETYPE: Failed to load font");

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // Then for the first 128 ASCII characters, pre-load/compile their
    // characters and store them
    for (GLubyte c = 0; c < 254; c++)  // lol see what I did there
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            WRITE_ERROR("ERROR::FREETYTPE: Failed to load Glyph");
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                     face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer);
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Now store character for later use
        Character character = {
            texture,
            Vector2<int>(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            Vector2<int>(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<GLuint>(face->glyph->advance.x)};
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::RenderText(const std::string &text, int x, int y, GLfloat scale,
                              const Vector3<float> &color)
{
    // Activate corresponding render state
    this->TextShader.Use();
    this->TextShader.SetVector3f("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos =
            y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] =
            {{xpos, ypos + h, 0.0, 1.0},
             {xpos + w, ypos, 1.0, 0.0},
             {xpos, ypos, 0.0, 0.0},
             {xpos, ypos + h, 0.0, 1.0},
             {xpos + w, ypos + h, 1.0, 1.0},
             {xpos + w, ypos, 1.0, 0.0}};
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferSubData(
            GL_ARRAY_BUFFER, 0, sizeof(vertices),
            vertices);  // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph
        x += (ch.Advance >> 6) * scale;  // Bitshift by 6 to get value in pixels
                                         // (1/64th times 2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    this->TextShader.UnUse();
}

void TextRenderer::RenderText(const std::string &text, const Vector2<int> &position,
                              GLfloat scale, const Vector3<float> &color)
{
    Vector2<int> positionN = position;
    // Activate corresponding render state
    this->TextShader.Use();
    this->TextShader.SetVector3f("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        GLfloat xpos = positionN.x + ch.Bearing.x * scale;
        GLfloat ypos = positionN.y +
                       (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
            {xpos, ypos + h, 0.0, 1.0}, {xpos + w, ypos, 1.0, 0.0}, {xpos, ypos, 0.0, 0.0},

            {xpos, ypos + h, 0.0, 1.0},
            {xpos + w, ypos + h, 1.0, 1.0},
            {xpos + w, ypos, 1.0, 0.0}};
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferSubData(
            GL_ARRAY_BUFFER, 0, sizeof(vertices),
            vertices);  // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph
        positionN.x +=
            (ch.Advance >> 6) * scale;  // Bitshift by 6 to get value in pixels
                                        // (1/64th times 2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    this->TextShader.UnUse();
}

Vector2<int> TextRenderer::CalculateSize(const std::string &text, GLfloat scale)
{
    // GLfloat startX = 0;
    float xPo = 0;
    // Activate corresponding render state
    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = this->Characters[*c];

        // Now advance cursors for next glyph
        xPo += (ch.Advance >> 6) * scale;  // Bitshift by 6 to get value in
                                           // pixels (1/64th times 2^6 = 64)
    }
    return Vector2<int>(static_cast<int>(xPo), 12);
}