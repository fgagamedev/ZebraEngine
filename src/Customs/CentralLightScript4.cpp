#include "Customs/CentralLightScript4.hpp"
#include "Globals/EngineGlobals.hpp"

CentralLightScript4::CentralLightScript4(GameObject *owner) : Script(owner) {}
void CentralLightScript4::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  gamecontroller = input->GetGameController(0);
  GetOwner()->SetZoomProportion(Vector(0,0));
    auto map = SceneManager::GetInstance()->GetScene("Gameplay")->GetGameObject("Map");
    if(map) GetOwner()->SetZoomProportion(Vector(map->originalWidth/GetOwner()->originalWidth,map->originalHeight/GetOwner()->originalHeight));

}
void CentralLightScript4::CreateAnimations(){

  auto centrallightSprite = new Image("assets/centro2.png", 0, 0,832, 64);
  auto centrallightAnimation = new Animation(GetOwner(), centrallightSprite);
  centrallightAnimation->AddFrame(new Frame(0, 0, 64, 64));

  auto centrallightAnimator = new Animator(GetOwner());
  centrallightAnimation->SetFramesPerSecond(9);
  centrallightAnimator->AddAnimation("CENTRAL LIGHT ANIMATION", centrallightAnimation);


}


void CentralLightScript4::ComponentUpdate() {

if(!animator->IsPlaying("CENTRAL LIGHT ANIMATION") && active)
animator->PlayAnimation("CENTRAL LIGHT ANIMATION");

}
void CentralLightScript4::FixedComponentUpdate() {

}
