#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/glew.h>

#include "../Math/Vector2.hpp"

class Circle
{
   public:
    Circle() = default;
    explicit Circle(bool empty);
    ~Circle() = default;

    void initEmptyCircle();
    void initFilledCircle();

    GLuint VAO;
};

#endif