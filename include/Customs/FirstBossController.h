#ifndef FIRST_BOSS_CONTROLLER_H
#define FIRST_BOSS_CONTROLLER_H

#include <Engine/GameObject.h>
#include <Globals/EngineGlobals.h>
#include "Customs/FirstBossAttackScript.h"
#include <stdlib.h>
#include <time.h>

class FirstBossController {
public:
  static FirstBossController *GetInstance();

  void StartBossFight();
  void EndBossFight();
  
  /*Add*/
  void AddPlayer(GameObject *player);
  void AddBoss(GameObject *boss);
  void AddInsideBossFx(GameObject *bossInsideFx);
  void AddTentacle(GameObject *tentacle);
  void AddLifeBar(GameObject *lifeBar);
  void AddCreditsAnimation(GameObject *creditsAnimation);
  void AddMap(GameObject *map);
  
  /*Posit*/
  void PositPlayer(Vector newPosition);
  void PositBoss();
  void PositTentacle(int index);
  void PositAllTentacles();
  void PositMap(Vector newPosition);

  /*Activate*/
  void ActivatePlayer();
  void ActivateBoss();
  void ActivateInsideBossFx();
  void ActivateTentacles();
  void ActivateTentacle(int indexTentacle);
  void ActivateLifeBars();
  void ActivateCreditsAnimation();

  /*Deactive*/
  void DeactivatePlayer(); 
  void DeactivateBoss();
  void DeactivateInsideBossFx(); 
  void DeactivateTentacles(); 
  void DeactivateTentacle(int tentacleIndex);
  void DeactivateLifeBars();
  void DeactivateCreditsAnimation();

  void FirstAttackSurge();
  void FirstAttackGone();
  void SecondAttack(); 

  std::pair <int, int> GetRandomPosition();
  
  
private:
  FirstBossController();
  static FirstBossController *m_instance;
  
  //Objects
  GameObject *m_player = nullptr;
  GameObject *m_boss = nullptr;
  GameObject *m_bossInsideFx =  nullptr;
  GameObject *m_creditsAnimation =  nullptr;
  GameObject *m_map =  nullptr;
  std::vector<GameObject *> m_tentacles;
  std::vector<GameObject *> m_lifeBars;
  
  //Positions
  int m_wPos;
  int m_hPos;

  int actualTentacle = 1;
  std::pair <int, int> randomPosition;
  
};

#endif
