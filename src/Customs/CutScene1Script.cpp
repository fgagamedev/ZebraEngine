#include "Customs/CutScene1Script.h"
#include "Globals/EngineGlobals.h"

CutScene1Script::CutScene1Script(GameObject *owner) : Script(owner) {}
void CutScene1Script::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  gamecontroller = input->GetGameController(0);
  GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    if(map) GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,map->originalHeight/GetOwner()->originalHeight));

}
void CutScene1Script::CreateAnimations(){

  auto centrallightSprite = new Image("assets/cut1.png", 0, 0,1705, 255);
  auto centrallightAnimation = new Animation(GetOwner(), centrallightSprite);
  centrallightAnimation->AddFrame(new Frame(0, 0, 341, 255));

  auto centrallightAnimator = new Animator(GetOwner());
  centrallightAnimation->SetFramesPerSecond(9);
  centrallightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION", centrallightAnimation);


}


void CutScene1Script::ComponentUpdate() {

if(!animator->IsPlaying("CENTRAL LIGHT ANIMATION") && active)
animator->PlayAnimation("CENTRAL LIGHT ANIMATION");

    if(animator->IsPlaying("CENTRAL LIGHT ANIMATION")){
    animator->PlayAnimation("CENTRAL LIGHT ANIMATION");
    }
}
void CutScene1Script::FixedComponentUpdate() {

}
