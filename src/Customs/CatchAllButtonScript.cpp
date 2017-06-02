#include "Customs/CatchAllButtonScript.h"

CatchAllButtonScript::CatchAllButtonScript(GameObject *owner) : Script(owner) {}

void CatchAllButtonScript::Start() {
  m_uiButton = (UIButton *)GetOwner()->GetComponent("UIButton");
  m_checkbox = SceneManager::GetInstance()->GetScene("Main")->GetGameObject(
      "CatchAll_CB");
}

void CatchAllButtonScript::ComponentUpdate() {
  if (m_uiButton->IsClicked())
    MenuController::GetInstance()->SelectGamemode(0x02);
  if (MenuController::GetInstance()->GetGamemode() & 0x02)
    m_checkbox->active = true;
  else
    m_checkbox->active = false;
}
