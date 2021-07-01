#include "TextRenderer.hpp"

#include <ft2build.h>

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
    this->TextShader.SetMatrix4(
        "projection",
        Projection::ortho(0.0f, static_cast<float>(width),
                          static_cast<float>(height), 0.0f, -1.0f, 1.0f));
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

TextRenderer::TextRenderer(GLuint width, GLuint height, Matrix4<float> camera)
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

void TextRenderer::Load(std::string font, GLuint fontSize)
{
    // First clear the previously loaded Characters
    this->Characters.clear();
    // Then initialize and load the FreeType library
    FT_Library ft;
    if (FT_Init_FreeType(&ft))  // All functions return a value different than 0
                                // whenever an error occurred
    {
        WRITE_ERROR("ERROR::FREETYPE: Could not init FreeType Library");
        exit(EXIT_FAILURE);
    }

    // Load font as face
    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
    {
        WRITE_ERROR("ERROR::FREETYPE: Failed to load font");
        exit(EXIT_FAILURE);
    }
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

void TextRenderer::RenderText(std::string text, int x, int y, GLfloat scale,
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
        x += (ch.Advance >> 6) * scale;  // Bitshift by 6 to get value in pixels
                                         // (1/64th times 2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    this->TextShader.UnUse();
}

void TextRenderer::RenderText(std::string text, Vector2<int> position,
                              GLfloat scale, const Vector3<float> &color)
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

        GLfloat xpos = position.x + ch.Bearing.x * scale;
        GLfloat ypos = position.y +
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
        position.x +=
            (ch.Advance >> 6) * scale;  // Bitshift by 6 to get value in pixels
                                        // (1/64th times 2^6 = 64)
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    this->TextShader.UnUse();
}

/*
void TextRenderer::RenderLabel(Label *label)
{
        GLfloat startX = label->position.x;
        GLfloat startY = label->position.y;
        float x = label->position.x;
        // Activate corresponding render state
        this->TextShader.Use();
        this->TextShader.SetVector3f("textColor", label->labelCurrentColor);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(this->VAO);
        GLfloat ypos;
        // Iterate through all characters
        std::string::const_iterator c;
        for (c = label->text.begin(); c != label->text.end(); c++)
        {
                Character ch = Characters[*c];

                GLfloat xpos = x + ch.Bearing.x * label->scale;
                ypos = label->position.y + (this->Characters['H'].Bearing.y -
ch.Bearing.y) * label->scale;

                GLfloat w = ch.Size.x * label->scale;
                GLfloat h = ch.Size.y * label->scale;
                // Update VBO for each character
                GLfloat vertices[6][4] = {
                        { xpos,     ypos + h,   0.0, 1.0 },
                        { xpos + w, ypos,       1.0, 0.0 },
                        { xpos,     ypos,       0.0, 0.0 },

                        { xpos,     ypos + h,   0.0, 1.0 },
                        { xpos + w, ypos + h,   1.0, 1.0 },
                        { xpos + w, ypos,       1.0, 0.0 }
                };
                // Render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                // Update content of VBO memory
                glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
// Be sure to use glBufferSubData and not glBufferData

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                // Render quad
                glDrawArrays(GL_TRIANGLES, 0, 6);
                // Now advance cursors for next glyph
                x += (ch.Advance >> 6) * label->scale; // Bitshift by 6 to get
value in pixels (1/64th times 2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        this->TextShader.UnUse();
        //label->size.x = x - startX;
        //label->size.y = 12;
}*/

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

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Now advance cursors for next glyph
        xPo += (ch.Advance >> 6) * scale;  // Bitshift by 6 to get value in
                                           // pixels (1/64th times 2^6 = 64)
    }
    return Vector2<int>(static_cast<int>(xPo), 12);
}
/*
void TextRenderer::RenderButton(Button *button)
{
        GLfloat startX = button->position.x;
        GLfloat startY = button->position.y;
        float x = button->position.x;
        // Activate corresponding render state
        this->TextShader.Use();
        this->TextShader.SetVector3f("textColor", button->labelColor);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(this->VAO);
        GLfloat ypos;
        // Iterate through all characters
        std::string::const_iterator c;
        for (c = button->text.begin(); c != button->text.end(); c++)
        {
                Character ch = Characters[*c];

                GLfloat xpos = x + ch.Bearing.x * button->scale;
                ypos = button->position.y + (this->Characters['H'].Bearing.y -
ch.Bearing.y) * button->scale;

                GLfloat w = ch.Size.x * button->scale;
                GLfloat h = ch.Size.y * button->scale;
                // Update VBO for each character
                GLfloat vertices[6][4] = {
                        { xpos,     ypos + h,   0.0, 1.0 },
                        { xpos + w, ypos,       1.0, 0.0 },
                        { xpos,     ypos,       0.0, 0.0 },

                        { xpos,     ypos + h,   0.0, 1.0 },
                        { xpos + w, ypos + h,   1.0, 1.0 },
                        { xpos + w, ypos,       1.0, 0.0 }
                };
                // Render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                // Update content of VBO memory
                glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
// Be sure to use glBufferSubData and not glBufferData

                glBindBuffer(GL_ARRAY_BUFFER, 0);
                // Render quad
                glDrawArrays(GL_TRIANGLES, 0, 6);
                // Now advance cursors for next glyph
                x += (ch.Advance >> 6) * button->scale; // Bitshift by 6 to get
value in pixels (1/64th times 2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        this->TextShader.UnUse();
        button->size.x = x - startX;
        button->size.y = ypos - startY;
}
*/