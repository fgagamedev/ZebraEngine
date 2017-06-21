#include "Customs/FirstBossScript.h"

FirstBossScript::FirstBossScript(GameObject *owner) : Script(owner) {}

void FirstBossScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  GetOwner()->SetZoomProportion(Vector(18,13));

}
void FirstBossScript::CreateAnimations(){

 auto firstBossImage = new Image("assets/boss1.png",0,0,2048, 372);

  auto firstBossAnimation= new Animation(GetOwner(),firstBossImage );
  for (int i = 0; i < 8; i++)
    firstBossAnimation->AddFrame(new Frame(i * 256,0, 256, 372));



     // animator
      auto firstBossAnimator = new Animator(GetOwner());
      firstBossAnimator->AddAnimation("firstBossAnimation", firstBossAnimation);


}


void FirstBossScript::ComponentUpdate() {
animator->PlayAnimation("firstBossAnimation");

}
void FirstBossScript::FixedComponentUpdate() {


}
