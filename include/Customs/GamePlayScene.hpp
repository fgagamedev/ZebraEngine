#ifndef __GAMEPLAYSCENE__
#define __GAMEPLAYSCENE__

#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"

#include "Components/UISound.hpp"
#include "Components/CircleRenderer.hpp"
#include "Components/RectangleRenderer.hpp"
#include "Components/Renderer.hpp"
#include "Components/Rigidbody.hpp"
#include "Components/UIText.hpp"
#include "Customs/MapScript.hpp"
#include "Customs/NakedManScript.hpp"
#include "Customs/SnowScript.hpp"
#include "Customs/RainScript.hpp"
#include "Customs/HitScript.hpp"
#include "Customs/LightScript.hpp"
#include "Customs/FirstBossController.hpp"
#include "Customs/ThunderScript.hpp"
#include "Customs/PlayerAttackScript.hpp"
#include "Customs/FirstBossScript.hpp"
#include "Customs/FirstBossLifeBorderScript.hpp"
#include "Customs/FirstBossAttackScript.hpp"
#include "Customs/CreditsScript.hpp"
#include "Customs/FirstBossLifeScript.hpp"
#include "Customs/FirstBossCentralEffectScript.hpp"
#include "Customs/BulletCounterScript.hpp"
#include "Customs/AudioController.hpp"
#include "Customs/SnowActivatorScript.hpp"
#include "Customs/ForestActivatorScript.hpp"
#include "Customs/ForestActivatorScript2.hpp"
#include "Customs/ForestActivatorScript3.hpp"
#include "Customs/CentralLightScript1.hpp"
#include "Customs/CentralLightScript2.hpp"
#include "Customs/CentralLightScript3.hpp"
#include "Customs/CentralLightScript4.hpp"


class GamePlayScene : public Scene {
public:
  void OnActivation() override;
  void OnDeactivation() override;
  void OnShown() override;
  void OnHidden() override;

private:
  void CreateCutScenes();
  void CreateCentralLights();
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
  void CreateSounds();
  void CreateForestActivator();
  void CreateSnowActivator();





};

#endif
