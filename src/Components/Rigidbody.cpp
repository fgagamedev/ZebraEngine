#include "Components/Rigidbody.hpp"
#include "Globals/ComponentTypes.hpp"
#include "Math/Vector.hpp"

Rigidbody::Rigidbody(GameObject *owner) : Component(owner, C_PHYSICS) {}

void Rigidbody::FixedComponentUpdate() {
  if (m_gravity)
    GetOwner()->AddVelocity(Vector(0, m_gravityForce));

  auto vel = GetOwner()->GetVelocity();
  GetOwner()->GetPosition()->m_x += vel.m_x;
  GetOwner()->GetPosition()->m_y += vel.m_y;
}
