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

  auto logo = new GameObject("Logo", new Vector(-30,0), 1024, 800,1);

  auto logoImage = new Image("assets/logo2.png", 0, 0, 311, 256);
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

/*void MainScene::CreatePlayButton() {
  auto playButton = new GameObject(
      "PlayButton", new Vector(m_width_middle - (190 * 1.4 / 2), 100),
      190 * 1.4, 45 * 1.4, 1);
  auto playButtonImage =
      new Image("assets/UIpack/Spritesheet/greenSheet.png", 0, 94, 190, 45);
  auto playButtonRenderer = new Renderer(playButton, playButtonImage);
  auto playButtonText =
      new UIText(playButton, "Play", "assets/UIpack/Font/kenvector_future.ttf",
                 120, 255, 255, 255, 255, 1);
  auto vec = Vector(10, 0);
  playButtonText->SetOffset(vec);
  auto playButtonUIB = new UIButton(playButton);
  auto playButtonScript = new PlayButtonScript(playButton);

  AddGameObject(playButton);
}

void MainScene::CreateQuitButton() {
  auto quitButton = new GameObject(
      "QuitButton",
      new Vector(m_width_middle - (190 * 1.4 / 2), 100 + (45 * 1.4)), 190 * 1.4,
      45 * 1.4, 1);
  auto quitButtonImage =
      new Image("assets/UIpack/Spritesheet/redSheet.png", 0, 94, 190, 45);
  auto quitButtonRenderer = new Renderer(quitButton, quitButtonImage);
  auto quitButtonText =
      new UIText(quitButton, "Quit", "assets/UIpack/Font/kenvector_future.ttf",
                 120, 255, 255, 255, 255, 1);
  auto vec = Vector(10, 0);
  quitButtonText->SetOffset(vec);
  auto quitButtonUIB = new UIButton(quitButton);
  auto quitButtonScript = new QuitButtonScript(quitButton);

  AddGameObject(quitButton);
}

void MainScene::CreateBackground() {
  auto background = new GameObject("Background", new Vector(0, 0),
                                   m_width_middle * 2, m_height_middle * 2, 0);
  auto backgroundRectangle = new RectangleRenderer(
      background, Vector(0, 0), m_width_middle * 2, m_height_middle * 2);
  backgroundRectangle->SetColor(20, 20, 20, 255);
  AddGameObject(background);
}

void MainScene::CreateGamemodes() {
  // instruction text
  auto instruction =
      new GameObject("InstructionText",
                     new Vector(m_width_middle - 100 - 5, 250), 400, 100, 1);
  auto instructionUIText = new UIText(instruction, "Choose a gamemode",
                                      "assets/UIpack/Font/kenvector_future.ttf",
                                      200, 255, 255, 255, 255, 1);
  auto vecOff = Vector(-100, 0);
  instructionUIText->SetOffset(vecOff);
  AddGameObject(instruction);

  // catch all
  auto catchAllButton = new GameObject(
      "CatchAllButton", new Vector(m_width_middle - 100 - 5, 340), 100, 100, 1);
  auto catchAllImage =
      new Image("assets/UIpack/Spritesheet/greySheet.png", 190, 98, 100, 100);
  auto catchAllRenderer = new Renderer(catchAllButton, catchAllImage);
  auto catchAllText = new UIText(catchAllButton, "Catch All",
                                 "assets/UIpack/Font/kenvector_future_thin.ttf",
                                 100, 0, 0, 0, 255, 1);
  auto catchAllScript = new CatchAllButtonScript(catchAllButton);
  auto catchAllUIB = new UIButton(catchAllButton);
  auto vec = Vector(2, 0);
  catchAllText->SetOffset(vec);
  AddGameObject(catchAllButton);

  auto catchAll_CB =
      new GameObject("CatchAll_CB", catchAllButton->GetPosition(), 38, 36, 3);
  auto checkBoxImage =
      new Image("assets/UIpack/Spritesheet/greenSheet.png", 380, 0, 38, 36);
  auto catchAll_CBRenderer = new Renderer(catchAll_CB, checkBoxImage);
  AddGameObject(catchAll_CB);

  // missile
  auto missileButton = new GameObject(
      "MissileButton", new Vector(m_width_middle + 5, 340), 100, 100, 1);
  auto missileImage =
      new Image("assets/UIpack/Spritesheet/greySheet.png", 190, 98, 100, 100);
  auto missileRenderer = new Renderer(missileButton, catchAllImage);
  auto missileText = new UIText(missileButton, "Missile",
                                "assets/UIpack/Font/kenvector_future_thin.ttf",
                                100, 0, 0, 0, 255, 1);
  auto missileUIB = new UIButton(missileButton);
  auto missileScript = new MissileButtonScript(missileButton);
  vec = Vector(2, 0);
  missileText->SetOffset(vec);
  AddGameObject(missileButton);

  auto missile_CB =
      new GameObject("Missile_CB", missileButton->GetPosition(), 38, 36, 3);
  auto missile_CBRenderer = new Renderer(missile_CB, checkBoxImage);
  missile_CBRenderer->active = true;
  AddGameObject(missile_CB);
}
*/

void MainScene::CreateMusic(){

  auto music = new GameObject("Music", new Vector(200, 200), 200, 100);

  auto themeMusic = new UISound(music, "Music", "assets/Audio/Menu/musicMenu1.wav", false, true);

  AddGameObject(music);

}
