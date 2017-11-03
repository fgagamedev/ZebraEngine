/**
    @file Scene.cpp
    @brief Methods that manages all scenes in the game.
    @copyright LGPL. MIT License.
*/

#include "Engine/Scene.hpp"

#include "Log/log.hpp"

// Constructor.
Scene::Scene() {

}

Scene::~Scene() {

}

/**
    @brief That function is for start the scene of the game.
*/
void Scene::Start() {
    // Run through the vector of game objects, starting them.
    for (auto object : m_gameObjects) {
        object->Start();
    }
}

/**
    @brief That function is for update the scene of the game.
    Compare the game objects, the begin and end objects. Checks if is
    active and update it.
*/
void Scene::Update() {
    // Sort and compares the gameobjects by the first element in its vector, and the last one, for update them.
    std::sort(m_gameObjects.begin(), m_gameObjects.end(), CompareGameObjects);
    for (auto it : m_gameObjects) {
        // Check if is active and them update it.
        if (it->active) {
            it->Update();
        }
    }
}

/**
    @brief That function is for update the draws of the game.
    Compare the game objects, the begin and end objects. Checks if is
    active and update the draws.
*/
void Scene::DrawUpdate() {
    // Sort and compares the gameobjects by the first element in its vector, and the last one, for update the object's draw.
    std::sort(m_gameObjects.begin(), m_gameObjects.end(), CompareGameObjects);
    for (auto it : m_gameObjects) {
        // Check if is active and them update it.
        if (it->active) {
            it->DrawUpdate();
        }
    }
}

/**
    @brief that function is for add the gameobjects to the game
    @param[in] GameObject pointer that points to the current gameobject
*/
void Scene::AddGameObject(GameObject *gameObject) {
    //Appends a gameobject to the end of the vector of gameobjects.
    m_gameObjects.push_back(gameObject);
}

void Scene::AddGameObject(std::vector<GameObject *> gameObjects) {
    //Inserts gameobjects in the end-position of the vector of gameobjects.
    m_gameObjects.insert(std::end(m_gameObjects), std::begin(gameObjects),
    std::end(gameObjects));
}

/**
    @brief That function is for fix the updates made before.
    Checks if gameObjects are active and fix the update.
*/
void Scene::FixedUpdate() {
    //Run through the gameobjects vector, and updates the active gameObjects.
    for (auto it : m_gameObjects) {
        // Check if is active and them update it.
        if (it->active) {
            it->FixedUpdate();
        }
    }
}

/**
    @brief set the state of the scene. Check the states of the scene,
    if is activated, deactivated, hidden and shown and change the state according
    to the state.
    @param[in] state = is the state of the scene.
*/
void Scene::SetState(SceneStates state) {
    // Sets the current state scene according to the int constants defined on the SceneStates enum.
    m_currentState = state;
    INFO("[SCENE] " << m_name << " state: " << m_currentState);

    // Check if the state is scene activated and call for Activation.
    if (state == SCENE_ACTIVATED) {
        Activation();
    // Check if the state is scene deactivated and call for Deactivation.
    } else if (state == SCENE_DEACTIVATED) {
        Deactivation();
    // Check if the state is scene hidden and call for Hidden.
    } else if (state == SCENE_HIDDEN) {
        Hidden();
    // Check if the state is scene shown and call for shown.
    } else if (state == SCENE_SHOWN) {
        Shown();
    }
}

/**
    @brief That function is for when the state is activated. So the Scene
    starts.
*/
void Scene::Activation() {
    OnActivation();
    Start();
}

/**
    @brief That function is for when the state isn't activated.
*/
void Scene::Deactivation() {
    OnDeactivation();
}

/**
    @brief That function is for when the state is shown.
*/
void Scene::Shown() {
    OnShown();
}

/**
    @brief That function is for when the state is shown.
*/
void Scene::Hidden() {
    OnHidden();
}

/**
    @brief Get the name of a scene gameobject.
    @param[in] name - the name of the searched scene.
    @return nullptr if the name doesn't match any gameobject, or the scene name found.
*/
GameObject *Scene::GetGameObject(std::string name) {
    //Run through the gameobjects vector, and get one gameobject by the given name.
    for (auto it : m_gameObjects) {
        if (it->GetName() == name) {
            return it;
        }
    }
    return nullptr;
}
