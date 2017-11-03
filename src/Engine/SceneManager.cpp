/**
    @file SceneManager.cpp
    @brief Methods manage game objects.
    @copyright LGPL. MIT License.
*/
#include "Engine/SceneManager.hpp"

#include "Log/log.hpp"

#include <iostream>

SceneManager *SceneManager::m_instance = 0;

SceneManager::SceneManager() {

}

SceneManager::~SceneManager() {
    m_instance = nullptr;
}

SceneManager *SceneManager::GetInstance() {
    // Check for something diferent of instace and instace a new Scene Manager.
    if (!m_instance) {
        m_instance = new SceneManager();
    }
    return m_instance;
}

void SceneManager::SetCurrentScene(std::string sceneName) {
    auto found = m_scenes.find(sceneName);
    // Check for found diferent of scenes and set the current state.
    if (found != m_scenes.end()) {
        if (m_currentScene.second != nullptr) {
            m_currentScene.second->SetState(SCENE_HIDDEN);
        }

        m_currentScene = std::make_pair(found->first, found->second);
        // Check for found diferent of scenes and set current the state.
        if (m_currentScene.second->GetState() == SCENE_DEACTIVATED) {
            m_currentScene.second->SetState(SCENE_ACTIVATED);
        }
        m_currentScene.second->SetState(SCENE_SHOWN);
    }
}

// Get the current scene name.
std::string SceneManager::GetCurrentSceneName() {
    return m_currentScene.second->GetName();
}

void SceneManager::AddScene(std::pair<std::string, Scene *> scenePair) {
    scenePair.second->SetName(scenePair.first);
    m_scenes.insert(scenePair);
}

void SceneManager::Start() {
    for (auto scene : m_scenes) {
        // Check for the state equal to deactivated and active it.
        if (scene.second->GetState() == SCENE_DEACTIVATED) {
            scene.second->SetState(SCENE_ACTIVATED);
        }
    }
}

void SceneManager::Update() {
    // Check the current scene and update.
    if (m_currentScene.second) {
        m_currentScene.second->Update();
    }
}

void SceneManager::DrawUpdate() {
    // Check the current scene and update the draw.
    if (m_currentScene.second) {
        m_currentScene.second->DrawUpdate();
    }
}

void SceneManager::FixedUpdate() {
    // Check the current scene and fix the update.
    if (m_currentScene.second) {
        m_currentScene.second->FixedUpdate();
    }
}

Scene *SceneManager::GetScene(std::string name) {
    for (auto pair : m_scenes) {
        if (pair.first == name) {
            return pair.second;
        }
    }
    ERROR("Looking for " << name << " scene which does not exist");
    return nullptr;
}
