#include "Customs/PlayButtonScript.hpp"
#include "Customs/AudioController.hpp"

PlayButtonScript::PlayButtonScript(GameObject *owner) : Script(owner) {}

void PlayButtonScript::Start() {
  m_uiButton = (UIButton *)GetOwner()->GetComponent("UIButton");
}

void PlayButtonScript::ComponentUpdate() {

	auto textButton = (UIText *)GetOwner()->GetComponent("UIText");
  auto soundButton = (UISound *)GetOwner()->GetComponent("UISound");
  auto menuSound = (UISound *)SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("Music")->GetComponent("UISound");
  if (m_uiButton->IsClicked()) {
    soundButton->Play(0, -1);
    menuSound->Stop();
    AudioController::GetInstance()->PlayAudio("mainSound", -1);
    SceneManager::GetInstance()->SetCurrentScene("Gameplay");
  }

  if (m_uiButton->IsOver()) {
    
  	textButton->SetColor(160,160,160, 255);
    

  }else{
  	
  	textButton->SetColor(255,255,255, 255);
  }
}
