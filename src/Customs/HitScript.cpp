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

  auto firstHitAnimation= new Animation(GetOwner(),hitImage );
  firstHitAnimation->AddFrame(new Frame(0,0, 1024, 1024));

  // animator
  auto hitAnimator = new Animator(GetOwner());
  hitAnimator->AddAnimation("firstHitAnimation",firstHitAnimation);

  // hit 2

  // hit 3

  // hit 4

  


}


void HitScript::ComponentUpdate() {

    if(hit){

      switch(hitLevel){

        case 0: //No hit
          //animator->StopAllAnimations();
          hit = false;
          break;
        case 1://Hit 1
          //hitAnimator->PlayAnimation("firstHitAnimation");
            
          break;
        case 2:// Hit 2
          break;
        case 3:// Hit 3
          break;

      }


    }

      
    
      

    if(input->GetKeyDown(INPUT_I)){
      hit = true;
    }

}

void HitScript::FixedComponentUpdate() {
  position->m_x=0;
  position->m_y=0;


}
