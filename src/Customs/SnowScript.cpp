#include "Customs/SnowScript.h"

SnowScript::SnowScript(GameObject *owner) : Script(owner) {}
void SnowScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
 GetOwner()->SetZoomProportion(Vector(0,0));


}
void SnowScript::CreateAnimations(){

    auto snowImage = new Image("assets/neve.png",0,0,6820, 256);

    auto snowAnimation= new Animation(GetOwner(),snowImage );
    for (int i = 0; i < 20; i++)
      snowAnimation->AddFrame(new Frame(i * 341,0, 341, 256));


     // animator
      auto weatherAnimator = new Animator(GetOwner());
      weatherAnimator->AddAnimation("snowAnimation", snowAnimation);


}


void SnowScript::ComponentUpdate() {

 if(play==1)
     animator->PlayAnimation("snowAnimation");

    if(input->GetKeyDown(INPUT_T) && play==0){
   // animator->StopAllAnimations();
      AudioController::GetInstance()->PlayAudio("snowSound", -1);
    play=1;
    }
    else if(input->GetKeyDown(INPUT_T) && play==1){
    play=0;
    AudioController::GetInstance()->StopAudio("snowSound");
    animator->StopAllAnimations();
    }

}
void SnowScript::FixedComponentUpdate() {

  position->m_x=0;
  position->m_y=0;

}
