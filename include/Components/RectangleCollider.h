#ifndef __RECTANGLE_COLLIDER__
#define __RECTANGLE_COLLIDER__

#include "Components/Collider.h"
#include "Engine/GameObject.h"
#include "Math/Shapes.h"
#include "Math/Vector.h"

using namespace std;

class RectangleCollider : public Collider {
public:
  RectangleCollider(GameObject *owner, Vector offset, float width, float height,
                    int layer);
  void FixedComponentUpdate() override;
  Vector GetRectanglePoint() { return Vector(m_shape.x, m_shape.y); };
  float GetWidth() { return m_shape.width; };
  float GetHeight() { return m_shape.height; };
  virtual string GetComponentName() override { return "RectangleCollider"; };

private:
  Rectangle m_shape;
  Vector m_offset;
};

#endif // __RECTANGLE_COLLIDER__
