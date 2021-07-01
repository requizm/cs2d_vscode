#include "SceneManager.hpp"

#include "../Model/Scene.hpp"
#include "../Scene/Menu.hpp"
#include "../Scene/StartGame.hpp"
#include "../Scene/Editor/Editor.hpp"

SceneManager::~SceneManager()
{
    for (auto& scene : scenes)
    {
        delete &scene;
    }
}

template <typename T>
T* SceneManager::GetActiveScene()
{
    return reinterpret_cast<T*>(activeScene);
}

void SceneManager::LoadNextScene()
{
    if (nextScene != nullptr)
    {
        if (activeScene != nullptr)
        {
            activeScene->Unload();
            InputManager::removeAllListeners();
        }
        activeScene = nextScene;
        activeScene->Load();

        nextScene = nullptr;
    }
}

void SceneManager::RequestLoadScene(const std::string& name)
{
    Scene* sc = nullptr;
    for (auto& scene : scenes)
    {
        if (scene->GetName() == name)
        {
            sc = scene;
            break;
        }
    }

    if (sc != nullptr)
    {
        nextScene = sc;
    }
    else
    {
        //boyle bir sahne yok
    }
}

void SceneManager::AddScene(Scene* scene)
{
    scenes.push_back(scene);
}

void SceneManager::LoadScene(const std::string &name)
{
    Scene* sc = nullptr;
    for (auto& scene : scenes)
    {
        if (scene->GetName() == name)
        {
            sc = scene;
            break;
        }
    }

    if (sc != nullptr)
    {
        activeScene = sc;
        activeScene->Load();
    }
    else
    {
        //boyle bir sahne yok
    }
}

std::vector<Scene*> SceneManager::GetScenes() const { return scenes; }
