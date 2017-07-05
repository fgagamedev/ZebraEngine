#include "Customs/MenuAnimationScript.h"
#include <stdio.h>


MenuAnimationScript::MenuAnimationScript(GameObject *owner) : Script(owner) {}

void MenuAnimationScript::Start() {
 CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");



}


void MenuAnimationScript::CreateAnimations(){

  // animator
  auto MenuAnimationScriptAnimator = new Animator(GetOwner());

 auto mainSprite = new Image("assets/menu_animation.png", 0, 0, 5456, 256);


 auto mainAnimation = new Animation(GetOwner(), mainSprite);
  for (int i = 0; i <16; i++)
    mainAnimation->AddFrame(new Frame(i * 341, 0, 341, 256));


   mainAnimation->SetFramesPerSecond(10);



  MenuAnimationScriptAnimator->AddAnimation("mainAnimation", mainAnimation);

}

void MenuAnimationScript::ComponentUpdate() {

if(!animator->IsPlaying("mainAnimation")){

animator->PlayAnimation("mainAnimation");
}


}

void MenuAnimationScript::FixedComponentUpdate() {



}

