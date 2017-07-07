#ifndef __RAIN_SCRIPT__
#define __RAIN_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"
#include "Customs/AudioController.h"
#include "Math/Vector.h"

#include <string>

class RainScript : public Script {

public:
  RainScript(GameObject *owner);
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
  int play=0;

};

#endif
