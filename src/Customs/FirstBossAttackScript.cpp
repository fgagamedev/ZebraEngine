#include "Customs/FirstBossAttackScript.h"

FirstBossAttackScript::FirstBossAttackScript(GameObject *owner) : Script(owner) {}

void FirstBossAttackScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  GetOwner()->SetZoomProportion(Vector(18,13));

}
void FirstBossAttackScript::CreateAnimations(){

 auto firstBossAttackImage = new Image("assets/boss1_Attack.png",0,0,512, 295);

  auto firstBossAttackAnimation= new Animation(GetOwner(),firstBossAttackImage );
  for (int i = 0; i < 12; i++){
    
      firstBossAttackAnimation->AddFrame(new Frame(i * 40, 0, 39, 147));
    
    


  }
     // animator
      auto firstBossAttackAnimator = new Animator(GetOwner());
      firstBossAttackAnimator->AddAnimation("firstBossAttackAnimation", firstBossAttackAnimation);
  


}


void FirstBossAttackScript::ComponentUpdate() {
  animator->PlayAnimation("firstBossAttackAnimation");

}
void FirstBossAttackScript::FixedComponentUpdate() {


}
