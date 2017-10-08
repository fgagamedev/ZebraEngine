/**
    @file SceneManager.hpp
    @brief Class that defines methods for managing the scenes of the game.
    @copyright LGPL. MIT License.
*/

#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "Engine/Scene.hpp"

#include <string>
#include <unordered_map>
#include <string>

class SceneManager {
public:
    // Singleton getter.
    static SceneManager *GetInstance();

    // Scene managing methods.
    Scene *GetCurrentScene() { return m_currentScene.second; };
    Scene *GetScene(std::string name);
    void SetCurrentScene(std::string sceneName);
    void AddScene(std::pair<std::string, Scene *> scenePair);

    // Start and update handlers.
    void Start();
    void Update();
    void FixedUpdate();
    void DrawUpdate();

    std::string GetCurrentSceneName();

private:
    // Constructor and destructor.
    SceneManager();
    ~SceneManager();

    // Scene handling attributes.
    static SceneManager *m_instance;

    // Builds an unordered map with the current scene name.
    std::unordered_map<std::string, Scene *> m_scenes;

    // Pair two objects of arbitrary type in a struct with the current scene name.
    std::pair<std::string, Scene *> m_currentScene;
};

#endif // __SCENE_MANAGER__
