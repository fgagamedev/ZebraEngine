#include "Customs/GamePlayScene.h"

void GamePlayScene::OnActivation() {
  CreateNakedMan();
  CreateMap();
}

void GamePlayScene::OnDeactivation() {}

void GamePlayScene::OnShown() {}

void GamePlayScene::OnHidden() {}

void GamePlayScene::CreateNakedMan() {

  int xPos, yPos;
  xPos =EngineGlobals::screen_width / 2 - 120;
  yPos =EngineGlobals::screen_height / 2 - 120;

  auto nakedMan = new GameObject("NakedMan", new Vector(xPos,yPos),96 , 96, 1);
  // renderer
 // auto nakedManImage = new Image("assets/player.png", 0, 0,1664,512);
  // circle renderer
  // auto cr = new CircleRenderer(nakedMan, Vector(32, 32), 32);

  // rect renderer
  // auto rr = new RectangleRenderer(nakedMan, Vector(0, 0), 64, 64);

  // animations
  auto nakedManSprite = new Image("assets/player.png", 0, 0, 1664, 512);

  auto StopDownAnimation = new Animation(nakedMan, nakedManSprite);
    StopDownAnimation->AddFrame(new Frame(0, 256, 128, 128));

  auto StopRightAnimation = new Animation(nakedMan, nakedManSprite);
         StopRightAnimation->AddFrame(new Frame(0, 0, 128, 128));

  auto StopLeftAnimation = new Animation(nakedMan, nakedManSprite);
        StopLeftAnimation->AddFrame(new Frame(0, 128, 128, 128));

  auto StopUpAnimation = new Animation(nakedMan, nakedManSprite);
        StopUpAnimation->AddFrame(new Frame(0, 384, 128, 128));

  auto walkSideAnimation = new Animation(nakedMan, nakedManSprite);
  for (int i = 1; i < 13; i++)
    walkSideAnimation->AddFrame(new Frame(i * 128, 0, 128, 128));

  auto walkUpAnimation = new Animation(nakedMan, nakedManSprite);
  for (int i = 1; i < 13; i++)
    walkUpAnimation->AddFrame(new Frame(i * 128, 384, 128, 128));

  auto walkDownAnimation = new Animation(nakedMan, nakedManSprite);
  for (int i = 1; i < 13; i++)
    walkDownAnimation->AddFrame(new Frame(i * 128, 256, 128, 128));

  // animator
  auto nakedManAnimator = new Animator(nakedMan);

  nakedManAnimator->AddAnimation("Walk Side", walkSideAnimation);
  nakedManAnimator->AddAnimation("Walk Up", walkUpAnimation);
  nakedManAnimator->AddAnimation("Walk Down", walkDownAnimation);

 nakedManAnimator->AddAnimation("Stop Down", StopDownAnimation);
 nakedManAnimator->AddAnimation("Stop Up", StopUpAnimation);
 nakedManAnimator->AddAnimation("Stop Left", StopLeftAnimation);
 nakedManAnimator->AddAnimation("Stop Right", StopRightAnimation);
  // script
  auto nakedManScript = new NakedManScript(nakedMan);

  // rigidbody
  // auto nakedManRB = new Rigidbody(nakedMan);

  AddGameObject(nakedMan);
}

void GamePlayScene::CreateMap() {
//Original resolution is 2048/2048
//6144,6144 = 3x

  //auto map = new GameObject("Map", new Vector(-2612 ,-2900),6144,6144);
    auto map = new GameObject("Map", new Vector(-2612 ,-2900),6144,6144);

  //auto map = new GameObject("Map", new Vector(-100,0),6144,6144);

  // Renderer
  auto mapImage = new Image("assets/world.png", 0, 0, 2048, 2048);
  auto mapRenderer = new Renderer(map, mapImage);
  // Script
  auto mapScript = new MapScript(map);

  AddGameObject(map);

}
