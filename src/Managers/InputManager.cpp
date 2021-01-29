#include "InputManager.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>

Vector2<int> InputManager::mousePos;
Vector2<float> InputManager::scroll;
bool InputManager::scrollYPressed;

/*GLboolean InputManager::Keys[1024];
GLboolean InputManager::KeysProcessed[1024];
GLboolean InputManager::KeysUp[1024];
GLboolean InputManager::downTrigger[1024];
GLboolean InputManager::upTrigger[1024];

GLboolean InputManager::mouseKeys[8];
GLboolean InputManager::mouseKeysProcessed[8];
GLboolean InputManager::mouseKeysUp[8];
GLboolean InputManager::mouseDownTrigger[8];
GLboolean InputManager::mouseUpTrigger[8];*/

GLboolean InputManager::mouseUp[8];
GLboolean InputManager::mouseDown[8];
GLboolean InputManager::mousePress[8];
GLboolean InputManager::oldMouseUp[8];
GLboolean InputManager::oldMouseDown[8];

GLboolean InputManager::keyUp[350];
GLboolean InputManager::keyDown[350];
GLboolean InputManager::keyPress[350];
GLboolean InputManager::oldKeyUp[350];
GLboolean InputManager::oldKeyDown[350];

wchar_t InputManager::keycode;
int InputManager::m_fps = 0;

std::map<int, std::vector<EventF>> InputManager::m_Callbacks_Down;
std::map<int, std::vector<EventF>> InputManager::m_Callbacks_Up;

InputManager::InputManager() = default;

/*void InputManager::processKey(int key)
{
	if (Keys[key] && !KeysProcessed[key])
	{
		KeysProcessed[key] = GL_TRUE;
	}
}*/

bool InputManager::isKey(const int key)
{
	//return Keys[key];
	return InputManager::keyPress[key];
}

bool InputManager::isKeyDown(const int key)
{
	/*InputManager::processKey(key);
	if (downTrigger[key])
	{
		downTrigger[key] = GL_FALSE;
		return Keys[key] && KeysProcessed[key] && !KeysUp[key];
	}

	return false;*/
	return InputManager::keyDown[key];
}

bool InputManager::isKeyUp(const int key)
{
	/*if (upTrigger[key])
	{
		upTrigger[key] = GL_FALSE;
		return !Keys[key] && KeysUp[key] && !KeysProcessed[key];
	}
	return false;*/
	return InputManager::keyUp[key];
}

/*void InputManager::processButton(int key)
{
	if (mouseKeys[key] && !mouseKeysProcessed[key])
	{
		mouseKeysProcessed[key] = GL_TRUE;
	}
}*/

bool InputManager::isButton(int key)
{
	//return mouseKeys[key];
	return InputManager::mousePress[key];
}

bool InputManager::isButtonDown(int key)
{
	//InputManager::processButton(key);
	/*if (mouseDownTrigger[key])
	{
		mouseDownTrigger[key] = GL_FALSE;
		return mouseKeys[key] && !mouseKeysUp[key];
	}
	return false;*/
	return InputManager::mouseDown[key];
}

bool InputManager::isButtonUp(int key)
{
	/*if (mouseUpTrigger[key])
	{
		mouseUpTrigger[key] = GL_FALSE;
		return !mouseKeys[key] && mouseKeysUp[key] && !mouseKeysProcessed[key];
	}
	return false;*/
	return InputManager::mouseUp[key];
}

void InputManager::addListenerDown(int key, std::function<void()> callback, int id)
{
	InputManager::m_Callbacks_Down[key].push_back(EventF(callback, id));
}

void InputManager::addListenerUp(int key, std::function<void()> callback, int id)
{
	InputManager::m_Callbacks_Up[key].push_back(EventF(callback, id));
}

void InputManager::removeListenerDown(int key, std::function<void()> callback, int id)
{
	for (auto &pair : m_Callbacks_Down)
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

void InputManager::removeListenerUp(int key, std::function<void()> callback, int id)
{
	for (auto &pair : m_Callbacks_Up)
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

void InputManager::onMouseDown(int key)
{
	Logger::DebugLog("listener count: " + std::to_string(ObjectManager::listenerObjCount));
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

template <typename T, typename... U>
size_t InputManager::getAddress(std::function<T(U...)> f)
{
	typedef T(fnType)(U...);
	fnType **fnPointer = f.template target<fnType *>();
	return (size_t)*fnPointer;
}