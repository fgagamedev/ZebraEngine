#include "Customs/MainScene.h"
#include "Customs/MenuAnimationScript.h"
MainScene::MainScene() {}

void MainScene::OnActivation() {
  m_width_middle = EngineGlobals::screen_width / 2;
  m_height_middle = EngineGlobals::screen_height / 2;
  CreateLogo();
  CreatePlayButton();
  CreateQuitButton();
  CreateMusic();
  CreateAnimation();
  //CreateBackground();
  //CreateGamemodes();

}

void MainScene::OnDeactivation() {}

void MainScene::OnShown() {}

void MainScene::OnHidden() {}


void MainScene::CreateLogo() {
  int xMiddle = EngineGlobals::screen_width / 2 - 240;

  auto logo = new GameObject("Logo", new Vector(xMiddle, 100), 500, 325,1);

  auto logoImage = new Image("assets/logo.png", 0, 0, 2048, 2048);
  auto logoRenderer = new Renderer(logo, logoImage);

  AddGameObject(logo);
}

void MainScene::CreatePlayButton() {
  int xMiddle = EngineGlobals::screen_width / 2 - 100;

  auto play = new GameObject("Play", new Vector(xMiddle, 400), 200, 100,1);

  auto playText = new UIText(play, "Play", "assets/Fonts/mini-pixel-7/mini-pixel-7.ttf",
                             200, 255, 255, 255, 150, 1);

  auto playButton = new UIButton(play);

  auto playSound = new UISound(play, "playSound", "assets/Audio/Button/MusicButton1.wav", false, false);

  auto script = new PlayButtonScript(play);

  AddGameObject(play);
}

void MainScene::CreateQuitButton() {
  int xMiddle = EngineGlobals::screen_width / 2 - 100;

  auto quit = new GameObject("Quit", new Vector(xMiddle, 500), 200, 100,1);

  auto quitText = new UIText(quit, "Quit", "assets/Fonts/mini-pixel-7/mini-pixel-7.ttf",
                             200, 255, 255, 255, 150, 1);

  auto quitButton = new UIButton(quit);

  auto quitSound = new UISound(quit, "playSound", "assets/Audio/Button/MusicButton1.wav", false, false);

  auto script = new QuitButtonScript(quit);

  AddGameObject(quit);
}
void MainScene::CreateAnimation(){

auto BackgroundAnimation = new GameObject("BackgroundAnimation", new Vector(0 ,0),1024,800,0);
 auto backgroundAnimationScript = new MenuAnimationScript(BackgroundAnimation);
  AddGameObject(BackgroundAnimation);
}


void MainScene::CreateMusic(){

  auto music = new GameObject("Music", new Vector(200, 200), 200, 100);

  auto themeMusic = new UISound(music, "Music", "assets/Audio/Menu/Menu.ogg", false, true);

  AddGameObject(music);

}
