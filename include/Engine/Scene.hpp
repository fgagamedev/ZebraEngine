/**
    @file Scene.hpp
    @brief Class that represents the scene of the game.
    @copyright LGPL. MIT License.
*/

#ifndef __SCENE__
#define __SCENE__

#include "Engine/GameObject.hpp"
#include "Globals/SceneStates.hpp"

#include <algorithm>
#include <vector>


class Scene {
public:
    // Constructor and destructor.
    Scene();
    ~Scene();

    // Start and update handling.
    virtual void Start() final;
    virtual void Update() final;
    virtual void FixedUpdate() final;
    virtual void DrawUpdate() final;

    // Handle gameobjects.
    virtual void AddGameObject(GameObject *gameObject) final;
    virtual void AddGameObject(std::vector<GameObject *> gameObjects) final;
    virtual GameObject *GetGameObject(std::string name) final;
    virtual std::vector<GameObject *> GetAllGameObjects() final {
      return m_gameObjects;
    };

    // States.
    virtual void SetState(SceneStates state) final;
    virtual inline SceneStates GetState() final { return m_currentState; };

    // Getter and setter.
    virtual inline void SetName(std::string name) final { m_name = name; };
    virtual inline std::string GetName() final { return m_name; };

    // Method for handling state changing.
    virtual void Activation() final;
    virtual void Deactivation() final;
    virtual void Shown() final;
    virtual void Hidden() final;

    // Method for being overrided.
    virtual void OnActivation(){};
    virtual void OnDeactivation(){};
    virtual void OnShown(){};
    virtual void OnHidden(){};

    // Compare gameobjects.
    static bool CompareGameObjects(GameObject *a, GameObject *b) {
      return a->GetLayer() < b->GetLayer();
    };

private:
    // Sets the scene name.
    std::string m_name;

    // Sets the scene state to deactivated.
    SceneStates m_currentState = SCENE_DEACTIVATED;

    // Sets a vector of gameobjects.
    std::vector<GameObject *> m_gameObjects;
};

#endif // __SCENE__
