#ifndef __PLAYER_ATTACK_SCRIPT__
#define __PLAYER_ATTACK_SCRIPT__

#include "Components/Animator.h"
#include "Engine/InputSystem.h"
#include "Components/Script.h"
#include "Engine/GameObject.h"
#include "Components/Renderer.h"
#include "Engine/SceneManager.h"
#include "Engine/CameraSystem.h"
#include "Math/Vector.h"

#include <string>

class PlayerAttackScript : public Script {

public:
  PlayerAttackScript(GameObject *owner);
  std::string GetComponentName() override { return "PlayerAttackScript"; };
  void FixedComponentUpdate() override;
  void Start() override;

protected:
  void ComponentUpdate() override;
private:
  void CreateAnimations();
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  int play=0;
  Vector *bulletVelocity = new Vector(0, 0);
  float bulletSpeed = 10;
  bool shoot = false;


};

#endif