#ifndef _BOSS_1_CENTRAL_SCRIPT__
#define _BOSS_1_CENTRAL_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"
#include "Math/Vector.h"

#include <string>

class FirstBossCentralEffectScript : public Script {

public:
  FirstBossCentralEffectScript(GameObject *owner);
  std::string GetComponentName() override { return "FirstBossCentralEffectScript"; };
  void FixedComponentUpdate() override;
  void Start() override;

protected:
  void ComponentUpdate() override;
private:
  void CreateAnimations();
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  GameObject *boss = nullptr;

};

#endif