#ifndef __FIRST_BOSS_SCRIPT__
#define __FIRST_BOSS_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"
#include "Math/Vector.h"
#include "Engine/GraphicsSystem.h"
#include "Components/RectangleCollider.h"
#include "Engine/Timer.h"
#include "Customs/FirstBossController.h"

#include <string>

class FirstBossScript : public Script {

public:
  FirstBossScript(GameObject *owner);
  std::string GetComponentName() override { return "FirstBossScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
  void Attack();

protected:
  void ComponentUpdate() override;
private:
  void CreateAnimations();

  RectangleCollider *firstBossCollider = nullptr;
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  GameObject *player = nullptr;
  Vector playerPosition = Vector(0,0);

  Timer timerFirstAttackCooldown;
  Timer timerFirstAttackGone;
  Timer timerAttackCooldown;
  Timer timerSecondAttack;
  Timer timerSecondAttackFall;

  
  bool FirstAttack = false;
  bool goneFirstAttack = false;
  bool SecondAttack = false;
  bool SecondAttackJump = false;
  bool SecondAttackFall = false;

  bool shake = false;


  int firstAttackCounter = 0;
  int randNum = -1;


};

#endif