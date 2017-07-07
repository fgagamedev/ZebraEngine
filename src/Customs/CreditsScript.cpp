#include "Customs/CreditsScript.h"
#include "Globals/EngineGlobals.h"

CreditsScript::CreditsScript(GameObject *owner) : Script(owner) {}
void CreditsScript::Start() {

 
  position = GetOwner()->GetPosition();
  GetOwner()->SetZoomProportion(Vector(0,0));

}



void CreditsScript::ComponentUpdate() {

  
}
void CreditsScript::FixedComponentUpdate() {
  position->m_x=0;
  position->m_y=0;

}
