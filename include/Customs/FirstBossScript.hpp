#ifndef __FIRST_BOSS_SCRIPT__
#define __FIRST_BOSS_SCRIPT__

#include "Engine/Timer.hpp"
#include "Engine/GraphicsSystem.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Components/Script.hpp"
#include "Components/RectangleCollider.hpp"
#include "Components/Animator.hpp"
#include "Customs/FirstBossController.hpp"
#include "Math/Vector.hpp"

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
