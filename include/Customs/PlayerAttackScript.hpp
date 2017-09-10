#ifndef __PLAYER_ATTACK_SCRIPT__
#define __PLAYER_ATTACK_SCRIPT__

#include "Engine/GraphicsSystem.hpp"
#include "Engine/InputSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"

#include "Components/Script.hpp"
#include "Components/Renderer.hpp"
#include "Components/RectangleCollider.hpp"
#include "Components/Animator.hpp"
#include "Customs/FirstBossLifeScript.hpp"
#include "Customs/AudioController.hpp"
#include "Math/Vector.hpp"

#include <string>

/**
    @file PlayerAttackScript.hpp
    @brief Class that represents the Script of the player attack 
    @copyright LGPL. MIT License.
*/

class PlayerAttackScript : public Script {

public:
  PlayerAttackScript(GameObject *owner);
  std::string GetComponentName() override { return "PlayerAttackScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
  void SetShoot(bool shoot);
  void GameCollisionCheck();

protected:
  void ComponentUpdate() override;
private:
  void CreateAnimations();
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  RectangleCollider* playerCollider =  nullptr;


  Vector mousePosition = Vector(0,0);
  Vector playerPosition = Vector(0,0);
  GameObject *player = nullptr;

  bool shoot = false;
  int play=0;
  float angle=0;
  Vector bulletVelocity = Vector(0, 0);

  float bulletSpeed = 30;



};

#endif
