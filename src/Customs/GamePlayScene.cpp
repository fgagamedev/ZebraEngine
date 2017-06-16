#include "Customs/GamePlayScene.h"

void GamePlayScene::OnActivation() {
  CreateNakedMan();
  CreateMap();
  CreateRain();
  CreateSnow();
}

void GamePlayScene::OnDeactivation() {}

void GamePlayScene::OnShown() {}

void GamePlayScene::OnHidden() {}

void GamePlayScene::CreateNakedMan() {

  int xPos, yPos;
  xPos =EngineGlobals::screen_width / 2 - 96/2;
  yPos =EngineGlobals::screen_height / 2 - 96/2;
  auto nakedMan = new GameObject("NakedMan", new Vector(xPos,yPos),96 , 96, 1);
  // Script
  auto nakedManScript = new NakedManScript(nakedMan);
  AddGameObject(nakedMan);
}

void GamePlayScene::CreateMap() {
  //Original resolution is 2048/2048
  //6144,6144 = 3x
  auto map = new GameObject("Map", new Vector(-5630 ,-6130),12288,12288);
  // Renderer
  auto mapImage = new Image("assets/world.png", 0, 0, 2048, 2048);
  auto mapRenderer = new Renderer(map, mapImage);
  // Script
  auto mapScript = new MapScript(map);
  AddGameObject(map);
}


void GamePlayScene::CreateRain() {

  auto rain = new GameObject("Rain", new Vector(0,0),1050,800,1);
  auto rainScript = new RainScript(rain);
  AddGameObject(rain);

}
void GamePlayScene::CreateSnow(){
  auto snow = new GameObject("Snow", new Vector(-10,-10),1050,800,1);
  auto snowScript = new SnowScript(snow);
  AddGameObject(snow);

}