#ifndef __SDL_LOGO_SCRIPT__
#define __SDL_LOGO_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Math/Vector.h"
#include <string>
#include "Engine/Timer.h"

class SdlLogoScript : public Script {

public:
  SdlLogoScript(GameObject *owner);
  std::string GetComponentName() override { return "SdlLogoScript"; };
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
