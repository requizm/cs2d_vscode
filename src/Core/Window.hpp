#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Manager/InputManager.hpp"


void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action,
                           int mods);
void character_callback(GLFWwindow *window, unsigned int codepoint);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

class Window {
   public:
    Window(std::string windowName, int x, int y);
    void Clear();
    void Update();
    void Destroy();
    GLFWwindow *GetWindow();

   private:
    GLFWwindow *window = nullptr;
};

#endif  // WINDOW_H