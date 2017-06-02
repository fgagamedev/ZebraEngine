#ifndef __SCENE__
#define __SCENE__

#include <algorithm>
#include <vector>

#include "Engine/GameObject.h"
#include "Globals/SceneStates.h"

class Scene {
public:
  // constructor and destructor
  Scene();
  ~Scene();
  // start and update handling
  virtual void Start() final;
  virtual void Update() final;
  virtual void FixedUpdate() final;
  virtual void DrawUpdate() final;
  // handle gameobjects
  virtual void AddGameObject(GameObject *gameObject) final;
  virtual void AddGameObject(std::vector<GameObject *> gameObjects) final;
  virtual GameObject *GetGameObject(std::string name) final;
  virtual std::vector<GameObject *> GetAllGameObjects() final {
    return m_gameObjects;
  };
  // states
  virtual void SetState(SceneStates state) final;
  virtual inline SceneStates GetState() final { return m_currentState; };
  // getter and setter
  virtual inline void SetName(std::string name) final { m_name = name; };
  virtual inline std::string GetName() final { return m_name; };
  // method for handling state changing
  virtual void Activation() final;
  virtual void Deactivation() final;
  virtual void Shown() final;
  virtual void Hidden() final;
  // method for being overrided
  virtual void OnActivation(){};
  virtual void OnDeactivation(){};
  virtual void OnShown(){};
  virtual void OnHidden(){};
  // compare gameobjects
  static bool CompareGameObjects(GameObject *a, GameObject *b) {
    return a->GetLayer() < b->GetLayer();
  };

private:
  // scene name
  std::string m_name;
  // scene state
  SceneStates m_currentState = SCENE_DEACTIVATED;
  // gameobjects vector
  std::vector<GameObject *> m_gameObjects;
};

#endif // __SCENE__
