#ifndef __RECTANGLE_RENDERER__
#define __RECTANGLE_RENDERER__

#include "Engine/Component.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/GraphicsSystem.hpp"

#include "Math/Vector.hpp"

#include <string>

using namespace std;

class RectangleRenderer : public Component {
public:
  RectangleRenderer(GameObject *owner, Vector offset, int width, int height);
  void SetColor(int r, int g, int b, int a);
  virtual string GetComponentName() override { return "RectangleRenderer"; };
  virtual void ComponentUpdate() override;
  inline void SetWidth(int width) { this->m_width = width; };
  inline int GetWidth() { return m_width; };
private:
  int m_width, m_height;
  Vector m_offset;
  int m_r = 0, m_g = 0, m_b = 255, m_a = 255;
};

#endif
