#ifndef __HIT_SCRIPT__
#define __HIT_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"
#include "Math/Vector.h"

#include <string>

class HitScript : public Script {

public:
  HitScript(GameObject *owner);
  std::string GetComponentName() override { return "HitScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
  int play=0;

protected:
  void ComponentUpdate() override;
private:
  void CreateAnimations();
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;

};

#endif
