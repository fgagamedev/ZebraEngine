#include "Engine/Scene.h"
#include "Log/log.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::Start() {
  for (auto obj : m_gameObjects)
    obj->Start();
}

void Scene::Update() {
  std::sort(m_gameObjects.begin(), m_gameObjects.end(), CompareGameObjects);
  for (auto it : m_gameObjects)
    if (it->active)
      it->Update();
}

void Scene::DrawUpdate() {
  std::sort(m_gameObjects.begin(), m_gameObjects.end(), CompareGameObjects);
  for (auto it : m_gameObjects)
    if (it->active)
      it->DrawUpdate();
}

void Scene::AddGameObject(GameObject *gameObject) {
  m_gameObjects.push_back(gameObject);
}

void Scene::AddGameObject(std::vector<GameObject *> gameObjects) {
  m_gameObjects.insert(std::end(m_gameObjects), std::begin(gameObjects),
                       std::end(gameObjects));
}

void Scene::FixedUpdate() {
  for (auto it : m_gameObjects)
    if (it->active)
      it->FixedUpdate();
}

void Scene::SetState(SceneStates state) {
  m_currentState = state;
  INFO("[SCENE] " << m_name << " state: " << m_currentState);

  if (state == SCENE_ACTIVATED)
    Activation();
  else if (state == SCENE_DEACTIVATED)
    Deactivation();
  else if (state == SCENE_HIDDEN)
    Hidden();
  else if (state == SCENE_SHOWN)
    Shown();
}

void Scene::Activation() {
  OnActivation();
  Start();
}

void Scene::Deactivation() { OnDeactivation(); }

void Scene::Shown() { OnShown(); }

void Scene::Hidden() { OnHidden(); }

GameObject *Scene::GetGameObject(std::string name) {
  for (auto it : m_gameObjects)
    if (it->GetName() == name)
      return it;
  return nullptr;
}
