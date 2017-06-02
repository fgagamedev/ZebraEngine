#ifndef __CIRCLE_COLLIDER__
#define __CIRCLE_COLLIDER__

#include <string>

#include "Components/Collider.h"
#include "Engine/GameObject.h"
#include "Math/Shapes.h"
#include "Math/Vector.h"

using namespace std;

class CircleCollider : public Collider {
public:
  CircleCollider(GameObject *owner, Vector &offset, float radius, int layer);
  Vector GetCenter() { return Vector(m_shape.x, m_shape.y); };
  float GetRadius() { return m_shape.radius; };
  void FixedComponentUpdate() override;
  virtual string GetComponentName() override { return "CircleCollider"; };

private:
  Circle m_shape;
  Vector m_offset;
};

#endif
