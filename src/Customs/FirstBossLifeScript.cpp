#include "Customs/FirstBossLifeScript.h"
#include "Globals/EngineGlobals.h"

FirstBossLifeScript::FirstBossLifeScript(GameObject *owner) : Script(owner) {}
void FirstBossLifeScript::Start() {

 
  position = GetOwner()->GetPosition();
  GetOwner()->SetZoomProportion(Vector(0,0));

}



void FirstBossLifeScript::ComponentUpdate() {

  
/*
  auto nakedManScript = (NakedManScript*)SceneManager::GetInstance() 
                          ->GetCurrentScene()
                          ->GetGameObject("NakedMan")
                          ->GetComponent("NakedManScript");
  
  m_numberBullet = nakedManScript->bulletNumber;

  
  auto var = (UIText *)GetOwner()->GetComponent("UIText");              
  var->SetText(std::to_string(m_numberBullet));
  */
  auto firstBossLifeRenderer = (RectangleRenderer*)GetOwner()->GetComponent("RectangleRenderer");
  int actualLife = firstBossLifeRenderer->GetWidth();
  //cout << actualLife << endl;
  if(hit && actualLife > 0){
    cout << "hit" << endl;
    

    
    cout << actualLife << endl;
    firstBossLifeRenderer->SetWidth(actualLife - 1);
    hit = false;
  }
  if(actualLife <= 0){
    FirstBossController::GetInstance()->ActivateCreditsAnimation();
    FirstBossController::GetInstance()->DeactivateLifeBars();
  }
}
void FirstBossLifeScript::FixedComponentUpdate() {
  position->m_x=650;
  position->m_y=10;

}
