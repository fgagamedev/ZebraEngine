/**
    @file GamePlayScene.cpp
    @brief Class responsible for creating and
    activating the information needed for game scenes.
    @copyright LGPL. MIT License.
*/

#include "Globals/EngineGlobals.hpp"

#include "Customs/GamePlayScene.hpp"
#include "Customs/CutScene1Script.hpp"
#include "Customs/AudioController.hpp"

/**
    @brief Responsible for creating the inputs
    needed to run the game scene that are defined further down.
*/
void GamePlayScene::OnActivation() {
    //This must be the first function to be called
    CreateMap();
    CreateCreditAnimation();
    CreateNakedMan();
    CreateFirstBoss();
    CreateFirstBossAttack();
    CreateFirstBossLife();
    CreateLight();
    CreateRain();
    CreateSnow();
    CreateThunder();
    CreatePlayerAttack();
    CreatePlayerHit();
    CreateForestActivator();
    CreateSnowActivator();
    CreateCentralLights();
    CreateCutScenes();
    FirstBossController::GetInstance()->StartBossFight();

}

void GamePlayScene::OnDeactivation() {}

void GamePlayScene::OnShown() {}

void GamePlayScene::OnHidden() {}

/**
    @brief Create the game map by adding the
    trees and correcting the screen rendering.
*/
void GamePlayScene::CreateMap() {


    //Original resolution is 2048/2048
    //6144,6144 = 3x
    auto map = new GameObject("Map", new Vector(-3500 ,-3800),8034,8034,0);
    // Renderer
    auto mapImage = new Image("assets/mapa2.png", 0, 0, 2678, 2678);
    //  auto mapImage = new Image("assets/transitavel.png", 0, 0, 2678, 2678);
    auto mapRenderer = new Renderer(map, mapImage);


    auto trees = new GameObject("Tree", new Vector(-3500 ,-3800),8034,8034,1);
    // Renderer
    auto treesImage = new Image("assets/trees.png", 0, 0, 2678, 2678);
    auto treesRenderer = new Renderer(trees, treesImage);

    // Script
    auto mapScript = new MapScript(map);



    auto bossBattleSound = new UISound(map, "bossBattleSound",
                                       "assets/Audio/Boss/heartfinal.ogg",
                                       false, false);

    AudioController::GetInstance()->AddAudio(bossBattleSound);

    auto mainSound = new UISound(map, "mainSound",
                                 "assets/Audio/florestafinal.ogg",
                                 false, false);

    AudioController::GetInstance()->AddAudio(mainSound);
    AudioController::GetInstance()->PlayAudio("mainSound", -1);

    AddGameObject(map);

    FirstBossController::GetInstance()->AddMap(map);

    AddGameObject(trees);

}

void GamePlayScene::CreateCutScenes(){

    auto scene1 = new GameObject("SCENE1", new Vector(0,0),1024,800,0);
    auto  scene1Script = new CutScene1Script(scene1);
    scene1Script->Activate();
    AddGameObject(scene1);
}

/**
    @brief Responsible for creating three forest-activating objects.
*/
void  GamePlayScene::CreateForestActivator(){
    //left
    auto forestActivator = new GameObject("FOREST ACTIVATOR",
                                          new Vector(1720, -3463), 192, 192, 1);
    auto  forestactivatorScript = new ForestActivatorScript(forestActivator);
    AddGameObject(forestActivator);
    //blue
    auto forestActivator2 = new GameObject("FOREST ACTIVATOR2",
                                           new Vector(701,-578),192,192,1);
    auto  forestactivatorScript2 = new ForestActivatorScript2(forestActivator2);
    AddGameObject(forestActivator2);
    //central
    auto forestActivator3 = new GameObject("FOREST ACTIVATOR3",
                                           new Vector(-579,-1546),192,192,1);
    auto  forestactivatorScript3 = new ForestActivatorScript3(forestActivator3);
    AddGameObject(forestActivator3);

}

/**
    @brief responsible for creating the snow activator at
    the end it sends to the class that treats the objects of the game.
*/
void GamePlayScene::CreateSnowActivator(){

    auto snowActivator = new GameObject("SNOW ACTIVATOR",
                                        new Vector(-1044,2446),192,192,1);
    auto  snowactivatorScript = new SnowActivatorScript(snowActivator);
    AddGameObject(snowActivator);

}

/**
    @brief responsible for creating four central lights at
    the end it sends to the class that treats the objects of the game.
*/
void GamePlayScene::CreateCentralLights(){

    auto centralLight1= new GameObject("CENTRAL LIGHT 1",
                                       new Vector(424,422),192,192,1);
    auto  centralLight1Script = new CentralLightScript1(centralLight1);
    AddGameObject(centralLight1);

    auto centralLight2= new GameObject("CENTRAL LIGHT 2",
                                       new Vector(309,308),192,192,1);
    auto  centralLight2Script = new CentralLightScript2(centralLight2);
    AddGameObject(centralLight2);

    auto centralLight3= new GameObject("CENTRAL LIGHT 3",
                                       new Vector(542,308),192,192,1);
    auto  centralLight3Script = new CentralLightScript3(centralLight3);
    AddGameObject(centralLight3);

    auto centralLight4= new GameObject("CENTRAL LIGHT 4",
                                       new Vector(424,197),192,192,1);
    auto  centralLight4Script = new CentralLightScript4(centralLight4);
    AddGameObject(centralLight4);

}


void GamePlayScene::CreateNakedMan() {

    int xPos, yPos;
    xPos = EngineGlobals::screen_width / 2 - 96 / 2;
    yPos = EngineGlobals::screen_height / 2 - 96 / 2;
    auto nakedMan = new GameObject("NakedMan", new Vector(xPos,yPos),96 , 96, 2);
    // Script
    auto nakedManScript = new NakedManScript(nakedMan);

    auto runSound = new UISound(nakedMan, "runSound",
                                "assets/Audio/Player/runcrushed.ogg", false,
                                false);
    AudioController::GetInstance()->AddAudio(runSound);

    AddGameObject(nakedMan);
    FirstBossController::GetInstance()->AddPlayer(nakedMan);

}

/**
    @brief Responsible for creating and defining
    the location that the first boss will be and which special
    effect he will have when he is found.
*/
void GamePlayScene::CreateFirstBoss() {
    /** Boss Inside FX **/
    auto FirstBossCentralEffect = new GameObject("FirstBossCentralEffect",
                                                 new Vector(0,0),211.86,211.86, 1);
    auto firstBossCentralEffectScript = new  FirstBossCentralEffectScript(FirstBossCentralEffect);
    AddGameObject(FirstBossCentralEffect);
    FirstBossController::GetInstance()->AddInsideBossFx(FirstBossCentralEffect);
    FirstBossController::GetInstance()->DeactivateInsideBossFx();

    /** Boss **/
    auto firstBoss = new GameObject("FirstBoss", new Vector(-3350,-1600),690,930, 2);

    //Tag
    firstBoss->SetTag("FirstBoss");

    // Script
    auto firstBossScript = new  FirstBossScript(firstBoss);
    AddGameObject(firstBoss);

    FirstBossController::GetInstance()->AddBoss(firstBoss);
    FirstBossController::GetInstance()->DeactivateBoss();
}

/**
    @brief Responsible for creating the first attack of the boss
    defining the sound effect of the attacks and
    the cries of the first three attacks.
*/
void GamePlayScene::CreateFirstBossAttack() {

    for (int i = 1; i < 5; i++) {
        std::string tentacleName = "FirstBossAttack" + std::to_string(i);
        auto firstBossAttack = new GameObject(tentacleName,
                                              new Vector(-4750, -1700), 100, 377,
                                                          2);
        //Tag
        firstBossAttack->SetTag("FirstBossAtack");

        // Script
        auto firstBossAttackScript = new  FirstBossAttackScript(firstBossAttack);

        //Sounds
        auto firstAttackSound = new UISound(firstBossAttack, "firstAttackSound",
                                            "assets/Audio/Boss/grito1.ogg",
                                            false, false);
        AudioController::GetInstance()->AddAudio(firstAttackSound);

        auto secondAttackSound = new UISound(firstBossAttack, "secondAttackSound",
                                            "assets/Audio/Boss/grito2.ogg",
                                            false, false);
        AudioController::GetInstance()->AddAudio(secondAttackSound);

        auto thirdAttackSound = new UISound(firstBossAttack, "thirdAttackSound",
                                            "assets/Audio/Boss/grito3.ogg",
                                            false, false);
        AudioController::GetInstance()->AddAudio(thirdAttackSound);

        auto fourthAttackSound = new UISound(firstBossAttack, "fourthAttackSound",
                                            "assets/Audio/Boss/heart_attack.ogg",
                                            false, false);
        AudioController::GetInstance()->AddAudio(fourthAttackSound);



        AddGameObject(firstBossAttack);
        FirstBossController::GetInstance()->AddTentacle(firstBossAttack);

        //bullet->active = false;

    }
}
/**
    @brief Responsible for creating the first boss life by setting the
    life bar and sending it to the class that creates the game objects.
*/
void GamePlayScene::CreateFirstBossLife() {

    // Life Border
    auto firstBossLifeBorderSprite = new GameObject("FirstBossBorderLife",
                                                    new Vector(0, 0),344, 25, 3);
    auto firstBossLifeBorderScript = new  FirstBossLifeBorderScript(firstBossLifeBorderSprite);
    AddGameObject(firstBossLifeBorderSprite);
    FirstBossController::GetInstance()->AddLifeBar(firstBossLifeBorderSprite);

    // Life
    auto firstBossLife = new GameObject("FirstBossLife",
                                        new Vector(0, 0),337, 25, 2);
    auto lifeRectangle = new RectangleRenderer(firstBossLife, Vector(0, 0), 337, 25);
    lifeRectangle->SetColor(255, 48, 48, 255);
    auto firstBossLifeScript = new  FirstBossLifeScript(firstBossLife);
    AddGameObject(firstBossLife);

    // Add to controller
    FirstBossController::GetInstance()->AddLifeBar(firstBossLife);

    // Desable all life bars
    FirstBossController::GetInstance()->DeactivateLifeBars();
}

/**
    @brief Responsible for creating the bullets that
    the player launches against the boss.
*/
void GamePlayScene::CreatePlayerAttack() {

    /** Creating Bullets **/
    for (int i = 1; i < 11; i++) {
        std::string bulletName = "Bullet" + std::to_string(i);
        auto bullet = new GameObject(bulletName, new Vector(100 * i, 0), 15, 15, 2);
        bullet->SetTag("Bullet");
        auto bulletScript = new  PlayerAttackScript(bullet);
        AddGameObject(bullet);

        auto bulletSound = new UISound(bullet, "bulletSound",
                                       "assets/Audio/Player/fireball.ogg",
                                        false, false);
        AudioController::GetInstance()->AddAudio(bulletSound);

        bullet->active = false;

        //MissileController::GetInstance()->AddPlayer(bullet);
        //bullet->active = false;
    }
    /** Bullet Counter **/
    auto bulletCounter = new GameObject("Score", new Vector(0, 0), 75 , 75, 2);
    bulletCounter->SetTag("BulletCounter");
    auto bulletText = new UIText(bulletCounter, "10",
                                 "assets/Fonts/advanced-pixel-7/advanced_pixel-7.ttf",
                                  150, 0 , 0, 0, 0, 1);
    auto bulletCounterScript = new BulletCounterScript(bulletCounter);
    AddGameObject(bulletCounter);
}

/**
    @brief Responsible for creating
    raindrops and the sound effect of rain.
*/
void GamePlayScene::CreateRain() {

    auto rain = new GameObject("Rain", new Vector(0,0),1024,800,1);
    auto rainScript = new RainScript(rain);
    auto rainSound = new UISound(rain, "rainSound",
                                 "assets/Audio/Boss/chuva.ogg",
                                 false, false);
    AudioController::GetInstance()->AddAudio(rainSound);
    AddGameObject(rain);
}

/**
    @brief Responsible for creating the hit object, which is the game's music.
*/
void GamePlayScene::CreatePlayerHit() {

    auto hit = new GameObject("Hit", new Vector(0,0),1024,800,1);

    auto hitScript = new HitScript(hit);
    AddGameObject(hit);
}

/**
    @grief Responsible for creating the visual effects of thunder.
*/
void GamePlayScene::CreateThunder() {

    auto thunder = new GameObject("Rain", new Vector(200,0),113,267,1);
    auto thunderScript = new ThunderScript(thunder);
    AddGameObject(thunder);
}

/**
    @grief Responsible for creating the visual effects of snow and the effect.
*/
void GamePlayScene::CreateSnow(){

    auto snow = new GameObject("Snow", new Vector(0,0),1024,800,1);
    auto snowScript = new SnowScript(snow);
    auto snowSound = new UISound(snow, "snowSound",
                                "assets/Audio/Clima/winteriscomming.ogg",
                                false, false);
    AudioController::GetInstance()->AddAudio(snowSound);
    AddGameObject(snow);
}

/**
    @grief Responsible for creating the visual effect of light.
*/
void GamePlayScene::CreateLight() {

    auto light = new GameObject("Light", new Vector(0,0),2*1024,2*800,2);
    auto lightScript = new LightScript(light);
    AddGameObject(light);
}

/**
    @grief Creates the visual effect of game credits.
*/
void GamePlayScene::CreateCreditAnimation() {

    /** Credits Animation **/
    auto creditAnimation = new GameObject("CreditAnimation",
                                          new Vector(0, 0),1200, 800, 3);

    auto creditRectangle = new RectangleRenderer(creditAnimation,
                                                 Vector(0, 0), 1200, 800);
    creditRectangle->SetColor(255, 48, 48, 255);
    auto creditsScript = new  CreditsScript(creditAnimation);
    AddGameObject(creditAnimation);
    FirstBossController::GetInstance()->AddCreditsAnimation(creditAnimation);
    FirstBossController::GetInstance()->DeactivateCreditsAnimation();
}

/**
    @grief Creates a player monition counter.
*/
void GamePlayScene::CreateAmmoCounter() {

    auto ammo = new GameObject("Ammo", new Vector(2,2),200,200,3);
    auto messengerText = new UIText(ammo, "15",
                                    "assets/UIpack/Font/kenvector_future_thin.ttf",
                                    100, 255, 255, 255, 255, 1);
    AddGameObject(ammo);
}
