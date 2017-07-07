#ifndef __CUT_SCENE1_SCRIPT__
#define __CUT_SCENE1_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Math/Vector.h"
#include <string>
#include "Engine/Timer.h"
#include "Engine/GameController.h"

class CutScene1Script : public Script {

public:
  CutScene1Script(GameObject *owner);
  std::string GetComponentName() override { return "CutScene1Script"; };
  void FixedComponentUpdate() override;
  void Start() override;
  void Activate(){active = true;}

protected:
  void ComponentUpdate() override;
private:
  bool active=false;
  Timer time;
  void CreateAnimations();
  InputSystem *input = nullptr;
   GameController* gamecontroller = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  int play=0;

};
#endif
