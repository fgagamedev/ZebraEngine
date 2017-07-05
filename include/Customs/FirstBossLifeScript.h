#ifndef __FIRST_BOSS_LIFE_SCRIPT__
#define __FIRST_BOSS_LIFE_SCRIPT__

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

class FirstBossLifeScript : public Script {

public:
  FirstBossLifeScript(GameObject *owner);
  std::string GetComponentName() override { return "FirstBossLifeScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
  bool hit =  false;
 

protected:
  void ComponentUpdate() override;
private:
  Vector *position = nullptr;


 

};

#endif
