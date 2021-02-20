#include "Square.hpp"

#define PI 3.14159265

Square::Square() : VAO(0) {}

void Square::init() { initData(); }

Square::~Square() = default;

void Square::initData() {
    // Configure VAO/VBO
    GLuint VBO;
    GLfloat vertices[12];

    vertices[0] = 0.0f;
    vertices[1] = 1.0f;
    vertices[2] = 1.0f;
    vertices[3] = 0.0f;
    vertices[4] = 0.0f;
    vertices[5] = 0.0f;

    vertices[6] = 0.0f;
    vertices[7] = 1.0f;
    vertices[8] = 1.0f;
    vertices[9] = 1.0f;
    vertices[10] = 1.0f;
    vertices[11] = 0.0f;

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
                          (GLvoid *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
