#include "Components/Renderer.h"
#include "Engine/GameObject.h"
#include "Engine/GraphicsSystem.h"
#include "Globals/ComponentTypes.h"
#include "Log/log.h"

#include <math.h>

void Renderer::ComponentUpdate() {
  std::pair<int, int> sizes =
      std::make_pair(GetOwner()->GetWidth(), GetOwner()->GetHeight());
  GraphicsSystem::GetInstance()->Draw(m_image, m_position, sizes);
}

Renderer::Renderer(GameObject *owner, Image *img) : Component(owner, C_DRAW) {
  m_image = img;

  m_position = GetOwner()->GetPosition();

  if (!m_image)
    ERROR("Null image on renderer");
}

Renderer::~Renderer() { delete m_image; }

void Renderer::Start() {}

void Renderer::RotateTowards(Vector *point) {
  double angles;
  angles = atan2(point->m_y - m_position->m_y, point->m_x - m_position->m_x);
  angles = angles * 180 / 3.1415;
  if (angles < 0)
    angles = 360 - (-angles);
  Rotate(angles);
}

void Renderer::Rotate(double angles) { GetImage()->Rotate(angles); }
