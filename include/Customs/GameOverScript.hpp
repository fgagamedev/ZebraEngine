#ifndef __GAME_OVER_SCRIPT__
#define __GAME_OVER_SCRIPT__

#include "Engine/GameObject.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/CameraSystem.hpp"
#include "Engine/InputSystem.hpp"

#include "Components/Script.hpp"
#include "Components/Animator.hpp"
#include "Customs/AudioController.hpp"

#include <string>

class GameOverScript : public Script {

public:
  GameOverScript(GameObject *owner);
  std::string GetComponentName() override { return "SnowScript"; };
  void FixedComponentUpdate() override;
  void Start() override;
 // char GetMovement() { return movements; };

protected:
  void ComponentUpdate() override;
private:
  void CreateAnimations();
  InputSystem *input = nullptr;
  Animator *animator = nullptr;
  Vector *position = nullptr;
  int play=0;

};

#endif
