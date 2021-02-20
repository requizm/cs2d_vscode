#ifndef SQUARE_H
#define SQUARE_H

#include <GL/glew.h>

class Square
{
   public:
    Square();
    void init();
    ~Square();

    GLuint VAO;

   private:
    void initData();
};

#endif  // SQUARE_H