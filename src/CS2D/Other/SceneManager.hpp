#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <map>
#include <functional>

#include "../Model/Scene.hpp"

class SceneManager
{
   public:
    static SceneManager &instance()
    {
        static SceneManager INSTANCE;
        return INSTANCE;
    }


    SceneManager() = default;
    SceneManager(SceneManager &&) = default;
    SceneManager(const SceneManager &) = default;
    SceneManager &operator=(SceneManager &&) = default;
    SceneManager &operator=(const SceneManager &) = default;
    ~SceneManager();

    template <class T>
    T *GetActiveScene()
    {
        return reinterpret_cast<T *>(activeScene);
    }

    /**
     * @brief Deletes old scene resources and load new scene immediately
     * 
     */
    void LoadNextScene();

    void RequestLoadScene(const std::string &name);

    /**
     * @brief Load scene instantly. Just that.
     * 
     */
    void LoadScene(const std::string &name);

    std::vector<std::string> params;

    typedef std::map<std::string, std::function<Scene*()>> SceneType;
    SceneType scenes;

   private:
    Scene *activeScene = nullptr;
    std::string nextSceneName;
};


#endif  // SCENEMANAGER_H