#ifndef __BULLET_COUNTER_SCRIPT__
#define __BULLET_COUNTER_SCRIPT__


#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Math/Vector.hpp"
#include "Components/UIText.hpp"
#include "Components/Animator.hpp"
#include "Components/Script.hpp"
#include "Customs/NakedManScript.hpp"

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
