#ifndef __FIRST_BOSS_SCENE__
#define __FIRST_BOSS_SCENE__

#include "Components/CircleCollider.h"
#include "Components/RectangleCollider.h"
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
#include "Customs/FirstBossAttackScript.h"
#include "Customs/FirstBossCentralEffectScript.h"
#include "Engine/CameraSystem.h"

class FirstBossScene : public Scene {
public:
  	FirstBossScene();
  	virtual void OnActivation() override;
  	void OnDeactivation() override;
  	void OnShown() override;
	void OnHidden() override;
private:
  	void CreateMap();
	void CreatePlayer();
  	void CreateBoss();
  	void CreatePlayerAttack();
  	void CreateFirstBossAttack();
  	void CreateLight();
  	void CreateRain();
  	void CreateSnow();
  	void CreateThunder();
  	void CreateAmmoCounter();
  	void CreatePlayerHit();
  
};

#endif
