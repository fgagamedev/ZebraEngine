#include <iostream>

#include "Engine/SceneManager.h"
#include "Log/log.h"

SceneManager *SceneManager::m_instance = 0;

SceneManager::SceneManager() {}

SceneManager::~SceneManager() { m_instance = nullptr; }

SceneManager *SceneManager::GetInstance() {
  if (!m_instance)
    m_instance = new SceneManager();
  return m_instance;
}

void SceneManager::SetCurrentScene(std::string sceneName) {
  auto found = m_scenes.find(sceneName);
  if (found != m_scenes.end()) {
    if (m_currentScene.second != nullptr)
      m_currentScene.second->SetState(SCENE_HIDDEN);

    m_currentScene = std::make_pair(found->first, found->second);
    if (m_currentScene.second->GetState() == SCENE_DEACTIVATED)
      m_currentScene.second->SetState(SCENE_ACTIVATED);
    m_currentScene.second->SetState(SCENE_SHOWN);
  }
}

void SceneManager::AddScene(std::pair<std::string, Scene *> scenePair) {
  scenePair.second->SetName(scenePair.first);
  m_scenes.insert(scenePair);
}

void SceneManager::Start() {
  for (auto scene : m_scenes) {
    if (scene.second->GetState() == SCENE_DEACTIVATED)
      scene.second->SetState(SCENE_ACTIVATED);
  }
}

void SceneManager::Update() {
  if (m_currentScene.second)
    m_currentScene.second->Update();
}

void SceneManager::DrawUpdate() {
  if (m_currentScene.second)
    m_currentScene.second->DrawUpdate();
}

void SceneManager::FixedUpdate() {
  if (m_currentScene.second)
    m_currentScene.second->FixedUpdate();
}

Scene *SceneManager::GetScene(std::string name) {
  for (auto pair : m_scenes) {
    if (pair.first == name)
      return pair.second;
  }
  ERROR("Looking for " << name << " scene which does not exist");
  return nullptr;
}
