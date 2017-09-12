#ifndef __ZEBRA_LOGO_SCRIPT__
#define __ZEBRA_LOGO_SCRIPT__

#include "Engine/Timer.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Math/Vector.hpp"

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
