#include "InputManager.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Vector2<float> InputManager::mousePos;
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