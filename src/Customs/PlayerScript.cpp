#include "Customs/PlayerScript.h"

PlayerScript::PlayerScript(GameObject *owner) : Script(owner){};

void PlayerScript::ComponentUpdate() { HandleInput(); }

void PlayerScript::HandleInput() {
  m_movement.m_x = m_movement.m_y = 0;

  if (InputSystem::GetInstance()->GetKeyPressed(INPUT_D))
    m_movement.m_x += 1;
  if (InputSystem::GetInstance()->GetKeyPressed(INPUT_A))
    m_movement.m_x -= 1;
  if (InputSystem::GetInstance()->GetKeyPressed(INPUT_S))
    m_movement.m_y += 1;
  if (InputSystem::GetInstance()->GetKeyPressed(INPUT_W))
    m_movement.m_y -= 1;

  m_movement = m_movement.GetNormalized();
}

void PlayerScript::FixedComponentUpdate() {
  GetOwner()->GetPosition()->m_x += m_movement.m_x * m_speed;
  GetOwner()->GetPosition()->m_y += m_movement.m_y * m_speed;
}
