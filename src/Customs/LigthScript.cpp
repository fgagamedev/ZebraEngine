#include "Customs/LightScript.h"
#include "Globals/EngineGlobals.h"

LightScript::LightScript(GameObject *owner) : Script(owner) {}
void LightScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  GetOwner()->SetZoomProportion(Vector(0,0));

}
void LightScript::CreateAnimations(){

  auto lightImage = new Image("assets/luz.png",0,0,682, 512);

  auto  lightAnimation= new Animation(GetOwner(),lightImage );
        lightAnimation->AddFrame(new Frame(0,0, 682, 512));

     // animator
      auto lightAnimator = new Animator(GetOwner());
      lightAnimator->AddAnimation("lightAnimation", lightAnimation);



}


void LightScript::ComponentUpdate() {

    if(play==1)
     animator->PlayAnimation("lightAnimation");

    if(input->GetKeyDown(INPUT_Y) && play==0){
    play=1;
    }
    else if(input->GetKeyDown(INPUT_Y) && play==1)
    play=0;
    }
void LightScript::FixedComponentUpdate() {
        position->m_x  =  SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("NakedMan")->GetPosition()->m_x -  GetOwner()->GetWidth()/2 + 40;
        position->m_y  =  SceneManager::GetInstance()->GetCurrentScene()->GetGameObject("NakedMan")->GetPosition()->m_y -  GetOwner()->GetHeight()/2 + 40;
}
