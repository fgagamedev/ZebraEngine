#include "Customs/BulletCounterScript.h"
#include "Globals/EngineGlobals.h"

BulletCounterScript::BulletCounterScript(GameObject *owner) : Script(owner) {}
void BulletCounterScript::Start() {

 
  position = GetOwner()->GetPosition();
  GetOwner()->SetZoomProportion(Vector(0,0));

}



void BulletCounterScript::ComponentUpdate() {

  

  auto nakedManScript = (NakedManScript*)SceneManager::GetInstance() 
                          ->GetCurrentScene()
                          ->GetGameObject("NakedMan")
                          ->GetComponent("NakedManScript");
  
  m_numberBullet = nakedManScript->bulletNumber;

  
  auto var = (UIText *)GetOwner()->GetComponent("UIText");              
  var->SetText(std::to_string(m_numberBullet));
}
void BulletCounterScript::FixedComponentUpdate() {
  position->m_x=900;
  position->m_y=700;

}
