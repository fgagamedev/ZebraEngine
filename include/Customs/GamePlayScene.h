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
#include "Customs/HitScript.h"
#include "Customs/LightScript.h"
#include "Customs/FirstBossController.h"
#include "Customs/ThunderScript.h"
#include "Customs/PlayerAttackScript.h"
#include "Customs/FirstBossScript.h"
#include "Customs/FirstBossLifeBorderScript.h"
#include "Customs/FirstBossAttackScript.h"
#include "Customs/CreditsScript.h"
#include "Customs/FirstBossLifeScript.h"
#include "Customs/FirstBossCentralEffectScript.h"
#include "Customs/BulletCounterScript.h"


class GamePlayScene : public Scene {
public:
  void OnActivation() override;
  void OnDeactivation() override;
  void OnShown() override;
  void OnHidden() override;

private:
  void CreateNakedMan();
  void CreatePlayerAttack();
  void CreateFirstBoss();
  void CreateMap();
  void CreateLight();
  void CreateRain();
  void CreateSnow();
  void CreateThunder();
  void CreateFirstBossAttack();
  void CreateAmmoCounter();
  void CreatePlayerHit();
  void CreateFirstBossLife();
  void CreateCreditAnimation();




};

#endif