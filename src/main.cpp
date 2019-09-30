#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "Managers/ResourceManager.h"
#include "Others/Game_Parameters.h"
#include "Others/Logger.h"
#include "Managers/InputManager.h"
#include <memory>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void character_callback(GLFWwindow *window, unsigned int codepoint);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

//Game_Parameters::LoadParameters();

//std::unique_ptr<Game> cs2d(std::make_unique<Game>(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT));
std::unique_ptr<Game> cs2d(std::make_unique<Game>());

//Game cs2d(SCREEN_WIDTH, SCREEN_HEIGHT);

//float lastX = SCREEN_WIDTH / 2.0F;
//float lastY = SCREEN_HEIGHT / 2.0F;
//bool firstMouse = true;

int main(int argc, char *argv[])
{
	Logger::Start();
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT, "CS2D", nullptr, nullptr);
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
	glfwSetCursorPos(window, 1440 / 2, 900 / 2);

	// OpenGL configuration

	glViewport(0, 0, Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_DEPTH_TEST);
	// Initialize game
	cs2d->Init();

	// DeltaTime variables
	float deltaTime = 0.0F;
	float lastFrame = 0.0F;

	// Start Game within Menu State
	//cs2d->State = MENU;
	int nbFrames = 0;
	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		const float currentFrame = static_cast<float>(glfwGetTime());
		//nbFrames++;
		deltaTime = currentFrame - lastFrame;
		//const double timeDelay = 1.0;
		//if (deltaTime >= timeDelay)
		//{
		//std::cout << static_cast<float>(1000) / static_cast<float>(nbFrames) << std::endl;
		//const double fps = nbFrames / deltaTime;
		//std::cout << 1.0 / deltaTime << std::endl;
		//std::cout << fps << std::endl;
		//lastFrame = currentFrame;
		//nbFrames = 0;
		//}
		lastFrame = currentFrame;
		glfwPollEvents();

		//deltaTime = 0.001f;
		// Manage user input
		cs2d->ProcessInput(deltaTime);

		// Update Game state
		cs2d->Update(deltaTime);

		// Render
		glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cs2d->Render(deltaTime);

		glfwSwapBuffers(window);
	}

	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();

	glfwTerminate();
	Logger::Stop();
	return 0;
}
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			InputManager::Keys[key] = GL_TRUE;
			InputManager::KeysUp[key] = GL_FALSE;
			InputManager::downTrigger[key] = GL_TRUE;
		}

		else if (action == GLFW_RELEASE)
		{
			InputManager::Keys[key] = GL_FALSE;
			InputManager::KeysProcessed[key] = GL_FALSE;
			InputManager::KeysUp[key] = GL_TRUE;
			InputManager::upTrigger[key] = GL_TRUE;
		}
	}
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	int lastX = static_cast<float>(xpos);
	int lastY = static_cast<float>(ypos);
	InputManager::mouseX = static_cast<int>(lastX);
	InputManager::mouseY = static_cast<int>(lastY);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (button >= 0 && button < 8)
	{
		/*InputManager::mouseNewKeys[button] = action;
		if (InputManager::mouseOldKeys[button] == GLFW_RELEASE && InputManager::mouseNewKeys[button] == GLFW_PRESS)
		{

		}
		InputManager::mouseOldKeys[button] = InputManager::mouseNewKeys[button];*/

		if (action == GLFW_PRESS)
		{
			InputManager::mouseKeys[button] = GL_TRUE;
			InputManager::mouseKeysUp[button] = GL_FALSE;
			InputManager::mouseDownTrigger[button] = GL_TRUE;
			//InputManager::mouseOldKeys[button] = GLFW_PRESS;
		}

		else if (action == GLFW_RELEASE)
		{
			InputManager::mouseKeys[button] = GL_FALSE;
			InputManager::mouseKeysProcessed[button] = GL_FALSE;
			InputManager::mouseKeysUp[button] = GL_TRUE;
			InputManager::mouseUpTrigger[button] = GL_TRUE;
			//InputManager::mouseOldKeys[button] = GLFW_RELEASE;
			//InputManager::mouseNewKeys[button] = GLFW_RELEASE;
		}
	}
}

void character_callback(GLFWwindow *window, unsigned int codepoint)
{
	//InputManager::keycode = codepoint;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	/*	Game* gm = cs2d.get();
	gm->ScrollCallback(xoffset, yoffset);*/
}