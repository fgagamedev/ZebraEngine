#include "Customs/FirstBossScript.h"

FirstBossScript::FirstBossScript(GameObject *owner) : Script(owner) {}

void FirstBossScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
  if(map) GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,map->originalHeight/GetOwner()->originalHeight));

}
void FirstBossScript::CreateAnimations(){

  auto firstBossImage = new Image("assets/boss1.png",0,0,2048, 372);
  auto firstBossJumpImage = new Image("assets/boss1_jump.png",0,0,1180, 406);


  auto firstBossAnimation= new Animation(GetOwner(),firstBossImage );
  for (int i = 0; i < 8; i++)
    firstBossAnimation->AddFrame(new Frame(i * 256,0, 256, 372));


  auto firstBossJumpAnimation= new Animation(GetOwner(),firstBossJumpImage );
  for (int i = 0; i < 5; i++)
    firstBossJumpAnimation->AddFrame(new Frame(i * 236,0, 236, 406));



  // animator
  auto firstBossAnimator = new Animator(GetOwner());
      
      firstBossAnimator->AddAnimation("firstBossAnimation", firstBossAnimation);
      firstBossAnimator->AddAnimation("firstBossJumpAnimation", firstBossJumpAnimation);


}


void FirstBossScript::ComponentUpdate() {
    
  animator->PlayAnimation("firstBossAnimation");
    
  //animator->PlayAnimation("firstBossJumpAnimation");
    

}
void FirstBossScript::FixedComponentUpdate() {

  
}
