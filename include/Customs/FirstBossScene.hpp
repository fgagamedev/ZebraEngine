#ifndef __FIRST_BOSS_SCENE__
#define __FIRST_BOSS_SCENE__

#include "Engine/CameraSystem.hpp"
#include "Engine/GameObject.hpp"
#include "Engine/Scene.hpp"

#include "Components/CircleCollider.hpp"
#include "Components/RectangleCollider.hpp"
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
#include "Customs/FirstBossAttackScript.hpp"
#include "Customs/FirstBossCentralEffectScript.hpp"


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
