#ifndef __CENTRAL_LIGHT_SCRIPT3__
#define __CENTRAL_LIGHT_SCRIPT3__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Math/Vector.h"
#include <string>
#include "Engine/Timer.h"
#include "Engine/GameController.h"

class CentralLightScript3 : public Script {

public:
  CentralLightScript3(GameObject *owner);
  std::string GetComponentName() override { return "CentralLightScript3"; };
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
