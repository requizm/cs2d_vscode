#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "../../Core/Manager/InputManager.hpp"
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

    template <typename T>
    T *GetActiveScene();

    /**
     * @brief Deletes old scene resources and load new scene immediately
     * 
     */
    void LoadNextScene();

    void RequestLoadScene(const std::string &name);

    /**
     * @brief Every scene should to be add on beginning of program
     * 
     * @param scene 
     */
    void AddScene(Scene *scene);

    /**
     * @brief Load scene instantly. Just that.
     * 
     */
    void LoadScene(const std::string &name);

    std::vector<Scene *> GetScenes() const;

    std::vector<std::string> params;

   private:
    Scene *activeScene = nullptr;
    Scene *nextScene = nullptr;

    std::vector<Scene *> scenes;
};


#endif  // SCENEMANAGER_H