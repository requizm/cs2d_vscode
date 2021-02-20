#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>

#include "../Manager/Logger.hpp"
#include "../Math/Projection.hpp"
#include "../Math/Vector2.hpp"


// General purpsoe shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility
// functions for easy management.
class Shader {
   public:
    // State
    GLuint ID;
    // Constructor
    Shader();
    // Sets the current shader as active
    Shader& Use();
    // Compiles the shader from given source code
    void Compile(const GLchar* vertexSource, const GLchar* fragmentSource,
                 const GLchar* geometrySource =
                     nullptr);  // Note: geometry source code is optional
    // Utility functions
    void SetFloat(const GLchar* name, GLfloat value,
                  GLboolean useShader = false) const;
    void SetInteger(const GLchar* name, GLint value,
                    GLboolean useShader = false) const;
    void SetVector2f(const GLchar* name, GLfloat x, GLfloat y,
                     GLboolean useShader = false) const;
    void SetVector2f(const GLchar* name, const Vector2<float>& value,
                     GLboolean useShader = false) const;
    void SetVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z,
                     GLboolean useShader = false) const;
    void SetVector3f(const GLchar* name, const Vector3<float>& value,
                     GLboolean useShader = false) const;
    void SetVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z,
                     GLfloat w, GLboolean useShader = false) const;
    // void    SetVector4f(const GLchar* name, const glm::vec4& value, GLboolean
    // useShader = false) const;
    void SetMatrix4(const GLchar* name, Matrix4<float> matrix,
                    GLboolean useShader = false) const;

    void UnUse() const;

   private:
    // Checks if compilation or linking failed and if so, print the error logs
    void checkCompileErrors(GLuint object, const std::string& type) const;
};

#endif