#ifndef __FOREST_ACTIVATOR_SCRIPT3__
#define __FOREST_ACTIVATOR_SCRIPT3__

#include "Engine/Timer.hpp"
#include "Engine/GameController.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Math/Vector.hpp"

#include <string>


class ForestActivatorScript3 : public Script {

public:
  ForestActivatorScript3(GameObject *owner);
  std::string GetComponentName() override { return "ForestActivatorScript3"; };
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
