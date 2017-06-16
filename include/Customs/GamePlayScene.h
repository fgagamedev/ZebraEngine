#ifndef __GAMEPLAYSCENE__
#define __GAMEPLAYSCENE__

#include "Engine/GameObject.h"
#include "Engine/Scene.h"
#include "Components/CircleRenderer.h"
#include "Components/RectangleRenderer.h"
#include "Components/Renderer.h"
#include "Components/Rigidbody.h"
#include "Components/UIText.h"
#include "Customs/MapScript.h"
#include "Customs/NakedManScript.h"
#include "Customs/SnowScript.h"
#include "Customs/RainScript.h"


class GamePlayScene : public Scene {
public:
  void OnActivation() override;
  void OnDeactivation() override;
  void OnShown() override;
  void OnHidden() override;

private:
  void CreateNakedMan();
  void CreateMap();
  void CreateRain();
  void CreateSnow();

};

#endif