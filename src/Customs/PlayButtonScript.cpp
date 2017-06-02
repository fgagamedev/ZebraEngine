#include "Customs/PlayButtonScript.h"

PlayButtonScript::PlayButtonScript(GameObject *owner) : Script(owner) {}

void PlayButtonScript::Start() {
  buttonComponent = (UIButton *)GetOwner()->GetComponent("UIButton");
}

void PlayButtonScript::ComponentUpdate() {
  if (buttonComponent->IsOver()) {
    GetOwner()->SetSize(240, 120);
  } else {
    GetOwner()->SetSize(200, 100);
  }

  if (buttonComponent->IsClicked()) {
    SceneManager::GetInstance()->SetCurrentScene("Gameplay");
  }
}
