#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

class Scene
{
   public:
    Scene(const std::string &name);
    Scene(Scene &&) = default;
    Scene(const Scene &) = default;
    Scene &operator=(Scene &&) = default;
    Scene &operator=(const Scene &) = default;
    ~Scene();

   public:
    virtual void Load();
    virtual void Unload();
    std::string GetName() const;

    virtual void ProcessInput();
    virtual void Update();
    virtual void Render();

   private:
    std::string name;
};

#endif  // SCENE_H