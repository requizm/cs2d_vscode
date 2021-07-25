#ifndef INPUTSTRUCTS_H
#define INPUTSTRUCTS_H


#include <functional>

struct EventF
{
   public:
    std::function<void()> event;
    int id;
    EventF(std::function<void()> func, int id)
    {
        this->id = id;
        event = func;
    }
};

enum KeyboardKeys
{
    KEY_SPACE,
    KEY_APOSTROPHE, /* ' */
    KEY_COMMA,      /* , */
    KEY_MINUS,      /* - */
    KEY_PERIOD,     /* . */
    KEY_SLASH,      /* / */
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_SEMICOLON, /* ; */
    KEY_EQUAL,     /* = */
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_LEFT_BRACKET,  /* [ */
    KEY_BACKSLASH,     /* \ */
    KEY_RIGHT_BRACKET, /* ] */
    KEY_GRAVE_ACCENT,  /* ` */
    KEY_WORLD_1,       /* non-US #1 */
    KEY_WORLD_2,       /* non-US #2 */

    KEY_ESCAPE,
    KEY_BACKSPACE
};

enum MouseKeys
{
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_MIDDLE
};

enum KeyStates
{
    NOTHING,
    DOWN,
    PRESS,
    RELEASE
};

struct KeyEvent
{
   public:
    KeyEvent() = default;
    int state = 0;
};
#endif  // INPUTSTRUCTS_H