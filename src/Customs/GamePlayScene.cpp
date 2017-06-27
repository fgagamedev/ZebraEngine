#include "Customs/GamePlayScene.h"
#include "Globals/EngineGlobals.h"

void GamePlayScene::OnActivation() {
  CreateMap();//This must be the first function to be called
  CreateNakedMan();
CreateFirstBoss();
  CreateFirstBossAttack();
  CreateLight();
  CreateRain();
  CreateSnow();
  CreateThunder();
  CreatePlayerAttack();
  CreateAmmoCounter();

}

void GamePlayScene::OnDeactivation() {}

void GamePlayScene::OnShown() {}

void GamePlayScene::OnHidden() {}

void GamePlayScene::CreateMap() {
  //Original resolution is 2048/2048
  //6144,6144 = 3x
  auto map = new GameObject("Map", new Vector(-5250 ,-5000),10500,10500);
  // Renderer
  auto mapImage = new Image("assets/world.png", 0, 0, 3500, 3500);
  auto mapRenderer = new Renderer(map, mapImage);
  // Script
  auto mapScript = new MapScript(map);
  AddGameObject(map);

}

void GamePlayScene::CreateNakedMan() {

  int xPos, yPos;
  xPos =EngineGlobals::screen_width / 2 - 96/2;
  yPos =EngineGlobals::screen_height / 2 - 96/2;
  auto nakedMan = new GameObject("NakedMan", new Vector(xPos,yPos),96 , 96, 1);
  // Script
  auto nakedManScript = new NakedManScript(nakedMan);
  AddGameObject(nakedMan);
}

void GamePlayScene::CreateFirstBoss() {

 auto FirstBossCentralEffect = new GameObject("FirstBossCentralEffect", new Vector(0,0),211.86,211.86, 1);
 auto firstBossCentralEffectScript = new  FirstBossCentralEffectScript(FirstBossCentralEffect);
 AddGameObject(FirstBossCentralEffect);

  auto firstBoss = new GameObject("FirstBoss", new Vector(-4700,-1600),690,930, 2);
  // Script
  auto firstBossScript = new  FirstBossScript(firstBoss);
  AddGameObject(firstBoss);

}

void GamePlayScene::CreateFirstBossAttack() {

  auto firstBossAttack = new GameObject("FirstBossAttack", new Vector(-4700,-1700),39,147, 1);
  // Script
  auto firstBossAttackScript = new  FirstBossAttackScript(firstBossAttack);
  AddGameObject(firstBossAttack);

}

void GamePlayScene::CreatePlayerAttack() {

  //Creating Bullets
  for (int i = 0; i < 15; i++) {
    std::string bulletName = "Bullet" + std::to_string(i + 1);
    auto bullet = new GameObject(bulletName, new Vector(0, 0), 15, 15, 2);
    //bullet->SetTag("Bullet");

    auto bulletScript = new  PlayerAttackScript(bullet);

    //auto playerCollider = new RectangleCollider(bullet, Vector(0, 0), 40, 60, 0);
 

    //MissileController::GetInstance()->AddPlayer(bullet);
    AddGameObject(bullet);
    auto gameObjectBullet = (GameObject*)SceneManager::GetInstance()
                   ->GetScene("Gameplay")
                   ->GetGameObject(bulletName);
    gameObjectBullet->active = false;
                   
  }

}

void GamePlayScene::CreateRain() {

  auto rain = new GameObject("Rain", new Vector(0,0),1024,800,1);
  auto rainScript = new RainScript(rain);
  AddGameObject(rain);

}


void GamePlayScene::CreateThunder() {

  auto thunder = new GameObject("Rain", new Vector(200,0),113,267,1);
  auto thunderScript = new ThunderScript(thunder);
  AddGameObject(thunder);

}


void GamePlayScene::CreateSnow(){

  auto snow = new GameObject("Snow", new Vector(0,0),1024,800,1);
  auto snowScript = new SnowScript(snow);
  AddGameObject(snow);

}
void GamePlayScene::CreateLight() {

  auto light = new GameObject("Light", new Vector(0,0),2*1024,2*800,1);
 //auto lightImage = new Image("assets/luz.png",0,0,682, 512);
 //auto mapRenderer = new Renderer(light, lightImage);
  auto lightScript = new LightScript(light);
  AddGameObject(light);

}

void GamePlayScene::CreateAmmoCounter() {

  auto ammo = new GameObject("Ammo", new Vector(2,2),200,200,3);
  auto messengerText = new UIText(ammo, "15", "assets/UIpack/Font/kenvector_future_thin.ttf",
                 100, 255, 255, 255, 255, 1);
  //auto lightScript = new LightScript(light);
  AddGameObject(ammo);

}