#include "Texture.hpp"

Texture2D::Texture2D()
    : Width(0),
      Height(0),
      Internal_Format(GL_RGB),
      Image_Format(GL_RGB),
      Wrap_S(GL_CLAMP_TO_EDGE),
      Wrap_T(GL_CLAMP_TO_EDGE),
      Filter_Min(GL_NEAREST),
      Filter_Max(GL_NEAREST) {
    glGenTextures(1, &this->ID);
}

void Texture2D::Generate(const GLuint width, const GLuint height,
                         unsigned char *data) {
    this->Width = width;
    this->Height = height;

    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0,
                 this->Image_Format, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Generate(GLuint width, GLuint height, GLubyte (*data)[1][4],
                         bool isBlack) {
    if (isBlack) {
        Filter_Min = GL_LINEAR;
        Filter_Max = GL_LINEAR;
    }

    this->Width = width;
    this->Height = height;

    // Create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0,
                 this->Image_Format, GL_UNSIGNED_BYTE, data);
    // Set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Generate(bool isAlpha, const GLuint width, const GLuint height,
                         unsigned char *data) {
    this->Width = width;
    this->Height = height;
    glGenTextures(1, &this->ID);
    glBindTexture(GL_TEXTURE_2D, this->ID);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);  // default

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::Bind() const { glBindTexture(GL_TEXTURE_2D, this->ID); }