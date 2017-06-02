#include "Customs/QuitButtonScript.h"

QuitButtonScript::QuitButtonScript(GameObject *owner) : Script(owner) {}

void QuitButtonScript::Start() {
  buttonComp = (UIButton *)GetOwner()->GetComponent("UIButton");
}

void QuitButtonScript::ComponentUpdate() {
  if (buttonComp->IsOver()) {
    GetOwner()->SetSize(240, 120);
  } else {
    GetOwner()->SetSize(200, 100);
  }

  if (buttonComp->IsClicked()) {
    SDLSystem::GetInstance()->SetRunning(false);
  }
}
