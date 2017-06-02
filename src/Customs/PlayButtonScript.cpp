#include "Customs/PlayButtonScript.h"

PlayButtonScript::PlayButtonScript(GameObject *owner) : Script(owner) {}

void PlayButtonScript::Start() {
  m_uiButton = (UIButton *)GetOwner()->GetComponent("UIButton");
}

void PlayButtonScript::ComponentUpdate() {
  if (m_uiButton->IsClicked()) {
    SceneManager::GetInstance()->SetCurrentScene("Gameplay");
  }
}
