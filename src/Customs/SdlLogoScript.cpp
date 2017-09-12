#include "Customs/SdlLogoScript.hpp"
#include "Globals/EngineGlobals.hpp"

SdlLogoScript::SdlLogoScript(GameObject *owner) : Script(owner) {}
void SdlLogoScript::Start() {

  CreateAnimations();
  position = GetOwner()->GetPosition();
  animator = (Animator *)GetOwner()->GetComponent("Animator");
  input = InputSystem::GetInstance();
  GetOwner()->SetZoomProportion(Vector(0,0));

}
void SdlLogoScript::CreateAnimations(){

  auto sdl_LogoSprite = new Image("assets/introsdl.png", 0, 0, 5115, 512);
   auto sdlAnimation = new Animation(GetOwner(), sdl_LogoSprite);
   for (int i = 0; i < 15; i++)
    sdlAnimation->AddFrame(new Frame(i * 341, 0, 341, 256));
      for (int i = 0; i < 15; i++)
        sdlAnimation->AddFrame(new Frame(i * 341, 256, 341, 256));

    auto sdlAnimator = new Animator(GetOwner());
    sdlAnimation->SetFramesPerSecond(9);
   sdlAnimator->AddAnimation("SDL ANIMATION", sdlAnimation);


}


void SdlLogoScript::ComponentUpdate() {


}
void SdlLogoScript::FixedComponentUpdate() {

time.Update(1);


if(time.GetTime()>=130){
animator->PlayAnimation("SDL ANIMATION");
}
if(time.GetTime()>=230){
animator->StopAllAnimations();
}

}
