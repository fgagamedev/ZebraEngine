#include "Customs/EndScene2.hpp"
#include "Customs/MenuAnimationScript.hpp"
EndScene2::EndScene2() {}

void EndScene2::OnActivation() {
  m_width_middle = EngineGlobals::screen_width / 2;
  m_height_middle = EngineGlobals::screen_height / 2;

  CreateQuitButton();
  CreateAnimation();

}

void EndScene2::OnDeactivation() {}

void EndScene2::OnShown() {}

void EndScene2::OnHidden() {}




void EndScene2::CreateAnimation(){

    auto BackgroundAnimation = new GameObject("ToBeAnimation", new Vector(0 ,0),1024,800,0);
    auto gameOverScript = new GameOverScript(BackgroundAnimation);
    AddGameObject(BackgroundAnimation);
}

void EndScene2::CreateQuitButton() {
  int xMiddle = EngineGlobals::screen_width / 2 - 100;

  auto quit = new GameObject("Quit", new Vector(xMiddle, 500), 200, 100,0);

  auto quitText = new UIText(quit, "Quit", "assets/Fonts/mini-pixel-7/mini-pixel-7.ttf",
                             200, 255, 255, 255, 150, 1);

  auto quitButton = new UIButton(quit);

  auto quitSound = new UISound(quit, "playSound", "assets/Audio/Button/MusicButton1.wav", false, false);

  auto script = new QuitButtonScript(quit);

  AddGameObject(quit);
}
