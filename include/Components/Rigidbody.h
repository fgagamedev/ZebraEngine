#ifndef __RIGIDBODY__
#define __RIGIDBODY__

#include <string>

#include "Engine/Component.h"
#include "Engine/GameObject.h"

class Rigidbody : public Component {
public:
  Rigidbody(GameObject *owner);
  std::string GetComponentName() override { return "Rigidbody"; };
  void FixedComponentUpdate() override;
  inline void SetGravityForce(int force) { m_gravityForce = force; };

private:
  bool m_gravity = true;
  float m_gravityForce = 0.4;
};

#endif
