#ifndef OUTLINE_H
#define OUTLINE_H

#include <GL/glew.h>

class Outline
{
   public:
    Outline() = default;
    ~Outline() = default;
    GLuint VAO = 0;
    void initData();
};
#endif  // OUTLINE_H
