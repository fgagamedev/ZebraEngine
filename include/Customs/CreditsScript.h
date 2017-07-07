#ifndef __CREDITS_SCRIPT__
#define __CREDITS_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Customs/NakedManScript.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"
#include "Math/Vector.h"
#include "Components/RectangleRenderer.h"
#include "Customs/FirstBossController.h"
#include "Components/UIText.h"

#include <string>

class CreditsScript : public Script {

public:
  CreditsScript(GameObject *owner);
  std::string GetComponentName() override { return "CreditsScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
 

protected:
  void ComponentUpdate() override;
private:
  Vector *position = nullptr;


 

};

#endif
