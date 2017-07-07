#ifndef __CONTROLE_LOGO_SCRIPT__
#define __CONTROLE_LOGO_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Math/Vector.h"
#include <string>
#include "Engine/Timer.h"

class ControleLogoScript : public Script {

public:
  ControleLogoScript(GameObject *owner);
  std::string GetComponentName() override { return "ControleLogoScript"; };
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
