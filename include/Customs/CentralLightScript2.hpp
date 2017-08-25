#ifndef __CENTRAL_LIGHT_SCRIPT2__
#define __CENTRAL_LIGHT_SCRIPT2__

#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/InputSystem.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Math/Vector.hpp"

#include <string>

class CentralLightScript2 : public Script {

public:
  CentralLightScript2(GameObject *owner);
  std::string GetComponentName() override { return "CentralLightScript2"; };
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
