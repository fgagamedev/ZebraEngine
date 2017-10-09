#ifndef FIRST_BOSS_CONTROLLER_H
#define FIRST_BOSS_CONTROLLER_H

#include <Engine/GameObject.hpp>

#include "Customs/FirstBossAttackScript.hpp"
#include <Globals/EngineGlobals.hpp>

#include <stdlib.h>
#include <time.h>

class FirstBossController {
public:
  static FirstBossController *GetInstance();

  void StartBossFight();
  void EndBossFight();

  // Add.
  void AddPlayer(GameObject *player);
  void AddBoss(GameObject *boss);
  void AddInsideBossFx(GameObject *bossInsideFx);
  void AddTentacle(GameObject *tentacle);
  void AddLifeBar(GameObject *lifeBar);
  void AddCreditsAnimation(GameObject *creditsAnimation);
  void AddMap(GameObject *map);

  // Posit.
  void PositPlayer(Vector newPosition);
  void PositBoss();
  void PositTentacle(int index);
  void PositAllTentacles();
  void PositMap(Vector newPosition);

  // Activate.
  void ActivatePlayer();
  void ActivateBoss();
  void ActivateInsideBossFx();
  void ActivateTentacles();
  void ActivateTentacle(int indexTentacle);
  void ActivateLifeBars();
  void ActivateCreditsAnimation();

  // Deactive.
  void DeactivatePlayer();
  void DeactivateBoss();
  void DeactivateInsideBossFx();
  void DeactivateTentacles();
  void DeactivateTentacle(int tentacleIndex);
  void DeactivateLifeBars();
  void DeactivateCreditsAnimation();

  // Define the attack of boss.
  void FirstAttackSurge();
  void FirstAttackGone();
  void SecondAttack();

  std::pair <int, int> GetRandomPosition();


private:
  FirstBossController();

  // Pointer that instantiates the control of the first boss.
  static FirstBossController *m_instance;

  // Pointer pointing to the player.
  GameObject *m_player = nullptr;

  // Pointer pointing to the boss.
  GameObject *m_boss = nullptr;

  // Pointer pointing to the boss inside.
  GameObject *m_bossInsideFx =  nullptr;

  // Pointer pointing to the credits animation.
  GameObject *m_creditsAnimation =  nullptr;

  // Pointer pointing to the map.
  GameObject *m_map =  nullptr;

  // Vector GameObject that defines the tentacles that appear in the attack of the boss.
  std::vector<GameObject *> m_tentacles;

  // Vector GameObject that defines the life bar of the boss.
  std::vector<GameObject *> m_lifeBars;

  //Positions
  int m_widthPosition;
  int m_heightPosition;

  // Variable count of tentacles released by boss attack.
  int m_currentTentacle = 1;
  std::pair <int, int> randomPosition;

};

#endif
