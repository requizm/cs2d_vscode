#include "OutlineTest.hpp"

OutlineTest::~OutlineTest()
{
    glBindVertexArray(VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void OutlineTest::initData()
{
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(VertexOne), nullptr, GL_DYNAMIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);
    glEnableVertexAttribArray(6);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexOne), (GLvoid*)offsetof(VertexOne, vertex));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexOne), (GLvoid*)offsetof(VertexOne, model_1));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexOne), (GLvoid*)offsetof(VertexOne, model_2));
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(VertexOne), (GLvoid*)offsetof(VertexOne, model_3));
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(VertexOne), (GLvoid*)offsetof(VertexOne, model_4));
    glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(VertexOne), (GLvoid*)offsetof(VertexOne, color));
    glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(VertexOne), (GLvoid*)offsetof(VertexOne, trans));


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}