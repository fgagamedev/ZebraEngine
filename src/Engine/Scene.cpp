#include "Engine/Scene.hpp"

#include "Log/log.hpp"

Scene::Scene() {}

Scene::~Scene() {}

/**
    @brief That function is for starts the scene of the game.
*/
void Scene::Start() {
    for (auto obj : m_gameObjects) {
        obj->Start();
    }
}

/**
    @brief That function is for update the scene of the game.
    Compare the game objects, the begin and end objects. Checks if is
    active and update it.
*/
void Scene::Update() {
    std::sort(m_gameObjects.begin(), m_gameObjects.end(), CompareGameObjects);
    for (auto it : m_gameObjects) {
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
    std::sort(m_gameObjects.begin(), m_gameObjects.end(), CompareGameObjects);
    for (auto it : m_gameObjects) {
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
    m_gameObjects.push_back(gameObject);
}

void Scene::AddGameObject(std::vector<GameObject *> gameObjects) {
    m_gameObjects.insert(std::end(m_gameObjects), std::begin(gameObjects),
    std::end(gameObjects));
}

/**
    @brief That function is for fix the updates made before.
    Checks if gameObjects are active and fix the update.
*/
void Scene::FixedUpdate() {
    for (auto it : m_gameObjects) {
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
    m_currentState = state;
    INFO("[SCENE] " << m_name << " state: " << m_currentState);

    if (state == SCENE_ACTIVATED) {
        Activation();
    } else if (state == SCENE_DEACTIVATED) {
        Deactivation();
    } else if (state == SCENE_HIDDEN) {
        Hidden();
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

GameObject *Scene::GetGameObject(std::string name) {
    for (auto it : m_gameObjects) {
        if (it->GetName() == name) {
            return it;
        }
    }
    return nullptr;
}
