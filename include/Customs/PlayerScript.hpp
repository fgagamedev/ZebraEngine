#ifndef __PLAYER_SCRIPT__
#define __PLAYER_SCRIPT__

#include "Engine/InputSystem.hpp"

#include "Components/Script.hpp"

using namespace std;

class PlayerScript : public Script {
public:
  PlayerScript(GameObject *owner);
  virtual string GetComponentName() override { return "PlayerScript"; };
  void ComponentUpdate() override;
  void FixedComponentUpdate() override;

private:
  Vector m_movement = Vector(0, 0);
  float m_speed = 5;
  void HandleInput();
};

#endif
