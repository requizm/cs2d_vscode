#include "SceneManager.hpp"

#include "../../Core/Manager/InputManager.hpp"
#include "../../Core/Manager/Timer.hpp"

SceneManager::~SceneManager()
{
    activeScene->Unload();
    delete activeScene;
}

void SceneManager::LoadNextScene()
{
    if (!nextSceneName.empty())
    {
        if (activeScene != nullptr)
        {
            activeScene->Unload();
            delete activeScene;
        }
        activeScene = scenes[nextSceneName]();
        activeScene->Load();
        Timer::timeSinceSceneStart = 0.0F;
        nextSceneName = "";
    }
}

void SceneManager::RequestLoadScene(const std::string& name)
{
    if (scenes[name] != nullptr)
    {
        nextSceneName = name;
    }
}

void SceneManager::LoadScene(const std::string& name)
{
    if (scenes[name] != nullptr)
    {
        activeScene = scenes[name]();
        activeScene->Load();
        Timer::timeSinceSceneStart = 0.0F;
    }
}
