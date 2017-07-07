#ifndef __SNOW_ACTIVATOR_SCRIPT__
#define __SNOW_ACTIVATOR_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Math/Vector.h"
#include <string>
#include "Engine/Timer.h"
#include "Engine/GameController.h"


#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Math/Vector.h"
#include <string>
#include "Engine/Timer.h"
#include "Engine/GameController.h"

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
