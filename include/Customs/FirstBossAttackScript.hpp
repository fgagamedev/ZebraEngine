/**
    @file FirstBossAttackScript.hpp
    @brief  Manage the animations for the first boss attack effect.
    @copyright MIT License.
*/

#ifndef __FIRST_BOSS_ATTACK_SCRIPT__
#define __FIRST_BOSS_ATTACK_SCRIPT__

#include "Engine/Timer.hpp"
#include "Engine/GraphicsSystem.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Components/Script.hpp"
#include "Components/UISound.hpp"
#include "Components/Animator.hpp"
#include "Components/RectangleCollider.hpp"
#include "Customs/FirstBossController.hpp"
#include "Math/Vector.hpp"

#include <string>

class FirstBossAttackScript : public Script {

public:
  FirstBossAttackScript(GameObject *owner);
  // Get the component name and replace it by returning its string name.
  std::string GetComponentName() override {
      return "FirstBossAttackScript";
  };
  void FixedComponentUpdate() override;
  void Start() override;

  void Attack();

  // Previous Animation Control Variable.
  bool goneAnimation = false;

  // Boolean variable that stores false or true for boss attack.
  bool attack = false;

  // Boolean variable that stores false or true for shake image.
  bool cameraShake =  false;

  // Bollean variable that store false or true for desactivate object.
  bool deactivateObj = false;


private:
  void CreateAnimations();
  void CameraShakeAttack();

  // Pointer to game controls
  InputSystem *m_input = nullptr;

  // Pointer to animator game.
  Animator *m_animator = nullptr;

  // Poiter to position of gamer.
  Vector *m_position = nullptr;

  // A rectangleCollider pointer that defines the first collision of the boss's attack.
  RectangleCollider* m_firstBossAttackCollider = nullptr;

  // Variable that stores true or false that assists in the beginning of the animation of the attack of the boss.
  bool m_surgeAnimation = true;

  bool m_idleAnimation = false;

  // Variable of type Timer that defines the gone time.
  Timer timerGone;

  // Variable of type Time that defines the animation time.
  Timer timerAnimation;

  Timer timerIdleAnimation;

  inline void SetSurgeAnimation(bool surgeAnimation) {
      m_surgeAnimation = surgeAnimation;
  };

  inline void SetIdleAnimation(bool idleAnimation) {
      m_idleAnimation = idleAnimation;
  };
  inline void SetGoneAnimation(bool goneAnimation) {
      goneAnimation = goneAnimation;
  };

protected:
  void ComponentUpdate() override;

};

#endif
