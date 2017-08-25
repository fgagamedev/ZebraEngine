#ifndef __SNOW_ACTIVATOR_SCRIPT__
#define __SNOW_ACTIVATOR_SCRIPT__

#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Math/Vector.hpp"

#include <string>

class SnowActivatorScript : public Script {

public:
  SnowActivatorScript(GameObject *owner);
  std::string GetComponentName() override { return "SnowActivatorScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
  void Activate(){activate=0;}
protected:
  void ComponentUpdate() override;
private:
  int activate=-1;
  bool runned=false;
  Timer time;
  void CreateAnimations();
  InputSystem *input = nullptr;
   GameController* gamecontroller = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  int play=0;

};
#endif
