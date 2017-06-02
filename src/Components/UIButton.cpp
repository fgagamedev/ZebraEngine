#include "Components/UIButton.h"
#include "Engine/GameObject.h"
#include "Engine/SDLSystem.h"
#include "Globals/ComponentTypes.h"
#include "Globals/InputGlobals.h"
#include "Log/log.h"

UIButton::UIButton(GameObject *owner) : Component(owner, C_DRAW) {}

void UIButton::Start() {
  // case exists
  m_position = GetOwner()->GetPosition();
}

bool UIButton::IsClicked() {
  // checking if mouse is over button and clicked
  if (IsOver() && InputSystem::GetInstance()->GetMouseButtonDown(M_INPUT_LEFT))
    return true;
  return false;
}

bool UIButton::IsOver() {
  // getting button and mouse position
  m_position = GetOwner()->GetPosition();
  int rendererWidth = GetOwner()->GetWidth();
  int rendererHeight = GetOwner()->GetHeight();
  std::pair<int, int> mousePos = InputSystem::GetInstance()->GetMousePosition();

  // checking if mouse is over
  if (mousePos.first > m_position->m_x &&
      mousePos.first < m_position->m_x + rendererWidth &&
      mousePos.second > m_position->m_y &&
      mousePos.second < m_position->m_y + rendererHeight)
    return true;
  return false;
}
