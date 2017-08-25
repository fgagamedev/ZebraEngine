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
  void SetColor(int red, int green, int blue, int alpha);
  virtual string GetComponentName() override { return "CircleRenderer"; };
  virtual void ComponentUpdate() override;
private:
    float m_radius;
    int m_red = 0, m_green = 0, m_blue = 255, m_alpha = 255;
    Vector m_offset;
};

#endif
