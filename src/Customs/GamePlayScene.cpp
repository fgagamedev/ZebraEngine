#include "Customs/GamePlayScene.h"
#include "Globals/EngineGlobals.h"

void GamePlayScene::OnActivation() {
  CreateMap();//This must be the first function to be called
  CreateNakedMan();
  CreateFirstBoss();
  CreateFirstBossAttack();
  CreateFirstBossLife();
  CreateLight();
  CreateRain();
  CreateSnow();
  CreateThunder();
  CreatePlayerAttack();
  //CreateAmmoCounter();
  CreatePlayerHit();

  //FirstBossController::GetInstance()->StartBossFight();

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
  auto nakedMan = new GameObject("NakedMan", new Vector(-3200,-100),96 , 96, 1);
  // Script
  auto nakedManScript = new NakedManScript(nakedMan);
  AddGameObject(nakedMan);
  FirstBossController::GetInstance()->AddPlayer(nakedMan);
}

void GamePlayScene::CreateFirstBoss() {
  /** Boss Inside FX **/
  auto FirstBossCentralEffect = new GameObject("FirstBossCentralEffect", new Vector(0,0),211.86,211.86, 1);
  auto firstBossCentralEffectScript = new  FirstBossCentralEffectScript(FirstBossCentralEffect);
  AddGameObject(FirstBossCentralEffect);
  FirstBossController::GetInstance()->AddInsideBossFx(FirstBossCentralEffect);
  FirstBossController::GetInstance()->DeactivateInsideBossFx();

  /** Boss **/
  auto firstBoss = new GameObject("FirstBoss", new Vector(-4700,-1600),690,930, 2);

  //Tag
  firstBoss->SetTag("FirstBoss");
  
  // Script
  auto firstBossScript = new  FirstBossScript(firstBoss);
  AddGameObject(firstBoss);

  FirstBossController::GetInstance()->AddBoss(firstBoss);
  FirstBossController::GetInstance()->DeactivateBoss();
}

void GamePlayScene::CreateFirstBossAttack() {
  
  for (int i = 1; i < 5; i++) {
    std::string tentacleName = "FirstBossAttack" + std::to_string(i);
    auto firstBossAttack = new GameObject(tentacleName, new Vector(-4750, -1700), 100, 377, 2);
    //Tag
    firstBossAttack->SetTag("FirstBossAtack");

    // Script
    auto firstBossAttackScript = new  FirstBossAttackScript(firstBossAttack);
    
    AddGameObject(firstBossAttack);
    FirstBossController::GetInstance()->AddTentacle(firstBossAttack);

    //bullet->active = false;
                   
  }
}

void GamePlayScene::CreateFirstBossLife() {
  auto firstBossLife = new GameObject("FirstBossLife", new Vector(-4550, -700),350, 25, 2);
  auto lifeRectangle = new RectangleRenderer(firstBossLife, Vector(0, 0), 350, 25);
  lifeRectangle->SetColor(255, 48, 48, 255);
  //Create Script

  auto firstBossLifeScript = new  FirstBossLifeScript(firstBossLife);
  AddGameObject(firstBossLife);
}

void GamePlayScene::CreatePlayerAttack() {

  /** Creating Bullets **/
  for (int i = 1; i < 11; i++) {
    std::string bulletName = "Bullet" + std::to_string(i);
    auto bullet = new GameObject(bulletName, new Vector(100 * i, 0), 15, 15, 2);
    bullet->SetTag("Bullet");
    auto bulletScript = new  PlayerAttackScript(bullet);
    AddGameObject(bullet);
    bullet->active = false;

    //MissileController::GetInstance()->AddPlayer(bullet);
    //bullet->active = false;               
  }
  /** Bullet Counter **/
  auto bulletCounter = new GameObject("Score", new Vector(0, 0), 75 , 75, 2);
  bulletCounter->SetTag("BulletCounter");
  auto bulletText = new UIText(bulletCounter, "10", "assets/Fonts/advanced-pixel-7/advanced_pixel-7.ttf", 150, 0 , 0, 0, 0, 1);
  auto bulletCounterScript = new BulletCounterScript(bulletCounter);
  AddGameObject(bulletCounter);



}

void GamePlayScene::CreateRain() {

  auto rain = new GameObject("Rain", new Vector(0,0),1024,800,1);
  auto rainScript = new RainScript(rain);
  AddGameObject(rain);
}

void GamePlayScene::CreatePlayerHit() {

  auto hit = new GameObject("Hit", new Vector(0,0),1024,800,1);

  auto hitScript = new HitScript(hit);
  AddGameObject(hit);
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