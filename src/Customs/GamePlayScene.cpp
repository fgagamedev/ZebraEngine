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

  auto nakedMan = new GameObject("NakedMan", new Vector(xPos, yPos), 120, 120, 1);

  // renderer
  auto nakedManImage = new Image("assets/player.png", 240, 240, 120, 120);
  auto nakedManRenderer = new Renderer(nakedMan, nakedManImage);

  // circle renderer
  // auto cr = new CircleRenderer(nakedMan, Vector(32, 32), 32);

  // rect renderer
  // auto rr = new RectangleRenderer(nakedMan, Vector(0, 0), 64, 64);

  // animations
  auto nakedManSprite = new Image("assets/player.png", 0, 0, 1440, 480);

  auto walkSideAnimation = new Animation(nakedMan, nakedManSprite);
  for (int i = 0; i < 12; i++)
    walkSideAnimation->AddFrame(new Frame(i * 120, 0, 120, 120));

  auto walkUpAnimation = new Animation(nakedMan, nakedManSprite);
  for (int i = 0; i < 12; i++)
    walkUpAnimation->AddFrame(new Frame(i * 120, 360, 120, 120));

  auto walkDownAnimation = new Animation(nakedMan, nakedManSprite);
  for (int i = 0; i < 12; i++)
    walkDownAnimation->AddFrame(new Frame(i * 120, 240, 120, 120));

  // animator
  auto nakedManAnimator = new Animator(nakedMan);
  nakedManAnimator->AddAnimation("Walk Side", walkSideAnimation);
  nakedManAnimator->AddAnimation("Walk Up", walkUpAnimation);
  nakedManAnimator->AddAnimation("Walk Down", walkDownAnimation);

  // script
  auto nakedManScript = new NakedManScript(nakedMan);

  // rigidbody
  // auto nakedManRB = new Rigidbody(nakedMan);

  AddGameObject(nakedMan);
}

void GamePlayScene::CreateMap() {
  auto map = new GameObject("Map", new Vector(-3300 ,-2650),7623, 5717);

  // Renderer
  auto mapImage = new Image("assets/world.png", 0, 0, 2000, 1498);
  auto mapRenderer = new Renderer(map, mapImage);

  // Script
  auto mapScript = new MapScript(map);

  AddGameObject(map);
}
