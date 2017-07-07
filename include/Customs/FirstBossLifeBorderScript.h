#ifndef __FIRST_BOSS_LIFE_BORDER_SCRIPT__
#define __FIRST_BOSS_LIFE_BORDER_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Customs/NakedManScript.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"
#include "Math/Vector.h"
#include "Components/RectangleRenderer.h"
#include "Components/UIText.h"

#include <string>

class FirstBossLifeBorderScript : public Script {

public:
  FirstBossLifeBorderScript(GameObject *owner);
  std::string GetComponentName() override { return "FirstBossLifeBorderScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
  void CreateAnimations();
  
 

protected:
  void ComponentUpdate() override;
private:
  Vector *position = nullptr;
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  
  RectangleCollider* firstBossAttackCollider = nullptr;




 

};

#endif
