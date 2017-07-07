#ifndef __UNB_LOGO_SCRIPT__
#define __UNB_LOGO_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Math/Vector.h"
#include <string>
#include "Engine/Timer.h"
#include "Engine/GameController.h"

class UnbLogoScript : public Script {

public:
  UnbLogoScript(GameObject *owner);
  std::string GetComponentName() override { return "UnbLogoScript"; };
  void FixedComponentUpdate() override;
  void Start() override;

protected:
  void ComponentUpdate() override;
private:
  Timer time;
  void CreateAnimations();
  InputSystem *input = nullptr;
    GameController* gamecontroller = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  int play=0;

};
#endif
