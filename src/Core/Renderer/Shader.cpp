#include "Shader.hpp"

#include <iostream>

#include "../Manager/Logger.hpp"
#include "../Math/Projection.hpp"

Shader &Shader::Use()
{
    glUseProgram(this->ID);
    return *this;
}

void Shader::Compile(const GLchar *vertexSource, const GLchar *fragmentSource,
                     const GLchar *geometrySource)
{
    GLuint sVertex, sFragment, gShader;
    // Vertex Shader
    sVertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(sVertex, 1, &vertexSource, NULL);
    glCompileShader(sVertex);
    checkCompileErrors(sVertex, "VERTEX");
    // Fragment Shader
    sFragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(sFragment, 1, &fragmentSource, NULL);
    glCompileShader(sFragment);
    checkCompileErrors(sFragment, "FRAGMENT");
    // If geometry shader source code is given, also compile geometry shader
    if (geometrySource != nullptr)
    {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    // Shader Program
    this->ID = glCreateProgram();
    glAttachShader(this->ID, sVertex);
    glAttachShader(this->ID, sFragment);
    if (geometrySource != nullptr) glAttachShader(this->ID, gShader);
    glLinkProgram(this->ID);
    checkCompileErrors(this->ID, "PROGRAM");
    // Delete the shaders as they're linked into our program now and no longer
    // necessery
    glDeleteShader(sVertex);
    glDeleteShader(sFragment);
    if (geometrySource != nullptr) glDeleteShader(gShader);
}

void Shader::SetFloat(const GLchar *name, GLfloat value,
                      GLboolean useShader) const
{
    glUniform1f(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetInteger(const GLchar *name, GLint value,
                        GLboolean useShader) const
{
    glUniform1i(glGetUniformLocation(this->ID, name), value);
}
void Shader::SetVector2f(const GLchar *name, GLfloat x, GLfloat y,
                         GLboolean useShader) const
{
    glUniform2f(glGetUniformLocation(this->ID, name), x, y);
}
void Shader::SetVector2f(const GLchar *name, const Vector2<float> &value,
                         GLboolean useShader) const
{
    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}
void Shader::SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z,
                         GLboolean useShader) const
{
    glUniform3f(glGetUniformLocation(this->ID, name), x, y, z);
}
void Shader::SetVector3f(const GLchar *name, const Vector3<float> &value,
                         GLboolean useShader) const
{
    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y,
                value.z);
}
void Shader::SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z,
                         GLfloat w, GLboolean useShader) const
{
    glUniform4f(glGetUniformLocation(this->ID, name), x, y, z, w);
}
/*void Shader::SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean
useShader) const
{
        glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y,
value.z, value.w);
}*/
void Shader::SetMatrix4(const GLchar *name, const Matrix4<float> &matrix,
                        GLboolean useShader) const
{
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE,
                       Projection::value_ptr(matrix));
}

void Shader::UnUse() const { glUseProgram(0); }

void Shader::checkCompileErrors(GLuint object, const std::string &type) const
{
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        ASSERTM_ERROR(success != 0, "SHADER: Compile-time error: Type: " + type +
                                        "\n" + infoLog);
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        ASSERTM_ERROR(success != 0, "SHADER: Link-time error: Type: " + type +
                                        "\n" + infoLog);
    }
}