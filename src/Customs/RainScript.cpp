#include "Customs/RainScript.h"
#include "Globals/EngineGlobals.h"

RainScript::RainScript(GameObject *owner) : Script(owner) {}
void RainScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  GetOwner()->SetZoomProportion(Vector(0,0));
  play=0;


}
void RainScript::CreateAnimations(){

  auto rainImage = new Image("assets/chuva.png",0,0,3410, 256);

  auto rainAnimation= new Animation(GetOwner(),rainImage );
  for (int i = 0; i < 10; i++)
    rainAnimation->AddFrame(new Frame(i * 341,0, 341, 256));

     // animator
      auto weatherAnimator = new Animator(GetOwner());
      weatherAnimator->AddAnimation("rainAnimation", rainAnimation);


}


void RainScript::ComponentUpdate() {


printf("x = %f\n",position->m_x);
printf("y = %f\n",position->m_y);
printf("width = %d\n" ,GetOwner()->GetWidth());
printf("heith = %d\n",GetOwner()->GetHeight());
printf("play %d\n\n",play);

if (input->GetKeyDown(INPUT_R) && play==0) {
      play=1;
    }
else if(input->GetKeyDown(INPUT_R) && play==1){
 play=0;
 animator->StopAllAnimations();
}

}
void RainScript::FixedComponentUpdate() {

  if(play==1){

        position->m_x=0;
        position->m_y=0;
        animator->PlayAnimation("rainAnimation");

  }
}
