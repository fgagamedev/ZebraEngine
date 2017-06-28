#ifndef __FIRST_BOSS_ATTACK_SCRIPT__
#define __FIRST_BOSS_ATTACK_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"
#include "Math/Vector.h"
#include "Engine/GraphicsSystem.h"
#include "Components/RectangleCollider.h"

#include <string>

class FirstBossAttackScript : public Script {

public:
  FirstBossAttackScript(GameObject *owner);
  std::string GetComponentName() override { return "FirstBossAttackScript"; };
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
  RectangleCollider* firstBossAttackCollider = nullptr;

};

#endif