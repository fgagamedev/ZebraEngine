#include "Customs/MissileButtonScript.hpp"

MissileButtonScript::MissileButtonScript(GameObject *owner) : Script(owner) {}

void MissileButtonScript::Start() {
  m_uiButton = (UIButton *)GetOwner()->GetComponent("UIButton");
  m_checkbox = SceneManager::GetInstance()->GetScene("Main")->GetGameObject(
      "Missile_CB");
}

void MissileButtonScript::ComponentUpdate() {
  if (m_uiButton->IsClicked())
    MenuController::GetInstance()->SelectGamemode(0x01);
  if (MenuController::GetInstance()->GetGamemode() & 0x01)
    m_checkbox->active = true;
  else
    m_checkbox->active = false;
}
