#include "Customs/QuitButtonScript.h"

QuitButtonScript::QuitButtonScript(GameObject *owner) : Script(owner) {}

void QuitButtonScript::Start() {
  m_uiButton = (UIButton *)GetOwner()->GetComponent("UIButton");
}

void QuitButtonScript::ComponentUpdate() {
  if (m_uiButton->IsClicked()) {
    SDLSystem::GetInstance()->SetRunning(false);
  }
}
