#ifndef __FIRST_BOSS_SCRIPT__
#define __FIRST_BOSS_SCRIPT__

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

class FirstBossScript : public Script {

public:
  FirstBossScript(GameObject *owner);
  std::string GetComponentName() override { return "FirstBossScript"; };
  void FixedComponentUpdate() override;
  void Start() override;

protected:
  void ComponentUpdate() override;
private:
  void CreateAnimations();

  RectangleCollider *firstBossCollider = nullptr;
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;


};

#endif