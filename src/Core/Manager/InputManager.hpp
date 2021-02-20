#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <algorithm>
#include <functional>
#include <map>

#include "../Math/Vector2.hpp"
#include "Input/InputStructs.hpp"


class InputManager {
   public:
    static Vector2<int> mousePos;
    static Vector2<float> scroll;
    static bool scrollYPressed;

    static wchar_t keycode;

    static int m_fps;
    InputManager();

    static KeyEvent mouseKeys[8];
    static KeyEvent oldMouseKeys[8];

    static KeyEvent keyboardKeys[52];
    static KeyEvent oldKeyboardKeys[52];

    static std::map<int, int>
        keys; /* keyboard keyleri 0, 1, 2 gibi siralamak icin */

    static bool isKey(const KeyboardKeys key);
    static bool isKeyDown(const KeyboardKeys key);
    static bool isKeyUp(const KeyboardKeys key);

    static bool isButton(int key);
    static bool isButtonDown(int key);
    static bool isButtonUp(int key);

    static void addListenerDown(int key, std::function<void()> callback,
                                int id);
    static void addListenerUp(int key, std::function<void()> callback, int id);

    static void removeListenerDown(int key, std::function<void()> callback,
                                   int id);
    static void removeListenerUp(int key, std::function<void()> callback,
                                 int id);

    static void onMouseDown(int key);
    static void onMouseUp(int key);

    static std::map<int, std::vector<EventF>> m_Callbacks_Down;
    static std::map<int, std::vector<EventF>> m_Callbacks_Up;

    static void InitKeyboardKeys();

    static void UpdateMouse(GLFWwindow *window);
    static void UpdateKeyboard(GLFWwindow *window);
};

#endif