#ifndef __CATCH_ALL_SCENE__
#define __CATCH_ALL_SCENE__

#include "Components/CircleCollider.h"
#include "Components/CircleRenderer.h"
#include "Components/RectangleCollider.h"
#include "Components/RectangleRenderer.h"
#include "Customs/PlayerScript.h"
#include "Engine/Scene.h"

class CatchAllScene : public Scene {
public:
  CatchAllScene();
  virtual void OnActivation() override;

private:
  void CreatePlayer();
  void CreateObstacles();
};

#endif
