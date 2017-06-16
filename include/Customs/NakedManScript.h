#ifndef __NAKED_MAN_SCRIPT__
#define __NAKED_MAN_SCRIPT__

#include "Components/Animator.h"
#include "Components/Script.h"
#include "Components/UIText.h"
#include "Engine/InputSystem.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"

class NakedManScript : public Script {
public:
  NakedManScript(GameObject *owner);
  std::string GetComponentName() override { return "NakedManScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
  char GetMovement() { return movements; };

protected:
  void ComponentUpdate() override;

private:
  void CreateAnimations();
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  float walkSpeed = 15;
  int movements=0; //1=UP,2=DOWN,3=LEFT,RIGHT
  int deadzone_x = EngineGlobals::screen_width / 2;
  int deadzone_y = EngineGlobals::screen_height / 2;
  bool shake=false;
  static bool isZooming;

};

#endif
