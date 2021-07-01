#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>

class Square
{
   public:
    Square() = default;
    ~Square() = default;

    void init();

    GLuint VAO = 0;

   private:
    void initData();
};

#endif  // SQUARE_H