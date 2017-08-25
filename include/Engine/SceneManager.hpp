#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "Engine/Scene.hpp"

#include <string>
#include <unordered_map>
#include <string>

class SceneManager {
public:
  // singleton getter
  static SceneManager *GetInstance();
  // scene managing methods
  Scene *GetCurrentScene() { return m_currentScene.second; };
  Scene *GetScene(std::string name);
  void SetCurrentScene(std::string sceneName);
  void AddScene(std::pair<std::string, Scene *> scenePair);
  // start and update handlers
  void Start();
  void Update();
  void FixedUpdate();
  void DrawUpdate();

  std::string GetCurrentSceneName();

private:
  // constructor and destructor
  SceneManager();
  ~SceneManager();
  // scene handling attributes
  static SceneManager *m_instance;
  std::unordered_map<std::string, Scene *> m_scenes;
  std::pair<std::string, Scene *> m_currentScene;
};

#endif // __SCENE_MANAGER__
