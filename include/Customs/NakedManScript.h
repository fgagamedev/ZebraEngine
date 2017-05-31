#ifndef __NAKED_MAN_SCRIPT__
#define __NAKED_MAN_SCRIPT__

#include "Components/Animator.h"
#include "Components/Script.h"
#include "Components/UIText.h"
#include "Engine/InputSystem.h"
#include "Engine/SceneManager.h"
#include "Globals/EngineGlobals.h"

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
  float walkSpeed = 7;
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  char movements = 0x00; // up down left right
  int deadzone_x = EngineGlobals::screen_width / 2 + 100;
  int deadzone_y = EngineGlobals::screen_height / 2 + 100;
};

#endif
