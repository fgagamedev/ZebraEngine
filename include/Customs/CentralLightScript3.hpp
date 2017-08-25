#ifndef __CENTRAL_LIGHT_SCRIPT3__
#define __CENTRAL_LIGHT_SCRIPT3__

#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Math/Vector.hpp"

#include <string>

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
