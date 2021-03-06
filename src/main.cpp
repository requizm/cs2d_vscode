#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>

#if defined(WIN32) && defined(TRACY_ENABLE)
#include <tracy/Tracy.hpp>
#endif

#include "CS2D/Game.hpp"
#include "Core/Window.hpp"

std::unique_ptr<Game> cs2d = std::make_unique<Game>(Game());
auto logger = spdlog::basic_logger_mt("write_logger", "log.txt");

int nbFrames = 0;

int main(int argc, char *argv[])
{
    // FreeConsole();
    GameParameters::LoadParameters();
    Window window("CS2D", GameParameters::SCREEN_WIDTH,
                  GameParameters::SCREEN_HEIGHT);
    Logger::StartApp();

    // Initialize game
    cs2d->Init();

    // DeltaTime variables
    float lastFrame = 0.0F;
    float time = 0.0F;
    InputManager::m_fps = 0;
    int fps = 0;
    InputManager::InitKeyboardKeys();
    while (!glfwWindowShouldClose(window.GetWindow()))
    {
#if defined(WIN32) && defined(TRACY_ENABLE)
        ZoneScoped;
#endif
        const auto currentFrame = static_cast<float>(glfwGetTime());
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
            // nbFrames = 0;
        }

        InputManager::UpdateMouse(window.GetWindow());
        InputManager::UpdateKeyboard(window.GetWindow());
        cs2d->ProcessInput();
        cs2d->Update();

        window.Clear();
        cs2d->Render();

        window.Update();
#if defined(WIN32) && defined(TRACY_ENABLE)
        FrameMark;
#endif
    }

    ResourceManager::Destroy();
    window.Destroy();
    Logger::StopApp();
    return 0;
}