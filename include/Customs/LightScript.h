#ifndef __LIGHT_SCRIPT__
#define __LIGHT_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"
#include "Math/Vector.h"

#include <string>

class LightScript : public Script {

public:
  LightScript(GameObject *owner);
  std::string GetComponentName() override { return "RainScript"; };
  void FixedComponentUpdate() override;
  void Start() override;

protected:
  void ComponentUpdate() override;
private:
  void CreateAnimations();
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  GameObject *player = nullptr;
  int play=0;

};

#endif
