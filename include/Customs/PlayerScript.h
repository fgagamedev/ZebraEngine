#ifndef __PLAYER_SCRIPT__
#define __PLAYER_SCRIPT__

#include "Components/Script.h"
#include "Engine/InputSystem.h"

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
