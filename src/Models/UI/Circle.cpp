#include "Circle.h"
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>

Circle::Circle()
{
}

Circle::Circle(bool empty)
{
    if (empty)
    {
        initEmptyCircle();
    }
    else
    {
        initFilledCircle();
    }
}

Circle::~Circle() = default;

void Circle::initEmptyCircle()
{
    GLuint VBO;
    glm::vec2 vertices[31];
    int i;
    int triangleAmount = 30; //# of triangles used to draw circle
    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;
    
    for (i = 0; i <= triangleAmount; i++)
    {
        vertices[i] = glm::vec2(
            (cos(i * twicePi / triangleAmount)),
            (sin(i * twicePi / triangleAmount)));
    }

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Circle::initFilledCircle()
{
    GLuint VBO;
    glm::vec2 vertices[32];
    int i;
    int triangleAmount = 30; //# of triangles used to draw circle
    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;
    vertices[0] = glm::vec2(0, 0);
    for (i = 1; i <= triangleAmount + 1; i++)
    {
        vertices[i] = glm::vec2(
            (cos(i * twicePi / triangleAmount)),
            (sin(i * twicePi / triangleAmount)));
    }

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}