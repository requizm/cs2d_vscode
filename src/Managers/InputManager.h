#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class InputManager
{
public:
	
	static int mouseX, mouseY;
	static int scrollX, scrollY;

	static GLboolean Keys[1024];
	static GLboolean KeysProcessed[1024];
	static GLboolean KeysUp[1024];
	static GLboolean downTrigger[1024];
	static GLboolean upTrigger[1024];

	static GLboolean mouseKeys[8];
	static GLboolean mouseKeysProcessed[8];
	static GLboolean mouseKeysUp[8];
	static GLboolean mouseDownTrigger[8];
	static GLboolean mouseUpTrigger[8];
	//static int mouseOldKeys[8];
	//static int mouseNewKeys[8];

	static wchar_t keycode;
	InputManager();

	static void processKey(int key);
	static bool isKey(int key);
	static bool isKeyDown(int key);
	static bool isKeyUp(int key);

	static void processButton(int key);
	static bool isButton(int key);
	static bool isButtonDown(int key);
	static bool isButtonUp(int key);
};

#endif