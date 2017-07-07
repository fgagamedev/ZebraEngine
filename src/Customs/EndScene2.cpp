#include "Customs/EndScene2.h"
#include "Customs/MenuAnimationScript.h"
EndScene2::EndScene2() {}

void EndScene2::OnActivation() {
  m_width_middle = EngineGlobals::screen_width / 2;
  m_height_middle = EngineGlobals::screen_height / 2;

  CreateAnimation();

}

void EndScene2::OnDeactivation() {}

void EndScene2::OnShown() {}

void EndScene2::OnHidden() {}




void EndScene2::CreateAnimation(){

    auto BackgroundAnimation = new GameObject("ToBeAnimation", new Vector(0 ,0),1024,800,0);
    //auto backgroundAnimationScript = new MenuAnimationScript(BackgroundAnimation);
    AddGameObject(BackgroundAnimation);
}
