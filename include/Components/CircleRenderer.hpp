#ifndef __CIRCLE_RENDERER__
#define __CIRCLE_RENDERER__

#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/GraphicsSystem.hpp"

#include "Math/Vector.hpp"

#include <string>

using namespace std;

class CircleRenderer : public Component {
public:
  CircleRenderer(GameObject *owner, Vector offset, float radius);
  void SetColor(int r, int g, int b, int a);
  virtual string GetComponentName() override { return "CircleRenderer"; };
  virtual void ComponentUpdate() override;

private:
  float m_radius;
  Vector m_offset;
  int m_r = 0, m_g = 0, m_b = 255, m_a = 255;
};

#endif
