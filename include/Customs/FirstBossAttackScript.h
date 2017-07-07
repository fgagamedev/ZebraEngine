#ifndef __FIRST_BOSS_ATTACK_SCRIPT__
#define __FIRST_BOSS_ATTACK_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Components/UISound.h"
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"
#include "Customs/FirstBossController.h"
#include "Math/Vector.h"
#include "Engine/GraphicsSystem.h"
#include "Components/RectangleCollider.h"
#include "Engine/Timer.h"

#include <string>

class FirstBossAttackScript : public Script {

public:
  FirstBossAttackScript(GameObject *owner);
  std::string GetComponentName() override { return "FirstBossAttackScript"; };
  void FixedComponentUpdate() override;
  void Start() override;

  void Attack();
  
  bool m_surgeAnimation = true;
  bool m_idleAnimation = false;
  bool m_goneAnimation = false;
  bool m_noAnimation = false;
  bool attack = false;
  bool shake =  false;
  bool desactivateObj = false;

protected:
  void ComponentUpdate() override;
private:
  void CreateAnimations();
  void CameraShakeAttack();
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  GameObject *boss = nullptr;
  RectangleCollider* firstBossAttackCollider = nullptr;
  int m_tentaclesFrames = 0;

  Timer timerGone;
  Timer timerAnimation;
  Timer timerIdleAnimation;


  
  double attackDuration = 4;
  inline void SetSurgeAnimation(bool surgeAnimation) {m_surgeAnimation = surgeAnimation; };
  inline void SetIdleAnimation(bool idleAnimation) {m_idleAnimation = idleAnimation; };
  inline void SetGoneAnimation(bool goneAnimation) {m_goneAnimation = goneAnimation; };

};

#endif