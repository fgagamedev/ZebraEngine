#ifndef __ZEBRA_LOGO_SCRIPT__
#define __ZEBRA_LOGO_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Math/Vector.h"
#include "Engine/Timer.h"
#include <string>

class ZebraLogoScript : public Script {

public:
  ZebraLogoScript(GameObject *owner);
  std::string GetComponentName() override { return "ZebraLogoScript"; };
  void FixedComponentUpdate() override;
  void Start() override;

protected:
  void ComponentUpdate() override;
private:
  Timer time;
  void CreateAnimations();
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  int play=0;

};
#endif
