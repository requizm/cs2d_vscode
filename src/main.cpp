#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.hpp"
#include "Managers/ResourceManager.hpp"
#include "Others/Game_Parameters.hpp"
#include "Others/Logger.hpp"
#include "Others/Timer.hpp"
#include "Managers/InputManager.hpp"
#include <memory>
#include <windows.h>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void character_callback(GLFWwindow *window, unsigned int codepoint);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

//Game_Parameters::LoadParameters();

std::unique_ptr<Game> cs2d(std::make_unique<Game>());

//Game cs2d(SCREEN_WIDTH, SCREEN_HEIGHT);

int nbFrames = 0;
int upFrames = 0;

int main(int argc, char *argv[])
{
	//FreeConsole();
	//Logger::Start();
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
	/*glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);*/
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glLineWidth(4.0F);

	Logger::StartApp();
	// Initialize game
	cs2d->Init();

	// DeltaTime variables
	float lastFrame = 0.0F;
	float time = 0.0F;
	InputManager::m_fps = 0;
	int fps = 0;
	InputManager::InitKeyboardKeys();
	while (!glfwWindowShouldClose(window))
	{
		const float currentFrame = static_cast<float>(glfwGetTime());
		Timer::DeltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		time += Timer::DeltaTime;
		nbFrames++;
		fps++;
		if (time >= 1.0F)
		{
			InputManager::m_fps = fps;
			time = 0.0F;
			fps = 0;
			//nbFrames = 0;
		}

		InputManager::UpdateMouse(window);
		InputManager::UpdateKeyboard(window);
		cs2d->ProcessInput();
		cs2d->Update();

		glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT);
		cs2d->Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Delete all resources as loaded using the resource manager
	ResourceManager::Clear();
	glfwDestroyWindow(window);
	glfwTerminate();
	//Logger::Stop();
	return 0;
}
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	// When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	/*if (action == GLFW_PRESS)
	{
	}
	else if (action == GLFW_RELEASE)
	{
	}*/
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	InputManager::mousePos = Vector2(static_cast<int>(xpos), static_cast<int>(ypos));
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (action == GLFW_RELEASE && upFrames != nbFrames)
	{
		//Logger::DebugLog("frame no: " + std::to_string(nbFrames) + "  up");
		InputManager::onMouseUp(button);
	}
	else if (action == GLFW_PRESS)
	{
		//Logger::DebugLog("frame no: " + std::to_string(nbFrames) + "  down");
		InputManager::onMouseDown(button);
		upFrames = nbFrames;
	}
}

void character_callback(GLFWwindow *window, unsigned int codepoint)
{
	InputManager::keycode = codepoint;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	//Logger::DebugLog(std::to_string(yoffset));
	InputManager::scroll = Vector2(static_cast<float>(xoffset), static_cast<float>(yoffset));
	InputManager::scrollYPressed = true;
}