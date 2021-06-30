#include "InputManager.hpp"

Vector2<int> InputManager::mousePos;
Vector2<float> InputManager::scroll;
bool InputManager::scrollYPressed;

wchar_t InputManager::keycode;
int InputManager::m_fps = 0;

KeyEvent InputManager::mouseKeys[3];
KeyEvent InputManager::oldMouseKeys[3];

KeyEvent InputManager::keyboardKeys[52];
KeyEvent InputManager::oldKeyboardKeys[52];

std::map<int, int> InputManager::keys;

std::map<int, std::vector<EventF>> InputManager::m_Callbacks_Down;
std::map<int, std::vector<EventF>> InputManager::m_Callbacks_Up;

InputManager::InputManager() = default;

bool InputManager::isKey(const KeyboardKeys key)
{
    return InputManager::keyboardKeys[(int)key].state == KeyStates::PRESS;
}

bool InputManager::isKeyDown(const KeyboardKeys key)
{
    return InputManager::keyboardKeys[(int)key].state == KeyStates::DOWN;
}

bool InputManager::isKeyUp(const KeyboardKeys key)
{
    return InputManager::keyboardKeys[(int)key].state == KeyStates::RELEASE;
}

bool InputManager::isButton(MouseKeys key)
{
    return InputManager::mouseKeys[(int)key].state == KeyStates::PRESS;
}

bool InputManager::isButtonDown(MouseKeys key)
{
    return InputManager::mouseKeys[(int)key].state == KeyStates::DOWN;
}

bool InputManager::isButtonUp(MouseKeys key)
{
    return InputManager::mouseKeys[(int)key].state == KeyStates::RELEASE;
}

void InputManager::addListenerDown(int key, std::function<void()> callback,
                                   int id)
{
    InputManager::m_Callbacks_Down[key].push_back(EventF(callback, id));
}

void InputManager::addListenerUp(int key, std::function<void()> callback,
                                 int id)
{
    InputManager::m_Callbacks_Up[key].push_back(EventF(callback, id));
}

void InputManager::removeListenerDown(int key, std::function<void()> callback,
                                      int id)
{
    for (auto &pair : InputManager::m_Callbacks_Down)
    {
        if (pair.first == key)
        {
            for (std::vector<int>::size_type i = 0; i < pair.second.size(); i++)
            {
                if (pair.second[i].id == id)
                {
                    pair.second.erase(pair.second.begin() + i);
                    break;
                }
            }
        }
    }
}

void InputManager::removeListenerUp(int key, std::function<void()> callback,
                                    int id)
{
    for (auto &pair : InputManager::m_Callbacks_Up)
    {
        if (pair.first == key)
        {
            for (std::vector<int>::size_type i = 0; i < pair.second.size(); i++)
            {
                if (pair.second[i].id == id)
                {
                    pair.second.erase(pair.second.begin() + i);
                    break;
                }
            }
        }
    }
}

void InputManager::removeAllListeners()
{
    InputManager::m_Callbacks_Down.clear();
    InputManager::m_Callbacks_Up.clear();
}

void InputManager::onMouseDown(int key)
{
    for (auto &callback : m_Callbacks_Down[key])
    {
        callback.event();
    }
}
void InputManager::onMouseUp(int key)
{
    for (auto &callback : m_Callbacks_Up[key])
    {
        callback.event();
    }
}

void InputManager::InitKeyboardKeys()
{
    InputManager::keys[0] = 32;
    InputManager::keys[1] = 39; /* ' */
    InputManager::keys[2] = 44; /* ; */
    InputManager::keys[3] = 45; /* - */
    InputManager::keys[4] = 46; /* . */
    InputManager::keys[5] = 47; /* / */
    InputManager::keys[6] = 48;
    InputManager::keys[7] = 49;
    InputManager::keys[8] = 50;
    InputManager::keys[9] = 51;
    InputManager::keys[10] = 52;
    InputManager::keys[11] = 53;
    InputManager::keys[12] = 54;
    InputManager::keys[13] = 55;
    InputManager::keys[14] = 56;
    InputManager::keys[15] = 57;
    InputManager::keys[16] = 59; /* ; */
    InputManager::keys[17] = 61; /* = */
    InputManager::keys[18] = 65;
    InputManager::keys[19] = 66;
    InputManager::keys[20] = 67;
    InputManager::keys[21] = 68;
    InputManager::keys[22] = 69;
    InputManager::keys[23] = 70;
    InputManager::keys[24] = 71;
    InputManager::keys[25] = 72;
    InputManager::keys[26] = 73;
    InputManager::keys[27] = 74;
    InputManager::keys[28] = 75;
    InputManager::keys[29] = 76;
    InputManager::keys[30] = 77;
    InputManager::keys[31] = 78;
    InputManager::keys[32] = 79;
    InputManager::keys[33] = 80;
    InputManager::keys[34] = 81;
    InputManager::keys[35] = 82;
    InputManager::keys[36] = 83;
    InputManager::keys[37] = 84;
    InputManager::keys[38] = 85;
    InputManager::keys[39] = 86;
    InputManager::keys[40] = 87;
    InputManager::keys[41] = 88;
    InputManager::keys[42] = 89;
    InputManager::keys[43] = 90;
    InputManager::keys[44] = 91;  /* [ */
    InputManager::keys[45] = 92;  /* \ */
    InputManager::keys[46] = 93;  /* ] */
    InputManager::keys[47] = 96;  /* ` */
    InputManager::keys[48] = 161; /* non-US #1 */
    InputManager::keys[49] = 162; /* non-US #2 */

    InputManager::keys[50] = 256; /* ESC */
    InputManager::keys[51] = 259; /* BACKSPACE */
}

void InputManager::UpdateMouse(GLFWwindow *window)
{
    int size = sizeof(InputManager::mouseKeys) / sizeof(KeyEvent);
    for (int i = 0; i < size; i++)
    {
        int newStatus = glfwGetMouseButton(window, i);
        if (InputManager::oldMouseKeys[i].state == GLFW_RELEASE &&
            newStatus == GLFW_PRESS)
        {
            InputManager::mouseKeys[i].state = (int)KeyStates::DOWN;
            InputManager::oldMouseKeys[i].state = GLFW_PRESS;
        }
        else if (InputManager::oldMouseKeys[i].state == GLFW_PRESS &&
                 newStatus == GLFW_PRESS)
        {
            InputManager::mouseKeys[i].state = (int)KeyStates::PRESS;
            InputManager::oldMouseKeys[i].state = GLFW_PRESS;
        }
        else if (InputManager::oldMouseKeys[i].state == GLFW_PRESS &&
                 newStatus == GLFW_RELEASE)
        {
            InputManager::mouseKeys[i].state = (int)KeyStates::RELEASE;
            InputManager::oldMouseKeys[i].state = GLFW_RELEASE;
        }
        else if (InputManager::oldMouseKeys[i].state == GLFW_RELEASE &&
                 newStatus == GLFW_RELEASE)
        {
            InputManager::mouseKeys[i].state = (int)KeyStates::NOTHING;
            InputManager::oldMouseKeys[i].state = GLFW_RELEASE;
        }
    }
}

void InputManager::UpdateKeyboard(GLFWwindow *window)
{
    for (int i = 0; i < InputManager::keys.size(); i++)
    {
        int newStatus = glfwGetKey(window, InputManager::keys[i]);
        if (InputManager::oldKeyboardKeys[i].state == GLFW_RELEASE &&
            newStatus == GLFW_PRESS)
        {
            InputManager::keyboardKeys[i].state = (int)KeyStates::DOWN;
            InputManager::oldKeyboardKeys[i].state = GLFW_PRESS;
        }
        else if (InputManager::oldKeyboardKeys[i].state == GLFW_PRESS &&
                 newStatus == GLFW_PRESS)
        {
            InputManager::keyboardKeys[i].state = (int)KeyStates::PRESS;
            InputManager::oldKeyboardKeys[i].state = GLFW_PRESS;
        }
        else if (InputManager::oldKeyboardKeys[i].state == GLFW_PRESS &&
                 newStatus == GLFW_RELEASE)
        {
            InputManager::keyboardKeys[i].state = (int)KeyStates::RELEASE;
            InputManager::oldKeyboardKeys[i].state = GLFW_RELEASE;
        }
        else if (InputManager::oldKeyboardKeys[i].state == GLFW_RELEASE &&
                 newStatus == GLFW_RELEASE)
        {
            InputManager::keyboardKeys[i].state = (int)KeyStates::NOTHING;
            InputManager::oldKeyboardKeys[i].state = GLFW_RELEASE;
        }
    }
}