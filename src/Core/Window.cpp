#include "Window.hpp"
Window::Window(const char *windowName, int x, int y)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(x, y, windowName, nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glGetError(); // Call it once to catch glewInit()

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCharCallback(window, character_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPos(window, x / 2, y / 2);

    // OpenGL configuration
    glViewport(0, 0, x, y);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSwapInterval(1);
}

void Window::Clear()
{
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Update()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::Destroy()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow *Window::GetWindow()
{
    return window;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    InputManager::mousePos = Vector2(static_cast<int>(xpos), static_cast<int>(ypos));
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (action == GLFW_RELEASE)
    {
        InputManager::onMouseUp(button);
    }
    else if (action == GLFW_PRESS)
    {
        InputManager::onMouseDown(button);
    }
}

void character_callback(GLFWwindow *window, unsigned int codepoint)
{
    InputManager::keycode = codepoint;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    InputManager::scroll = Vector2(static_cast<float>(xoffset), static_cast<float>(yoffset));
    InputManager::scrollYPressed = true;
}