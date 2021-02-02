#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

#include "Game.hpp"
#include "Window.hpp"

std::unique_ptr<Game> cs2d = std::make_unique<Game>(Game());

int nbFrames = 0;

int main(int argc, char *argv[])
{
	//FreeConsole();
	Game_Parameters::LoadParameters();
	Window window("CS2D", Game_Parameters::SCREEN_WIDTH, Game_Parameters::SCREEN_HEIGHT);
	Logger::StartApp();

	// Initialize game
	cs2d->Init();

#ifdef DEBUG
	LOG_ERROR("cum");
#endif // DEBUG

	Logger::WriteLog("cum");

	// DeltaTime variables
	float lastFrame = 0.0F;
	float time = 0.0F;
	InputManager::m_fps = 0;
	int fps = 0;
	InputManager::InitKeyboardKeys();
	while (!glfwWindowShouldClose(window.GetWindow()))
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

		InputManager::UpdateMouse(window.GetWindow());
		InputManager::UpdateKeyboard(window.GetWindow());
		cs2d->ProcessInput();
		cs2d->Update();

		window.Clear();
		cs2d->Render();

		window.Update();
	}

	ResourceManager::Destroy();
	window.Destroy();
	Logger::StopApp();
	return 0;
}