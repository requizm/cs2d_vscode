#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/glew.h>

#include "../Math/Vector2.hpp"

class Circle
{
   public:
    Circle();
    explicit Circle(bool empty);
    ~Circle();

    void initEmptyCircle();
    void initFilledCircle();

    GLuint VAO;
};

#endif