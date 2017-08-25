#ifndef __CENTRAL_LIGHT_SCRIPT1__
#define __CENTRAL_LIGHT_SCRIPT1__

#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"

#include "Math/Vector.hpp"
#include "Components/Script.hpp"
#include "Components/Animator.hpp"

#include <string>

class CentralLightScript1 : public Script {

public:
  CentralLightScript1(GameObject *owner);
  std::string GetComponentName() override { return "CentralLightScript1"; };
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
