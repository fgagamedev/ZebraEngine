#ifndef __BULLET_COUNTER_SCRIPT__
#define __BULLET_COUNTER_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Customs/NakedManScript.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"
#include "Math/Vector.h"
#include "Components/UIText.h"

#include <string>

class BulletCounterScript : public Script {

public:
  BulletCounterScript(GameObject *owner);
  std::string GetComponentName() override { return "BulletCounterScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
 

protected:
  void ComponentUpdate() override;
private:
  Vector *position = nullptr;
  int m_numberBullet;

};

#endif
