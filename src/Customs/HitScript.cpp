#include "Customs/HitScript.h"
#include "Globals/EngineGlobals.h"

HitScript::HitScript(GameObject *owner) : Script(owner) {}
void HitScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  GetOwner()->SetZoomProportion(Vector(0,0));

}
void HitScript::CreateAnimations(){

  auto hitImage = new Image("assets/Sprites/Blood/blood4.png",0,0,1024, 1024);

  auto hitAnimation= new Animation(GetOwner(),hitImage );
  hitAnimation->AddFrame(new Frame(0,0, 1024, 1024));

  // animator
  auto hitAnimator = new Animator(GetOwner());
  hitAnimator->AddAnimation("firstHitAnimation",hitAnimation);



  


}


void HitScript::ComponentUpdate() {

    if(play==1)
      animator->PlayAnimation("firstHitAnimation");
      

    if(input->GetKeyDown(INPUT_I) && play==0){
      //animator->StopAllAnimations();
      play=1;
    }
    else if(input->GetKeyDown(INPUT_I) && play==1){
      play=0;
      animator->StopAllAnimations();
    }

}
void HitScript::FixedComponentUpdate() {
  position->m_x=0;
  position->m_y=0;


}
