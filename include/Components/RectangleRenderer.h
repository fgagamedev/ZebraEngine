#ifndef __RECTANGLE_RENDERER__
#define __RECTANGLE_RENDERER__

#include <string>

#include "Engine/Component.h"
#include "Engine/GameObject.h"
#include "Engine/GraphicsSystem.h"
#include "Math/Vector.h"

using namespace std;

class RectangleRenderer : public Component {
public:
  RectangleRenderer(GameObject *owner, Vector offset, int width, int height);
  void SetColor(int r, int g, int b, int a);
  virtual string GetComponentName() override { return "RectangleRenderer"; };
  virtual void ComponentUpdate() override;

private:
  int m_width, m_height;
  Vector m_offset;
  int m_r = 0, m_g = 0, m_b = 255, m_a = 255;
};

#endif
