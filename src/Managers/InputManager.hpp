#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <map>
#include "../Core/Math/Vector2.hpp"
#include "../Others/Utils.hpp"
#include "ResourceManager.hpp"
#include "ObjectManager.hpp"
#include "../Others/Logger.hpp"

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

class InputManager
{
public:
	static Vector2<int> mousePos;
	static Vector2<float> scroll;
	static bool scrollYPressed;

	/*static GLboolean Keys[1024];
	static GLboolean KeysProcessed[1024];
	static GLboolean KeysUp[1024];
	static GLboolean downTrigger[1024];
	static GLboolean upTrigger[1024];

	static GLboolean mouseKeys[8];
	static GLboolean mouseKeysProcessed[8];
	static GLboolean mouseKeysUp[8];
	static GLboolean mouseDownTrigger[8];
	static GLboolean mouseUpTrigger[8];*/

	static GLboolean mouseUp[8];
	static GLboolean mouseDown[8];
	static GLboolean mousePress[8];
	static GLboolean oldMouseUp[8];
	static GLboolean oldMouseDown[8];

	static GLboolean keyUp[350];
	static GLboolean keyDown[350];
	static GLboolean keyPress[350];
	static GLboolean oldKeyUp[350];
	static GLboolean oldKeyDown[350];

	static wchar_t keycode;

	static int m_fps;
	InputManager();

	//static void processKey(int key);
	static bool isKey(int key);
	static bool isKeyDown(int key);
	static bool isKeyUp(int key);

	//static void processButton(int key);
	static bool isButton(int key);
	static bool isButtonDown(int key);
	static bool isButtonUp(int key);

	static void addListenerDown(int key, std::function<void()> callback, int id);
	static void addListenerUp(int key, std::function<void()> callback, int id);

	static void removeListenerDown(int key, std::function<void()> callback, int id);
	static void removeListenerUp(int key, std::function<void()> callback, int id);

	static void onMouseDown(int key);
	static void onMouseUp(int key);

	static std::map<int, std::vector<EventF>> m_Callbacks_Down;
	static std::map<int, std::vector<EventF>> m_Callbacks_Up;

	template <typename T, typename... U>
	static size_t getAddress(std::function<T(U...)> f);
};

#endif