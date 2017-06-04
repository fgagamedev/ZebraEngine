#include "Customs/CatchAllScene.h"

CatchAllScene::CatchAllScene() {}

void CatchAllScene::OnActivation() {
  CreateObstacles();
  CreatePlayer();
}

void CatchAllScene::CreatePlayer() {
  auto player = new GameObject("Player", new Vector(25, 25), 40, 40, 2);
  // auto playerCircle = new CircleRenderer(player, Vector(0, 0), 20);
  // playerCircle->SetColor(255, 255, 255, 255);
  auto playerRectangle = new RectangleRenderer(player, Vector(0, 0), 40, 40);
  playerRectangle->SetColor(0, 150, 0, 255);
  auto playerScript = new PlayerScript(player);
  // auto colliderOffset = Vector(20, 20);
  // auto playerCollider = new CircleCollider(player, colliderOffset, 20, 0);
  auto playerCollider = new RectangleCollider(player, Vector(0, 0), 40, 40, 0);
  AddGameObject(player);
    }

void CatchAllScene::CreateObstacles() {
  auto obsRect = new GameObject("ObsRect", new Vector(200, 200), 40, 40, 1);
  auto obsRectRect = new RectangleRenderer(obsRect, Vector(0, 0), 40, 40);
  obsRectRect->SetColor(255, 255, 255, 255);
  auto obsRectCollider =
      new RectangleCollider(obsRect, Vector(0, 0), 40, 40, 0);
  AddGameObject(obsRect);

  auto obsCircle = new GameObject("ObsCircle", new Vector(400, 400), 40, 40, 1);
  auto obsCircleCircle = new CircleRenderer(obsCircle, Vector(0, 0), 20);
  obsCircleCircle->SetColor(255, 255, 255, 255);
  auto colliderOffset = Vector(0, 0);
  auto obsCircleCollider = new CircleCollider(obsCircle, colliderOffset, 20, 0);
  AddGameObject(obsCircle);
}
