#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/glew.h>

#include "../../Core/Math/Vector2.hpp"

class Circle
{
public:
    Circle();
    Circle(bool empty);
    ~Circle();

    void initEmptyCircle();
    void initFilledCircle();

    GLuint VAO;
};

#endif