#include "Scene.hpp"

Scene::Scene(const std::string& name)
{
    this->name = name;
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
