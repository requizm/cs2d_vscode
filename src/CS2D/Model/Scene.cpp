#include "Scene.hpp"

#include "../Other/SceneManager.hpp"


Scene::Scene(const std::string& name)
{
    std::vector<Scene*> scenes = SceneManager::instance().GetScenes();
    for (auto& scene : scenes)
    {
        if (scene->GetName() == name)
        {
            //WRONG NAME
            return;
        }
    }
    this->name = name;
    SceneManager::instance().AddScene(this);
}

Scene::~Scene()
{
    Unload();
}

std::string Scene::GetName() const { return name; }

void Scene::ProcessInput()
{
}

void Scene::Update()
{
}

void Scene::Render()
{
}


void Scene::Load()
{
}

void Scene::Unload()
{
}
